/* -*- c++ -*- */
/* 
 * Copyright 2014 Travis S. Humble - Oak Ridge National Laboratory
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


#ifndef INCLUDED_QITKAT_BER_BF_H
#define INCLUDED_QITKAT_BER_BF_H

#include <qitkat/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace qitkat {

    /*!
     * \brief Calculate the BER between two unsigned char input streams of num_items, bit by bit.
     *        Use bit_mask to isolate relevant bits in each iterm. Values for bit_mask range from 0x01 to 0xFF.
     * \ingroup qitkat
     *
     */
    class QITKAT_API ber_bf : virtual public gr::sync_decimator {
     public:
      typedef boost::shared_ptr<ber_bf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of qitkat::ber_bf.
       *
       * To avoid accidental use of raw pointers, qitkat::ber_bf's
       * constructor is in a private implementation
       * class. qitkat::ber_bf::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned int num_items, unsigned char bit_mask);
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_BER_BF_H */

