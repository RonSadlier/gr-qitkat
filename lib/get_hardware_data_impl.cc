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
#include "get_hardware_data_impl.h"

#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <exception>

using namespace std;

namespace gr {
  namespace qitkat {

    get_hardware_data::sptr get_hardware_data::make(string address, unsigned short port, unsigned int requested) {
      return gnuradio::get_initial_sptr(new get_hardware_data_impl(address, port, requested));
    }

    get_hardware_data_impl::get_hardware_data_impl(string address, unsigned short port, unsigned int requested)
      : gr::sync_block("get_hardware_data",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 1)), d_address(address), d_port(port), d_requested(requested),
               d_context(1), d_socket(d_context, ZMQ_REQ), d_received(0), d_toReceive(requested) {
      // Try to connect to the server
      std::string connectAddress = "tcp://"+address+":"+boost::lexical_cast<std::string>(port);
      d_socket.connect(connectAddress.c_str());
    }

    get_hardware_data_impl::~get_hardware_data_impl() {
    }

    int get_hardware_data_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {

      unsigned char *out = (unsigned char*) output_items[0];

      // We don't have anything left to get
      if(d_toReceive == 0) {
	    return -1;
	  }

      ::zmq::message_t request(4);
	  unsigned long requestNow(0);

      if(noutput_items <= d_toReceive) {
		// Not enough buffer space to store all the requested data
        // Only request a partial amount
        requestNow = noutput_items;
	  } else {
		requestNow = d_toReceive;
	  }
	  
      unsigned char* data = (unsigned char*)request.data();
      data[0] = (unsigned char)(requestNow >> 24);
      data[1] = (unsigned char)(requestNow >> 16);
      data[2] = (unsigned char)(requestNow >> 8);
      data[3] = (unsigned char)(requestNow);
      d_socket.send(request);
      
      ::zmq::message_t reply;
      d_socket.recv(&reply);
	  
      if(reply.size() == 0) {
        return 0;
      } else {
		d_received += reply.size();
		d_toReceive -= reply.size();
		memcpy(out, (unsigned char*)reply.data(), reply.size());
		return reply.size();
	  }
    }

  } /* namespace qitkat */
} /* namespace gr */

