/* -*- c++ -*- */
/*
 * Copyright 2014-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#include "ecc_repetition_decode_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
	namespace qitkat {
		unsigned long ecc_repetition_decode_bb_impl::power2_table[8] = {1, 2, 4, 8, 16, 32, 64, 128};
		
		/**
		 * \brief todo.
		 */
		ecc_repetition_decode_bb::sptr ecc_repetition_decode_bb::make(unsigned int repetition) {
			return gnuradio::get_initial_sptr(new ecc_repetition_decode_bb_impl(repetition));
		}
		
		/**
		 * \brief Constructor.
		 */
		ecc_repetition_decode_bb_impl::ecc_repetition_decode_bb_impl(unsigned int repetition)
				: gr::sync_decimator("ecc_repetition_decode_bb",
					gr::io_signature::make(1, 1, sizeof(unsigned char)),
					gr::io_signature::make(1, 1, sizeof(unsigned char)), repetition), d_repetition(repetition) {
			d_hamming_middle = repetition/2.0;
		}
		
		/**
		 * \brief Destructor.
		 */
		ecc_repetition_decode_bb_impl::~ecc_repetition_decode_bb_impl() {
		}
		
		/**
		 * \brief Work function.
		 */
		int ecc_repetition_decode_bb_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char *) input_items[0];
			unsigned char *out = (unsigned char *) output_items[0];
			
			std::size_t inByte(0);
			std::size_t inBit(0);
			
			memset(out, 0, noutput_items);
			
			for(std::size_t outByte = 0; outByte < noutput_items; outByte++) {
				for(std::size_t outBit = 0; outBit < 8; outBit++) {
					std::vector<bool> symbol(d_repetition, 0);
					for(std::size_t i = 0; i < d_repetition; i++) {
						if(inBit > 7) {
							inBit = 0;
							inByte++;
						}
						symbol[i] = (in[inByte] & power2_table[inBit]) >> inBit;
						inBit++;
					}
					if(std::accumulate(symbol.begin(), symbol.end(), 0) > d_hamming_middle) {
						out[outByte] += 1 << outBit;
					}
				}
			}
			return noutput_items;
		}
	}
}
