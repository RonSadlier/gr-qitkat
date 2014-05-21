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

#include <vector>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace state {

        /**
         * This class is the base for all types of quantum states.
         *
         * All children should inherit from quantum_state.
         * This naming convention is funky because great attention should be
         * given when editing state files. When creating a polymorphic state
         * object, this class should be used, e.g.
         *    state_type* = ..
         * The majority of the parent code is more suited to be in the template file.
         */
        class state_type {
         public:
          state_type() {}
          ~state_type() {}

          virtual unsigned int get_state_size() {}
          virtual void set_size(unsigned char n, unsigned char m) = 0;
          virtual unsigned char get_n() = 0;
          virtual unsigned char get_m() = 0;
          virtual unsigned int insert_state_element(const unsigned char* state) = 0;
          virtual unsigned int get_state_element_count() = 0;
          virtual unsigned short get_state_unit_size() = 0;
          // TODO: virtual functions to get standardized states
        };
      } // namspace state
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_STATE_TYPE_H */
