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

#ifndef INCLUDED_QITKAT_ECC_BIT_PERMUTE_BB_IMPL_H
#define INCLUDED_QITKAT_ECC_BIT_PERMUTE_BB_IMPL_H

#include <qitkat/ecc_bit_permute_bb.h>

namespace gr {
	namespace qitkat {
		class ecc_bit_permute_bb_impl : public ecc_bit_permute_bb {
		 public:
			ecc_bit_permute_bb_impl(std::vector<long> permutation_matrix);
			~ecc_bit_permute_bb_impl();

			int work(int noutput_items,
					gr_vector_const_void_star &input_items,
					gr_vector_void_star &output_items);
		 private:
			// Permutation matrix for bits. The lowest index is the least significant bit.
			std::vector<std::vector<bool> > perm_matrix;
		};
	}
}

#endif
