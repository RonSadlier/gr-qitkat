/* -*- c++ -*- */
/*
 * Copyright 2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#include "send_message_b_impl.h"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gnuradio/io_signature.h>
#include <boost/lexical_cast.hpp>
#include <exception>

namespace gr {
	namespace qitkat {
		/**
		 * \brief \todo
		 */
		send_message_b::sptr send_message_b::make(const std::string endpoint,
					const unsigned int timeout,
					const std::string name) {
			return gnuradio::get_initial_sptr(new send_message_b_impl(endpoint, timeout, name));
		}
		
		/**
		 * \brief \todo
		 */
		send_message_b_impl::send_message_b_impl(const std::string endpoint,
				const unsigned int timeout,
				const std::string name)
				: gr::sync_block("send_message_b",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(0, 0, 0)),
				d_endpoint(endpoint), d_timeout(timeout), d_name(name), d_context(1),
				d_socket(d_context, ZMQ_REQ) {
			d_socket.connect(d_endpoint.c_str());
			d_socket.setsockopt(ZMQ_RCVTIMEO, &d_timeout, sizeof(d_timeout));
			d_socket.setsockopt(ZMQ_SNDTIMEO, &d_timeout, sizeof(d_timeout));
		}
		
		/**
		 * \brief \todo
		 */
		send_message_b_impl::~send_message_b_impl() {
		}
		
		/**
		 * \brief \todo
		 */
		int send_message_b_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			const char* in = (const char*)input_items[0];
			
			for(std::size_t i = 0; i < noutput_items; i++) {
				// We have to send ASCII characters, so convert raw binary to ascii binary
				char temp = in[i] + 48;
				std::string message("{\"method\":\"tx\",\"parameters\":[\""+d_name+"\", \""+std::string(&temp, 1)+"\"]}");
				d_socket.send(message.data(), message.size());
				std::cerr << "A";
				::zmq::message_t reply;
				d_socket.recv(&reply);
			}
			
			return noutput_items;
		}
	}
}
