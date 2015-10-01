/* -*- c++ -*- */
/* 
 * Copyright 2013, 2014 Ronald J. Sadlier - Oak Ridge National Laboratory
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
#include "qrng_source_i_impl.h"

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		qrng_source_i::sptr qrng_source_i::make(std::string middleware) {
			return gnuradio::get_initial_sptr(new qrng_source_i_impl(middleware));
		}
		
		/**
		 * \brief Constructor.
		 */
		qrng_source_i_impl::qrng_source_i_impl(std::string middleware)
				: gr::sync_block("qrng_source_i",
				gr::io_signature::make(0, 0, 0),
				gr::io_signature::make(1, 1, sizeof(unsigned int))),
				d_middleware(middleware), d_context(1), d_socket(d_context, ZMQ_REQ) {
			set_output_multiple(2);
			d_socket.connect(d_middleware.c_str());
		}
		
		/**
		 * \brief Destructor.
		 */
		qrng_source_i_impl::~qrng_source_i_impl() {
			d_socket.disconnect(d_middleware.c_str());
		}
		
		/**
		 * \brief Work function.
		 */
		int qrng_source_i_impl::work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items) {
			unsigned int *out = (unsigned int*)output_items[0];
			
			for(std::size_t i = 0; i < noutput_items; i+=2) {
				d_socket.send("{\"transaction_type\":\"rx\"}", 27);
				::zmq::message_t response;
				d_socket.recv(&response);
				
				/** \todo */
			}
			
			return noutput_items;
		}
	}
}

