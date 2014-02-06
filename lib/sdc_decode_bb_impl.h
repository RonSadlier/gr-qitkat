/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_QITKAT_SDC_DECODE_BB_IMPL_H
#define INCLUDED_QITKAT_SDC_DECODE_BB_IMPL_H

#include <qitkat/sdc_decode_bb.h>

namespace gr {
  namespace qitkat {

    class sdc_decode_bb_impl : public sdc_decode_bb {
     private:
      // This is the root number of basis states for the qudits. This may or may not
      // be the number of bits to encode with. The number of basis states can
      // support up to n^2 number of states, while bits have 2^n states.
      //
      // Currently, 2 <= n <= 7
      unsigned char d_n;

      // The number of bits that can be encoded into each qudit.
      unsigned char d_num_bits_encoded;

      // The number of flags required each iteration.
      unsigned char d_num_flags_required;

      // The number of bytes to output each iteration.
      unsigned char d_num_bytes_output;

     public:
      sdc_decode_bb_impl(int n);

      ~sdc_decode_bb_impl();
   
      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_SDC_DECODE_BB_IMPL_H */

