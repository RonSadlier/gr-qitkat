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


#ifndef INCLUDED_QITKAT_ECC_GOLAY2412_ENCODE_BB_H
#define INCLUDED_QITKAT_ECC_GOLAY2412_ENCODE_BB_H

#include <qitkat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace qitkat {

    /*!
     * \brief Encode data using the Golay2412 algorithm.
     * \ingroup qitkat
     *
     */
    class QITKAT_API ecc_golay2412_encode_bb : virtual public gr::block {
     public:
      typedef boost::shared_ptr<ecc_golay2412_encode_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of qitkat::ecc_golay2412_encode_bb.
       *
       * To avoid accidental use of raw pointers, qitkat::ecc_golay2412_encode_bb's
       * constructor is in a private implementation
       * class. qitkat::ecc_golay2412_encode_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_ECC_GOLAY2412_ENCODE_BB_H */

