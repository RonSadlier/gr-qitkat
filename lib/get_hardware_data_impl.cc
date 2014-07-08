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
#include "get_hardware_data_impl.h"

#include <boost/lexical_cast.hpp>

using namespace std;
using boost::asio::ip::tcp;

namespace gr {
  namespace qitkat {

    get_hardware_data::sptr get_hardware_data::make(string address, unsigned short port) {
      return gnuradio::get_initial_sptr(new get_hardware_data_impl(address, port));
    }

    /*
     * The private constructor
     */
    get_hardware_data_impl::get_hardware_data_impl(string address, unsigned short port)
      : gr::sync_block("get_hardware_data",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 1)), d_address(address), d_port(port), resolver(io_service),
              query(tcp::v4(), d_address, boost::lexical_cast<string>(d_port)), iterator(resolver.resolve(query)), s(io_service) {

      memset(buffer, 0, MAX_PACKET_SIZE);

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
    get_hardware_data_impl::~get_hardware_data_impl() {
    }

    int get_hardware_data_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {

      unsigned char *out = (unsigned char*) output_items[0];

      size_t read_header_size = boost::asio::read(s, boost::asio::buffer(buffer, PACKET_HEADER_SIZE));

      // Number of packets
      unsigned int body_count = 0;
      unsigned char* body_count_p = (unsigned char*)&body_count;
      body_count_p[0] = buffer[0];
      body_count_p[1] = buffer[1];
      body_count_p[2] = buffer[2];

      if(body_count > 1) {
        size_t read_body_size = boost::asio::read(s, boost::asio::buffer(buffer+PACKET_HEADER_SIZE, body_count*ITEM_SIZE));
        // We'll probably need to be more sophisticated here in the future,
        // but for right now this is ok.
        memcpy(out, buffer+PACKET_HEADER_SIZE, body_count*ITEM_SIZE);
        // Tell runtime system how many output items we produced.
        return body_count*ITEM_SIZE;
      } else {
        // TODO
        std::cerr << "No data received.";
        exit(-1);
      }
    }

  } /* namespace qitkat */
} /* namespace gr */

