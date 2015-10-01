/* -*- c++ -*- */
/*
 * Copyright 2014-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#include "send_hardware_data_impl.h"
#include <gnuradio/io_signature.h>
#include <exception>
#include <boost/lexical_cast.hpp>

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		send_hardware_data::sptr send_hardware_data::make(std::string address, unsigned short port) {
			return gnuradio::get_initial_sptr(new send_hardware_data_impl(address, port));
		}
		
		/**
		 * \brief Constructor.
		 */
		send_hardware_data_impl::send_hardware_data_impl(std::string address, unsigned short port)
				: gr::sync_block("send_hardware_data",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(0, 0, 0)), d_address(address), d_port(port),
				d_context(1), d_socket(d_context, ZMQ_REQ) {
			d_socket.connect(std::string("tcp://"+address+":"+boost::lexical_cast<std::string>(port)).c_str());
		}
		
		/**
		 * \brief Destructor.
		 */
		send_hardware_data_impl::~send_hardware_data_impl() {
			//d_socket.disconnect(connectAddress.c_str());
		}
		
		/**
		 * \brief Work function.
		 */
		int send_hardware_data_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const unsigned char* in = (const unsigned char *) input_items[0];
			
			::zmq::message_t request(noutput_items+1);
			memset((unsigned char*)request.data(), 1, 1);
			unsigned char *data = (unsigned char*)request.data();
			memcpy(&data[1], in, noutput_items);
			d_socket.send(request);
			
			::zmq::message_t reply;
			d_socket.recv(&reply);
			
			return noutput_items;
		}
	}
}
