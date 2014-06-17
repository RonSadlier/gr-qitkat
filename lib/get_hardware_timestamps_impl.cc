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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define MAX_PACKET_SIZE 256
#define PACKET_HEADER_SIZE 3

#include <gnuradio/io_signature.h>
#include "get_hardware_timestamps_impl.h"

#include <boost/lexical_cast.hpp>

using namespace std;
using boost::asio::ip::tcp;

namespace gr {
  namespace qitkat {

    get_hardware_timestamps::sptr get_hardware_timestamps::make(string address, unsigned short port) {
      return gnuradio::get_initial_sptr(new get_hardware_timestamps_impl(address, port));
    }

    /*
     * The private constructor
     */
    get_hardware_timestamps_impl::get_hardware_timestamps_impl(string address, unsigned short port)
      : gr::sync_block("get_hardware_timestamps",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 1)), d_address(address), d_port(port), resolver(io_service),
              query(tcp::v4(), d_address, boost::lexical_cast<string>(d_port)), iterator(resolver.resolve(query)), s(io_service) {

      // Try to connect to the server
      try {
        s.connect(*iterator);
      } catch(exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
      }

    }

    /*
     * Our virtual destructor.
     */
    get_hardware_timestamps_impl::~get_hardware_timestamps_impl() {
    }

    int get_hardware_timestamps_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {
        unsigned char *out = (unsigned char*) output_items[0];

        unsigned char buffer[MAX_PACKET_SIZE];
        size_t read_header_size = boost::asio::read(s, boost::asio::buffer(buffer, PACKET_HEADER_SIZE));

        unsigned int body_size = (buffer[0] << 16) + (buffer[1] << 8) + buffer[2];

        size_t read_body_size = boost::asio::read(s, boost::asio::buffer(buffer+3, body_size));

        unsigned char* timestamps = &buffer[3];

        // TODO: Process timestamps

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace qitkat */
} /* namespace gr */

