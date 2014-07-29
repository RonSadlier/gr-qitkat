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
#include "send_hardware_data_impl.h"

#include <boost/lexical_cast.hpp>

using namespace std;
using boost::asio::ip::tcp;

namespace gr {
  namespace qitkat {

    send_hardware_data::sptr send_hardware_data::make(std::string address, unsigned short port) {
      return gnuradio::get_initial_sptr(new send_hardware_data_impl(address, port));
    }

    /*
     * The private constructor
     */
    send_hardware_data_impl::send_hardware_data_impl(std::string address, unsigned short port)
      : gr::sync_block("send_hardware_data",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(0, 0, 0)), d_address(address), d_port(port), resolver(io_service),
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
    send_hardware_data_impl::~send_hardware_data_impl() {
      s.shutdown(tcp::socket::shutdown_both);
      s.close();
    }

    int send_hardware_data_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {

      const unsigned char* in = (const unsigned char *) input_items[0];

      unsigned int body_count = 0;
      unsigned char* body_count_p = (unsigned char*)&body_count;

      if(noutput_items*ITEM_SIZE + PACKET_HEADER_SIZE > MAX_PACKET_SIZE) {
        body_count = (int)((MAX_PACKET_SIZE-PACKET_HEADER_SIZE)/ITEM_SIZE);
      } else {
        body_count = noutput_items;
      }
      buffer[0] = body_count_p[0];
      buffer[1] = body_count_p[1];
      buffer[2] = body_count_p[2];

      for(unsigned int i = 0; i < body_count; i++) {
        buffer[PACKET_HEADER_SIZE+i] = in[i];
      }

      boost::asio::write(s, boost::asio::buffer(buffer, body_count*ITEM_SIZE + PACKET_HEADER_SIZE));

      // Tell runtime system how many output items we produced.
      return body_count;
    }

  } /* namespace qitkat */
} /* namespace gr */
