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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_QUANTUM_MANAGER_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_QUANTUM_MANAGER_H

#include "state/quantum_state.h"
#include "noise/quantum_noise.h"
#include <complex>
#include <map>
#include <vector>
#include <boost/random.hpp>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {

      /**
       * The quantum channel through which select parties are communicating with some
       * defined parameters.
       */
      struct quantum_channel {
       public:
        quantum_channel() {}
        quantum_channel(state::state_type* state_type, noise::noise_type* noise_type)
            : state_type_(state_type), noise_type_(noise_type) {
        }
        ~quantum_channel() {}

        state::state_type* state_type() {
          return state_type_;
        }

        noise::noise_type* noise_type() {
          return noise_type_;
        }

        unsigned int get_state_element_count() {
          return state_type_->get_state_element_count();
        }

        template<typename T> void insert_state_element(std::vector<T> &state) {
          state_type_->insert_state_element(state);
        }

       private:
        // The type of state the quantum channel can handle.
        // This also contains the list of states, since the type of element is dynamic.
        state::state_type* state_type_;

        // The type of noise the quantum channel models.
        // This also contains the list of probabilities, since the type of element is dynamic.
        noise::noise_type* noise_type_;
      };

      /**
       * This class acts as a daemon in the code through being singleton, providing
       * the interface to the quantum simulation code.
       */
      class quantum_manager {
       public:
        // Singleton functions.
        static quantum_manager* instance();

        void create_channel(unsigned char channel_id, state::state_type* state_type, noise::noise_type* noise_type);

        quantum_channel* get_channel(unsigned char channel_id);

        unsigned int create_managed_qudits(unsigned char channel_id, unsigned char* state);

        unsigned char projective_bell_measurement(unsigned char channel_id, unsigned int state_id);

        // The mathematically defined mod function.
        int mod(int a, int b);

        unsigned int pick_weighted_number(double distribution[], unsigned int size);

       private:
        // Singleton functions.
        quantum_manager();
        quantum_manager(quantum_manager const&){};
        quantum_manager& operator=(quantum_manager const&){};
        static quantum_manager* pInstance;

        // The random number generator used to simulate quantum effects.
        boost::mt19937 gen;

        std::map<unsigned char, quantum_channel> quantum_channels;
        unsigned char quantum_channel_count;
      };
    } //namespace quantum_manager
  } // namespace qitkat
} // namespace gr

#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_QUANTUM_MANAGER_H */

