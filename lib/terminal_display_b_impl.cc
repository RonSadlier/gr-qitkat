/* -*- c++ -*- */
/* 
 * Copyright 2013-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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
#include "terminal_display_b_impl.h"

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		terminal_display_b::sptr terminal_display_b::make() {
			return gnuradio::get_initial_sptr(new terminal_display_b_impl());
		}
		
		/**
		 * \brief Constructor.
		 */
		terminal_display_b_impl::terminal_display_b_impl()
				: gr::sync_block("terminal_display_b",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(0, 0, 0)) {
		}
		
		/**
		 * \brief Destructor.
		 */
		terminal_display_b_impl::~terminal_display_b_impl() {
		}
		
		/**
		 * \brief Work function.
		 */
		int terminal_display_b_impl::work(int noutput_items,
					gr_vector_const_void_star &input_items,
					gr_vector_void_star &output_items) {
			const unsigned char *in = (const unsigned char*)input_items[0];
			
			for(std::size_t i = 0; i < noutput_items; i++) {
				std::cout << in[i];
			}
			
			return noutput_items;
		}
	}
}

