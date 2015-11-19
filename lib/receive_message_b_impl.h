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

#ifndef INCLUDED_QITKAT_RECEIVE_MESSAGE_B_IMPL_H
#define INCLUDED_QITKAT_RECEIVE_MESSAGE_B_IMPL_H

#include <qitkat/receive_message_b.h>
#include <string>
#include <zmq.hpp>

namespace gr {
	namespace qitkat {
		class receive_message_b_impl : public receive_message_b {
		 public:
			receive_message_b_impl(const std::string endpoint,
					const unsigned int timeout,
					const std::string name);
			~receive_message_b_impl();
			
			int work(int noutput_items,
					gr_vector_const_void_star &input_items,
					gr_vector_void_star &output_items);
		
		 private:
			std::string d_endpoint;
			unsigned int d_timeout;
			std::string d_name;
			::zmq::context_t d_context;
			::zmq::socket_t d_socket;
		};
	}
}

#endif
