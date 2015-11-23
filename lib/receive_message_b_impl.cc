/* -*- c++ -*- */
/*
 * Copyright 201 Ronald J. 5Sadlier - Oak Ridge National Laboratory
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


#include "receive_message_b_impl.h"
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
		receive_message_b::sptr receive_message_b::make(const std::string endpoint,
				const unsigned int timeout,
				const unsigned int receivedMax) {
			return gnuradio::get_initial_sptr(new receive_message_b_impl(endpoint, timeout, receivedMax));
		}
		
		/**
		 * \brief \todo
		 */
		receive_message_b_impl::receive_message_b_impl(const std::string endpoint,
				const unsigned int timeout,
				const unsigned int receivedMax)
				: gr::sync_block("receive_message_b",
				gr::io_signature::make(0, 0, 0),
				gr::io_signature::make(1, 1, 1)),
				d_endpoint(endpoint), d_timeout(timeout), d_receivedCount(0),
				d_receivedMax(receivedMax), d_context(1), d_socket(d_context, ZMQ_SUB) {
			d_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
			d_socket.connect(d_endpoint.c_str());
		}
		
		/**
		 * \brief \todo
		 */
		receive_message_b_impl::~receive_message_b_impl() {
			d_socket.disconnect(d_endpoint.c_str());
		}
		
		/**
		 * \brief \todo
		 */
		int receive_message_b_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			unsigned char* out = (unsigned char*)output_items[0];
			
			if(d_receivedCount == d_receivedMax) {
				return -1;
			}
			
			zmq::pollitem_t items[] = { { d_socket, 0, ZMQ_POLLIN, 0 } };
			zmq::poll(&items[0], 1, d_timeout);
			
			if(items[0].revents & ZMQ_POLLIN) {
				zmq::message_t msg;
				d_socket.recv(&msg);
				::rapidjson::Document _dom;
				char* buffer = new char[msg.size()+1];
				memcpy(buffer, msg.data(), msg.size());
				memset(buffer+msg.size(), '\0', 1);
				_dom.Parse(buffer);
				delete[] buffer;
				
				/** \todo: this may be a problem later on!!!! **/
				out[0] = _dom["result"].GetUint();
				
				d_receivedCount++;
				
				return 1;
			}
			
			return 0;
		}
	}
}
