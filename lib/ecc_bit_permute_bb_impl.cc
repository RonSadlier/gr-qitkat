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
		ecc_bit_permute_bb::sptr ecc_bit_permute_bb::make(std::vector<long> permutation_matrix) {
			return gnuradio::get_initial_sptr(new ecc_bit_permute_bb_impl(permutation_matrix));
		}
		
		ecc_bit_permute_bb_impl::ecc_bit_permute_bb_impl(std::vector<long> permutation_matrix)
				: gr::sync_block("ecc_bit_permute_bb",
					gr::io_signature::make(1, 1, sizeof(unsigned char)),
					gr::io_signature::make(1, 1, sizeof(unsigned char))),
				perm_matrix(24, std::vector<bool>(24, false)) {
			for(unsigned long row = 0; row < permutation_matrix.size(); row++) {
				unsigned long size = sizeof(permutation_matrix[row])*8;
				for(unsigned long bit = 0; bit < size; bit++) {
					if((permutation_matrix[row] >> bit) & 1 == 1) {
						perm_matrix[row][bit] = true;
						break;
					}
				}
			}
			set_output_multiple(3);
		}
		
		ecc_bit_permute_bb_impl::~ecc_bit_permute_bb_impl() {
		}
		
		int ecc_bit_permute_bb_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char *) input_items[0];
			unsigned char *out = (unsigned char *) output_items[0];
			
			// \todo: make this generic
			for(unsigned long i; i < noutput_items; i+=3) {
				unsigned long inL(0);
				unsigned char* inC = (unsigned char*)(&inL);
				inC[0] = in[i+2];
				inC[1] = in[i+1];
				inC[2] = in[i+0];
				
				unsigned long outL(0);
				unsigned char* outC = (unsigned char*)&outL;
				
				for(unsigned long row = 0; row < perm_matrix.size(); row++) {
					for(unsigned long col = 0; col < perm_matrix[row].size(); col++) {
						if(perm_matrix[row][col] && (inL >> row) & 1 == 1) {
							outL |= 1 << col;
							break;
						}
					}
				}
				
				out[i+0] = outC[2];
				out[i+1] = outC[1];
				out[i+2] = outC[0];
			}
			
			return noutput_items;
		}
	}
}
