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

#ifndef INCLUDED_QITKAT_GET_HARDWARE_DATA_IMPL_H
#define INCLUDED_QITKAT_GET_HARDWARE_DATA_IMPL_H

#define ITEM_SIZE 1 // Bytes

#include <qitkat/get_hardware_data.h>
#include <string>
#include <zmq.hpp>

namespace gr {
  namespace qitkat {

    class get_hardware_data_impl : public get_hardware_data {
     public:
      get_hardware_data_impl(std::string address, unsigned short port, unsigned int requested);
      ~get_hardware_data_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
     private:
      std::string d_address;
      unsigned short d_port;
      unsigned int d_requested;
      
      ::zmq::context_t d_context;
      ::zmq::socket_t d_socket;
      
	  unsigned long d_received;
	  unsigned long d_toReceive;
    };
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_GET_HARDWARE_DATA_IMPL_H */

