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


#ifndef INCLUDED_QITKAT_ENTROPY_BF_H
#define INCLUDED_QITKAT_ENTROPY_BF_H

#include <qitkat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace qitkat {

    /*!
     * \brief Compute the shannon entropy of a string of binary symbols.
     * \ingroup qitkat
     *
     */
    class QITKAT_API entropy_bf : virtual public gr::block {
     public:
      typedef boost::shared_ptr<entropy_bf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of qitkat::entropy_bf.
       *
       * To avoid accidental use of raw pointers, qitkat::entropy_bf's
       * constructor is in a private implementation
       * class. qitkat::entropy_bf::make is the public interface for
       * creating new instances.
       */
      static sptr make(int num_items);
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_ENTROPY_BF_H */

