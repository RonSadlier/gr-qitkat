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

#define UNIT_SIZE 8 // bytes

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "extract_hardware_sdc_impl.h"

namespace gr {
  namespace qitkat {

    extract_hardware_sdc::sptr extract_hardware_sdc::make() {
      return gnuradio::get_initial_sptr(new extract_hardware_sdc_impl());
    }

    extract_hardware_sdc_impl::extract_hardware_sdc_impl()
      : gr::sync_decimator("extract_hardware_sdc",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), UNIT_SIZE) {
    }

    extract_hardware_sdc_impl::~extract_hardware_sdc_impl() {
    }

    int extract_hardware_sdc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      unsigned int output_pos = 0;

      // Deal with whole events, UNIT_SIZE bytes at a time.
      for(int i = 0; i < noutput_items*UNIT_SIZE; i+=UNIT_SIZE) {
        // We really only care about the last byte though
        if(in[i+7] == 17) {
          out[output_pos] = 0;
          output_pos++;
        } else if(in[i+7] == 64) {
          out[output_pos] = 1;
          output_pos++;
        } else if(in[i+7] == 68) {
          out[output_pos] = 2;
          output_pos++;
        } else if(in[i+7] == 136){
          out[output_pos] = 3;
          output_pos++;
        } else {
          std::cerr << "Unknown input state on extract hardware sdc";
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace qitkat */
} /* namespace gr */

