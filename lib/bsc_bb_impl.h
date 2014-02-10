/* -*- c++ -*- */
/* 
 * Copyright 2011 - 2014 Travis S. Humble - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_BSC_BB_IMPL_H
#define INCLUDED_QITKAT_BSC_BB_IMPL_H

#include <qitkat/bsc_bb.h>

namespace gr {
  namespace qitkat {

    class bsc_bb_impl : public bsc_bb {
     private:
      // BSC error rate.
      float d_error_rate;

      // PRNG seed.
      unsigned int d_seed;

      // Bit mask to indicate alphabet size, ie which bits within each byte to check.
      unsigned char d_bit_mask;

      // The number of bits in each byte to check according to the bitmask.
      unsigned char d_bit_mask_len;

     public:
      bsc_bb_impl(float error_rate, unsigned int seed, unsigned char bit_mask);
      ~bsc_bb_impl();

      int general_work(int noutput_items,
		     gr_vector_int &ninput_items,
		     gr_vector_const_void_star &input_items,
		     gr_vector_void_star &output_items);
    };
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_BSC_BB_IMPL_H */

