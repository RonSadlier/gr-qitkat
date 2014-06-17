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


#ifndef INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_H
#define INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_H

#include <qitkat/api.h>
#include <gnuradio/sync_block.h>
#include <string>

namespace gr {
  namespace qitkat {

    /*!
     * \brief Listen for timestamps from our hardware.
     * \ingroup qitkat
     *
     */
    class QITKAT_API get_hardware_timestamps : virtual public gr::sync_block {
     public:
      typedef boost::shared_ptr<get_hardware_timestamps> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of qitkat::get_hardware_timestamps.
       *
       * To avoid accidental use of raw pointers, qitkat::get_hardware_timestamps's
       * constructor is in a private implementation
       * class. qitkat::get_hardware_timestamps::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string address, unsigned short port);
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_GET_HARDWARE_TIMESTAMPS_H */

