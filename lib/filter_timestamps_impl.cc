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
#include "filter_timestamps_impl.h"

namespace gr {
  namespace qitkat {

    filter_timestamps::sptr filter_timestamps::make() {
      return gnuradio::get_initial_sptr(new filter_timestamps_impl());
    }

    filter_timestamps_impl::filter_timestamps_impl()
      : gr::block("filter_timestamps",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
    }

    filter_timestamps_impl::~filter_timestamps_impl(){
    }

    void filter_timestamps_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
        // We need at least 64 bits (one record), so we need 8 bytes.
        ninput_items_required[0] = 8;
    }

    int filter_timestamps_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      unsigned int outpos = 0;

      for(unsigned int j = 1; j < 7; j++) {
          out[outpos] = in[j];
          outpos++;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      //consume_each ((int)(noutput_items/8)*8);
      consume_each(8);

      // Tell runtime system how many output items we produced.
      return outpos;
    }

  } /* namespace qitkat */
} /* namespace gr */

