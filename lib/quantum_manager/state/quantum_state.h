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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_QUANTUM_STATE_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_QUANTUM_STATE_H

#include "state_type.h"
#include <cmath>
#include <map>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace state {

        template <class T> class quantum_state : public state_type {
         public:
          quantum_state(bool vector_compatible) {
            this->vector_compatible = vector_compatible;
          }

          void set_state_size(unsigned char n, unsigned char m) {
            this->n = n;
            this->m = m;
          }

          unsigned char get_n() {
            return n;
          }

          unsigned char get_m() {
            return m;
          }

          unsigned int get_state_size() {
            return pow(n, m);
          }

          unsigned int get_state_element_count() {
            return state_count;
          }

          void delete_state_element(unsigned int state_id) {
            states.erase(state_id);
          }

          // Since this cannot be accessed through state_type*, this is used
          // only when the state type is known.
          T get_encoded_state(unsigned int state_id);

          bool is_vector_compatible() {
            return vector_compatible;
          }

         protected:
          unsigned char n;
          unsigned char m;
          unsigned int state_count;
          std::map<unsigned int, T> states;
          bool vector_compatible;
        };
      } // namspace state
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_QUANTUM_STATE_H */
