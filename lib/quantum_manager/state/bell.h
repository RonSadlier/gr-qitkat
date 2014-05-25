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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_BELL_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_BELL_H

#include "quantum_state.h"
#include <complex>
#include <vector>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace state {

        /**
         * A Bell state of some dimension. 
         */
        class bell : public quantum_state<unsigned char> {
         public:
          bell() { }
          ~bell() { }

          // Get the number of bytes used to store a single state.
          unsigned short get_state_byte_size();

          // Return a state in its native format.
          unsigned char get_encoded_state(unsigned int state_id);

          // Insert a state from raw bytes. 
          unsigned int insert_state_element(const unsigned char* state);

          // Return the standardized state vector.
          std::vector<std::complex<double> > get_state_vector(unsigned int state_id);

          // Return the standardized density matrix.
          std::vector<std::vector<std::complex<double> > > get_density_matrix(unsigned int state_id);
        };
      } // namspace state
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_STATE_BELL_H */
