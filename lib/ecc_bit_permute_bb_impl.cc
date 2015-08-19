/* -*- c++ -*- */
/*
 * Copyright 2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#include "ecc_bit_permute_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
	namespace qitkat {
		ecc_bit_permute_bb::sptr ecc_bit_permute_bb::make(std::vector<unsigned long> permutation_matrix) {
			return gnuradio::get_initial_sptr(new ecc_bit_permute_bb_impl(permutation_matrix));
		}
		
		ecc_bit_permute_bb_impl::ecc_bit_permute_bb_impl(std::vector<unsigned long> permutation_matrix)
				: gr::sync_block("ecc_bit_permute_bb",
					gr::io_signature::make(1, 1, sizeof(unsigned char)),
					gr::io_signature::make(1, 1, sizeof(unsigned char))), d_permutation_matrix(permutation_matrix) {

			// \todo: input sanity check

			set_output_multiple(permutation_matrix.size()/8);
		}
		
		ecc_bit_permute_bb_impl::~ecc_bit_permute_bb_impl() {
		}
		
		int ecc_bit_permute_bb_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char *) input_items[0];
			unsigned char *out = (unsigned char *) output_items[0];
			
			unsigned long numBytes = d_permutation_matrix.size()/8;
			
			for(unsigned long i = 0; i < noutput_items; i+=numBytes) {
				unsigned long inL(0);
				unsigned char* inC = (unsigned char*)(&inL);
				for(unsigned long j = 0; j < numBytes; j++) {
					inC[j] = in[i+j];
				}
				
				unsigned long outL(0);
				unsigned char* outC = (unsigned char*)&outL;
				
				for(unsigned long row = 0; row < d_permutation_matrix.size(); row++) {
					if(((inL >> d_permutation_matrix[row]) & 1) == 1) {
						outL |= 1 << row;
					}
				}
				
				for(unsigned long j = 0; j < numBytes; j++) {
					out[i+j] = outC[j];
				}
			}
			
			return noutput_items;
		}
	}
}
