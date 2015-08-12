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

#include "ecc_repetition_encode_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
	namespace qitkat {
		unsigned long ecc_repetition_encode_bb_impl::power2_table[8] = {1, 2, 4, 8, 16, 32, 64, 128};
		
		ecc_repetition_encode_bb::sptr ecc_repetition_encode_bb::make(unsigned int repetition) {
			return gnuradio::get_initial_sptr(new ecc_repetition_encode_bb_impl(repetition));
		}
		
		ecc_repetition_encode_bb_impl::ecc_repetition_encode_bb_impl(unsigned int repetition)
				: gr::sync_interpolator("ecc_repetition_encode_bb",
					gr::io_signature::make(1, 1, sizeof(unsigned char)),
					gr::io_signature::make(1, 1, sizeof(unsigned char)), repetition), d_repetition(repetition) {
		}
		
		ecc_repetition_encode_bb_impl::~ecc_repetition_encode_bb_impl() {
		}
		
		int ecc_repetition_encode_bb_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char *) input_items[0];
			unsigned char *out = (unsigned char *) output_items[0];
			
			unsigned long inByte(0);
			unsigned long inBit(0);
			unsigned long outByte(0);
			unsigned long outBit(0);
			
			memset(out, 0, noutput_items);
			
			while(outByte < noutput_items) {
				if(inBit > 7) {
					inBit = 0;
					++inByte;
				}
				for(unsigned long i = 0; i < d_repetition; i++) {
					if(outBit > 7) {
						outBit = 0;
						++outByte;
					}
					out[outByte] += ((in[inByte] & power2_table[inBit]) >> inBit) << outBit;
					++outBit;
				}
				++inBit;
			}
			
			return noutput_items;
		}
	}
}
