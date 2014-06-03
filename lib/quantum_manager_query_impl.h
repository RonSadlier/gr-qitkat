/* -*- c++ -*- */
/* 
 * Copyright 2013 - 2014 Ronald Sadlier - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_IMPL_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_IMPL_H

#include <qitkat/quantum_manager_query.h>
#include <vector>

namespace gr {
  namespace qitkat {

    class quantum_manager_query_impl : public quantum_manager_query {
     public:
      quantum_manager_query_impl(unsigned char channel_id, unsigned char noise_type, unsigned char state_type, unsigned int inputtypehack, unsigned int outputtypehack, unsigned char pcount, std::vector<unsigned char> p);
      ~quantum_manager_query_impl();

      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_QUERY_IMPL_H */
