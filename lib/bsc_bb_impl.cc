/* -*- c++ -*- */
/* 
 * Copyright 2011-2013 Travis S. Humble - Oak Ridge National Laboratory
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

#include "bsc_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		bsc_bb::sptr bsc_bb::make(float error_rate, unsigned int seed, unsigned char bit_mask) {
			return gnuradio::get_initial_sptr(new bsc_bb_impl(error_rate, seed, bit_mask));
		}
		
		/**
		 * \brief Constructor.
		 */
		bsc_bb_impl::bsc_bb_impl(float error_rate, unsigned int seed, unsigned char bit_mask)
				: gr::sync_block("bsc_bb",
				gr::io_signature::make(1, 1, 1),
				gr::io_signature::make(1, 1, 1)) {
			// BSC error rate
			d_error_rate = error_rate;
			
			// PRNG seed
			d_seed = seed;
			
			// PRNG initializer: srand() sets the seed for rand()
			srand(seed);
			
			// Initialize bit mask for encoded alphabet
			d_bitmask = bit_mask;
			
			// Loop through bits in a byte
			int current_index = 0;
			for(std::size_t i = 0; i < 8; i++) {
				// We only care about the bits set in the bitmask
				if(d_bitmask & (1 << i)) {
					d_bitmask_indices[current_index] = i;
					current_index++;
				}
			}
			d_bitmask_hweight = current_index;
			
			if(d_error_rate == 1.0) {
				// Rounding gets iffy here
				d_rand_threshold = RAND_MAX;
			} else {
				d_rand_threshold = d_error_rate*RAND_MAX;
			}
		}
		
		/**
		 * \brief Destructor.
		 */
		bsc_bb_impl::~bsc_bb_impl() {
		}
		
		/**
		 * \brief Work function.
		 */
		int bsc_bb_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char *)input_items[0];
			unsigned char *out = (unsigned char *)output_items[0];
			
			memcpy(out, in, noutput_items);
			
			for(std::size_t i = 0; i < noutput_items; i++) {
				// Loop through bits we care about
				/** \brief \todo: this has a bug! */
				for(std::size_t j = 0; j < d_bitmask_hweight; j++) {
					if(rand() < d_rand_threshold) {
					out[i] ^= 1 << d_bitmask_indices[j];
					}
				}
			}
			
			// Tell runtime system how many output items we produced.
			return noutput_items;
		}
	}
}

