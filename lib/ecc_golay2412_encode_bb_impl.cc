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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ecc_golay2412_encode_bb_impl.h"
#include "ecc_golay.h"

namespace gr {
  namespace qitkat {

    ecc_golay2412_encode_bb::sptr ecc_golay2412_encode_bb::make() {
      return gnuradio::get_initial_sptr(new ecc_golay2412_encode_bb_impl());
    }

    ecc_golay2412_encode_bb_impl::ecc_golay2412_encode_bb_impl()
      : gr::block("ecc_golay2412_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
    }

    ecc_golay2412_encode_bb_impl::~ecc_golay2412_encode_bb_impl() {
    }

    void ecc_golay2412_encode_bb_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
        ninput_items_required[0] = 3*noutput_items;
    }

    int ecc_golay2412_encode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        unsigned int outputPos = 0;

        for(int i = 0; i < noutput_items; i+=3) {
          // This are temporary holders for two halfs of 24 bits
          unsigned long firstPart = 0;
          unsigned char* pFirstPart = (unsigned char*)&firstPart;
          unsigned long secondPart = 0;
          unsigned char* pSecondPart = (unsigned char*)&secondPart;	

          // We can only convert 12 bits at a time, so we have to pack them properly
          pFirstPart[0] = in[i]; // 8 Bits
          pFirstPart[1] = in[i+1] & 0x0F; // 12 Bits 
          pSecondPart[0] = (in[i+1] & 0xF0) >> 4; // 4 Bits
          pSecondPart[0] += (in[i+2] & 0x0F) << 4; // 8 Bits
          pSecondPart[1] = (in[i+2] & 0xF0) >> 4; // 12 Bits

          // We encode each 12 bit input to a 24 bit output
          unsigned long encoded1 = golay_encode(firstPart);
          unsigned char* pEncoded1 = (unsigned char*)&encoded1;
          unsigned long encoded2 = golay_encode(secondPart);
          unsigned char* pEncoded2 = (unsigned char*)&encoded2;

          // Unpack our encoded bits
          out[outputPos] = pEncoded1[0]; // 8 Bits
          out[outputPos+1] = pEncoded1[1]; // 16 Bits
          out[outputPos+2] = pEncoded1[2]; // 24 Bits
          out[outputPos+3] = pEncoded2[0]; // 8 Bits
          out[outputPos+4] = pEncoded2[1]; // 16 Bits
          out[outputPos+5] = pEncoded2[2]; // 24 Bits
          outputPos += 6;
      }
      // Consume each input byte
      consume_each(noutput_items);

      // We have items available for the scheduler.
      return noutput_items*2;
    }

  } /* namespace qitkat */
} /* namespace gr */

