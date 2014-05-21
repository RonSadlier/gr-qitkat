/* -*- c++ -*- */
/* 
 * Copyright 2014 Ronald Sadlier - Oak Ridge National Laboratory
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


#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_H

#include <qitkat/api.h>
#include <gnuradio/block.h>
#include <vector>

namespace gr {
  namespace qitkat {

    /*!
     * \brief Communicate with our quantum manager server.
     * \ingroup qitkat
     *
     */
    class QITKAT_API quantum_manager_query : virtual public gr::block {
     public:
      typedef boost::shared_ptr<quantum_manager_query> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of qitkat::quantum_manager_query.
       *
       * To avoid accidental use of raw pointers, qitkat::quantum_manager_query's
       * constructor is in a private implementation
       * class. qitkat::quantum_manager_query::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned char channel_id, unsigned char noise_type, unsigned char state_type, unsigned int inputtypehack, unsigned int outputtypehack, unsigned char pcount, std::vector<unsigned char> p);
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_H */

