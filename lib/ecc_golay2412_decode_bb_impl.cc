/* -*- c++ -*- */
/* 
 * Copyright 2014 Ronald J. Sadlier - Oak Ridge National Laboratory
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
#include "ecc_golay2412_decode_bb_impl.h"

#include "ecc_golay.h"

namespace gr {
  namespace qitkat {

    ecc_golay2412_decode_bb::sptr ecc_golay2412_decode_bb::make() {
      return gnuradio::get_initial_sptr(new ecc_golay2412_decode_bb_impl());
    }

    ecc_golay2412_decode_bb_impl::ecc_golay2412_decode_bb_impl()
      : gr::block("ecc_golay2412_decode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
      set_output_multiple(3);
    }

    ecc_golay2412_decode_bb_impl::~ecc_golay2412_decode_bb_impl() {
    }

    void ecc_golay2412_decode_bb_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
        ninput_items_required[0] = 6*noutput_items;
    }

    int ecc_golay2412_decode_bb_impl::general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      unsigned int inPos = 0;
      unsigned int outPos = 0;

      while(inPos < noutput_items*6) {
        // This are temporary holders for two 24 bit strings
        unsigned long firstPart = 0;
        unsigned char* pFirstPart = (unsigned char*)&firstPart;
        unsigned long secondPart = 0;
        unsigned char* pSecondPart = (unsigned char*)&secondPart;	

        // Repack bits
        pFirstPart[0] = in[inPos]; // 8 Bits
        pFirstPart[1] = in[inPos+1]; // 16 Bits 
        pFirstPart[2] = in[inPos+2]; // 24 Bits 
        pSecondPart[0] = in[inPos+3]; // 8 Bits
        pSecondPart[1] = in[inPos+4]; // 16 Bits
        pSecondPart[2] = in[inPos+5]; // 24 Bits

        // We decode each 24 bit input to a 12 bit output
        unsigned long decoded1 = golay_decode(firstPart);
        unsigned char* pDecoded1 = (unsigned char*)&decoded1;
        unsigned long decoded2 = golay_decode(secondPart);
        unsigned char* pDecoded2 = (unsigned char*)&decoded2;

        // Unpack our dedcoded bits
        out[outPos] = pDecoded1[0]; // 8 Bits
        out[outPos+1] = pDecoded1[1] & 0x0F; // 12 Bits 
        out[outPos+1] += (pDecoded2[0] & 0x0F) << 4; // 16 Bits
        out[outPos+2] = (pDecoded2[0] & 0xF0) >> 4; // 20 Bits
        out[outPos+2] += (pDecoded2[1] & 0x0F) << 4; // 24 Bits
        inPos += 6;
        outPos += 3;
      }

      // Consume 6 input bytes
      consume_each(inPos);

      // We have items available for the scheduler.
      return outPos;
    }

  } /* namespace qitkat */
} /* namespace gr */

