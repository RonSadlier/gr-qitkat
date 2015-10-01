/* -*- c++ -*- */
/* 
 * Copyright 2011-2012 Travis S. Humble - Oak Ridge National Laboratory
 * Copyright 2013-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "entropy_bf_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		entropy_bf::sptr entropy_bf::make(int num_items) {
			return gnuradio::get_initial_sptr(new entropy_bf_impl(num_items));
		}
		
		/**
		 * \brief Constructor.
		 */
		entropy_bf_impl::entropy_bf_impl(int num_items)
				: gr::block("entropy_bf",
				gr::io_signature::make(1, 2, sizeof(unsigned char)),
				gr::io_signature::make(1, 1, sizeof(float))) {
			d_num_items = num_items;
		}
		
		/**
		 * \brief Destructor.
		 */
		entropy_bf_impl::~entropy_bf_impl() {
		}
		
		/**
		 * \brief Forecast function.
		 */
		void entropy_bf_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
			ninput_items_required[0] = d_num_items;
			ninput_items_required[1] = d_num_items;
		}
		
		int entropy_bf_impl::general_work (int noutput_items,
				gr_vector_int &ninput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			// Input streams are determined below
			float* out = (float*)output_items[0];
			
			if(output_items.size() == 2) {
				// 2 inputs, joint entropy.
				unsigned char* in0 = (unsigned char*)input_items[0];
				unsigned char* in1 = (unsigned char*)input_items[1];
				out[0] = joint_entropy(in0, in1, d_num_items);
			} else { 
				// 1 input, marginal entropy.
				unsigned char* in = (unsigned char*)input_items[0];
				out[0] = single_entropy(in, d_num_items);
			}
			
			consume_each(d_num_items);
			return 1;
		}
		
		/**
		 * \brief Method to compute entropy of joint input streams.
		 */
		float entropy_bf_impl::joint_entropy(void* in0, void* in1, std::size_t size) {
			// 4 bins for possible binary values.
			uint_fast64_t zz(0);
			uint_fast64_t oo(0);
			uint_fast64_t oz(0);
			uint_fast64_t zo(0);
			
			// Compute relative probabilities.
			for(std::size_t i = 0; i < size; i++) {
				if((((unsigned char*)in0)[i] == 0x0) && (((unsigned char*)in1)[i] == 0x0))  {
					// 0,0
					zz++;
				} else if((((unsigned char*)in0)[i] == 0x0) && (((unsigned char*)in1)[i] == 0x1)) {
					// 0,1
					zo++;
				} else if((((unsigned char*)in0)[i] == 0x1) && (((unsigned char*)in1)[i] == 0x0)) {
					// 1,0 
					oz++;
				} else if((((unsigned char*)in0)[i] == 0x1) && (((unsigned char*)in1)[i] == 0x1)) {
					// 1,1
					oo++;
				}
			}
			
			float p00 = (float)zz / (float)d_num_items;
			float p01 = (float)zo / (float)d_num_items;
			float p10 = (float)oz / (float)d_num_items;
			float p11 = (float)oo / (float)d_num_items;
			
			// This version does not work on MAC OS X
			/*
			// avoid NAN
			float term00(-p00*log2f(p00));
			if(isnan(term00)) { 
				term00 = 0;
			}
			
			// avoid NAN
			float term01(-p01*log2f(p01));
			if(isnan(term01)) {
				term01 = 0;
			}
			
			// avoid NAN
			float term10(-p10*log2f(p10));
			if(isnan(term10)) {
				term10 = 0;
			}
			
			// avoid NAN
			float term11(-p11*log2f(p11));
			if(isnan(term11)) { 
				term11 = 0;
			}
			*/
			
			// Work around for MAC OS X.
			float term00(-p00*log2f(p00));
			if(p00 == 0) {
				term00 = 0;
			}
			
			float term01(-p01*log2f(p01));
			if(p01 == 0) {
				term01 = 0;
			}
			
			float term10(-p10*log2f(p10));
			if(p10 == 0) {
				term10 = 0;
			}
			
			float term11(-p11*log2f(p11));
			if(p11 == 0) {
				term11 = 0;
			}
			
			// Add up entropy terms.
			float entropy = term00 + term01 + term10 + term11;
			
			return entropy;
		}
		
		/**
		 * \brief Method to compute entropy of single input stream.
		 */
		float entropy_bf_impl::single_entropy(void* in, const std::size_t size) {
			// Count the number of ones in the input.
			uint_fast64_t ones(0);
			for(std::size_t i = 0; i < size; i++) {
				// If it is 1, increase; otherwise, not.
				ones += 0x1 & ((unsigned char*)in)[i];  
			}
			
			// individual probabilities for 1's and 0's
			float p1((float)(ones) / (float)(size));
			float p0(1. - p1);
			
			// This version does not work on MAC OS X.
			/*
			// Avoid NAN
			float term0(-p0*log2f(p0));
			if(isnan(term0)) {
				term0 = 0;
			}
			
			// Avoid NAN
			float term1(-p1*log2f(p1));
			if(isnan(term1)) {
				term1 = 0;
			}
			*/
			
			// Work around for MAC OS X.
			// Avoid NAN
			float term0(-p0*log2f(p0));
			if(p0 == 0) {
				term0 = 0;
			}
			
			// Avoid NAN
			float term1(-p1*log2f(p1));
			if(p1 == 0) {
				term1 = 0;
			}
			
			// Binary entropy function.
			float entropy = term0 + term1;
			
			return entropy;
		}
	}
}

