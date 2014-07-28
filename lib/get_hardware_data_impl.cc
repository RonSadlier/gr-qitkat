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

#include <algorithm>

using namespace std;
using boost::asio::ip::tcp;

namespace gr {
  namespace qitkat {

    get_hardware_data::sptr get_hardware_data::make(string address, unsigned short port) {
      return gnuradio::get_initial_sptr(new get_hardware_data_impl(address, port));
    }

    get_hardware_data_impl::get_hardware_data_impl(string address, unsigned short port)
      : gr::sync_block("get_hardware_data",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 1)), d_address(address), d_port(port), resolver(io_service),
              query(tcp::v4(), d_address, boost::lexical_cast<string>(d_port)), iterator(resolver.resolve(query)), s(io_service) {

      memset(buffer, 0, MAX_PACKET_SIZE);
      buffer_size = 0;

      // Try to connect to the server
      try {
        s.connect(*iterator);
      } catch(exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
      }

    }

    get_hardware_data_impl::~get_hardware_data_impl() {
    }

    int get_hardware_data_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {

      unsigned char *out = (unsigned char*) output_items[0];
      
      if(buffer_size != 0) {
        if(buffer_size > noutput_items) {
          memcpy(out, buffer, noutput_items);
          for(int i = noutput_items; i < buffer_size; i++) {
            buffer[i - noutput_items] = buffer[i];
          }
          buffer_size -= noutput_items;
          return noutput_items;
        } else {
          memcpy(out, buffer, buffer_size);
          int temp = buffer_size;
          buffer_size = 0;

          return temp;
        }
      } else {
        // We have nothing in our buffer
        try {
          boost::asio::read(s, boost::asio::buffer(buffer, PACKET_HEADER_SIZE));
        } catch (std::exception& e) {
          // Timeout from our server not sending anything
          return -1;
        }

        // Number of units in packet
        int body_count = (int)buffer[0] + ((int)buffer[1] << 8) + ((int)buffer[2] << 16);

        if(body_count > 1) {
          buffer_size = boost::asio::read(s, boost::asio::buffer(buffer, body_count*ITEM_SIZE));
          
          if(buffer_size > noutput_items) {
            memcpy(out, buffer, noutput_items);
            for(int i = noutput_items; i < buffer_size; i++) {
              buffer[i - noutput_items] = buffer[i];
            }
            buffer_size -= noutput_items;

            return noutput_items;
          } else {
            memcpy(out, buffer, buffer_size);
            int temp = buffer_size;
            buffer_size = 0;

            return temp;
          }
        } else {
          // TODO
          std::cerr << "No data received.";
          exit(-1);
        }
      }
    }

  } /* namespace qitkat */
} /* namespace gr */

