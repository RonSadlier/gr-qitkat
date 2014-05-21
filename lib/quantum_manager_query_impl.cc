/* -*- c++ -*- */
/* 
 * Copyright 2013 - 2014 Ronald Sadlier - Oak Ridge National Laboratory
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
#include "quantum_manager_query_impl.h"

namespace gr {
  namespace qitkat {

    quantum_manager_query::sptr
    quantum_manager_query::make(unsigned char channel_id, unsigned char noise_type, unsigned char state_type, unsigned int inputtypehack, unsigned int outputtypehack, unsigned char pcount, std::vector<unsigned char> p) {
      return gnuradio::get_initial_sptr(new quantum_manager_query_impl(channel_id, noise_type, state_type, inputtypehack, outputtypehack, pcount, p));
    }

    quantum_manager_query_impl::quantum_manager_query_impl(unsigned char channel_id, unsigned char noise_type, unsigned char state_type, unsigned int inputtypehack, unsigned int outputtypehack, unsigned char pcount, std::vector<unsigned char> p)
      : gr::block("quantum_manager_query",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))) {
      // TODO: Fill in function
    }

    quantum_manager_query_impl::~quantum_manager_query_impl() {
    }

    void quantum_manager_query_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required) {
        // TODO: Fill in function
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int quantum_manager_query_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        // TODO: Fill in function

        return 0;
    }

  } /* namespace qitkat */
} /* namespace gr */

