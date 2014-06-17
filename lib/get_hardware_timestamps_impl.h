/* -*- c++ -*- */
/*
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_IMPL_H
#define INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_IMPL_H

#include <qitkat/get_hardware_timestamps.h>
#include <string>
#include <boost/asio.hpp>

namespace gr {
  namespace qitkat {

    class get_hardware_timestamps_impl : public get_hardware_timestamps {
     public:
      get_hardware_timestamps_impl(std::string address, unsigned short port);
      ~get_hardware_timestamps_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
     private:
      std::string d_address;
      unsigned short d_port;
      boost::asio::io_service io_service;
      boost::asio::ip::tcp::resolver resolver;
      boost::asio::ip::tcp::resolver::query query;
      boost::asio::ip::tcp::resolver::iterator iterator;
      boost::asio::ip::tcp::socket s;
    };
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_IMPL_H */

