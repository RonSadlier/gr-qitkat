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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_STATE_TYPE_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_STATE_TYPE_H

#include <complex>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace state {

        /**
         * This class is the base for all types of quantum states.
         *
         * The only child of this class should be quantum_state. All implementations
         * of states should inherit from quantum_state.
         * The majority of the parent code is more suited to be in the template file,
         * so there should not be any implementions at all in this file.
         */
        class state_type {
         public:
          state_type() {}
          ~state_type() {}

          virtual void set_state_size(unsigned char n, unsigned char m) = 0;
          virtual unsigned int get_state_size() = 0;
          virtual unsigned char get_n() = 0;
          virtual unsigned char get_m() = 0;
          virtual unsigned short get_state_byte_size() = 0;
          virtual unsigned int get_state_element_count() = 0;
          virtual unsigned int insert_state_element(const unsigned char* state) = 0;
          virtual void delete_state_element(unsigned int state_id) = 0;
          virtual std::vector<std::complex<double> > get_state_vector(unsigned int state_id) = 0;
          virtual boost::numeric::ublas::matrix<std::complex<double> > get_density_matrix(unsigned int state_id) = 0;
          virtual bool is_vector_compatible() = 0;
        };
      } // namspace state
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_STATE_TYPE_H */
