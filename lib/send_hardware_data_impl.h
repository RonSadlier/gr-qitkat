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

#ifndef INCLUDED_QITKAT_SEND_HARDWARE_DATA_IMPL_H
#define INCLUDED_QITKAT_SEND_HARDWARE_DATA_IMPL_H

#define ITEM_SIZE 1 // Bytes, since we are only sending SDC flags

#include <qitkat/send_hardware_data.h>
#include <string>
#include <zmq.hpp>

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		class send_hardware_data_impl : public send_hardware_data {
		 public:
			send_hardware_data_impl(std::string address, unsigned short port);
			~send_hardware_data_impl();
			
			int work(int noutput_items,
					gr_vector_const_void_star &input_items,
					gr_vector_void_star &output_items);
		
		 private:
			std::string d_address;
			unsigned short d_port;
			::zmq::context_t d_context;
			::zmq::socket_t d_socket;
		};
	}
}

#endif

