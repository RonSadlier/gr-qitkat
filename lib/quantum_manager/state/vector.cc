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

#include "vector.h"
#include "state_type.h"

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace state {

        unsigned short vector::get_state_byte_size() {
          return 16*pow(n, m);
        }

        std::vector<std::complex<double> > vector::get_encoded_state(unsigned int state_id) {
          return this->states.at(state_id);
        }

        unsigned int vector::insert_state_element(const unsigned char* state) {
          std::vector<std::complex<double> > input_state;

          for(unsigned short i = 0; i < get_state_byte_size(); i += 2*sizeof(double)) {
            input_state.push_back(std::complex<double>(*(double*)&state[i], *(double*)&state[i+sizeof(double)]));
          }

          states.insert(std::pair<unsigned int, std::vector<std::complex<double> > >(state_count, input_state));
          return ++state_count;
        }

        std::vector<std::complex<double> > vector::get_state_vector(unsigned int state_id) {
          return this->states.at(state_id);
        }

        boost::numeric::ublas::matrix<std::complex<double> > vector::get_density_matrix(unsigned int state_id) {
          // TODO
        }

      } // namspace state
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
