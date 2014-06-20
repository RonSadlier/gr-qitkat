/* -*- c++ -*- */
/*
 * Copyright 2014 Ronald Sadlier - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_ECC_REPETITION_ENCODE_BB_IMPL_H
#define INCLUDED_QITKAT_ECC_REPETITION_ENCODE_BB_IMPL_H

#include <qitkat/ecc_repetition_encode_bb.h>

namespace gr {
  namespace qitkat {

    class ecc_repetition_encode_bb_impl : public ecc_repetition_encode_bb {
     private:
      // The number of times to repeat something.
      unsigned int d_repetition;

     public:
      ecc_repetition_encode_bb_impl(unsigned int repetition);

      ~ecc_repetition_encode_bb_impl();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_ECC_REPETITION_ENCODE_BB_IMPL_H */

