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

#include "special_case_optimization.h"
#include "../quantum_manager.h"
#include "depolarizing.h"
#include "../state/bell.h"
#include <cmath>

using namespace gr::qitkat::quantum_manager;

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        unsigned char special_case_optimization::projective_bell_measurement(quantum_channel& current_channel,
            unsigned int state_id, bool& indicator) {
          if(typeid(current_channel.state_type()) == typeid(state::bell)) {
            if(typeid(current_channel.noise_type()) == typeid(depolarizing)) {
              // Bell State
              unsigned char current_state = dynamic_cast<state::bell*>(current_channel.state_type())->get_encoded_state(state_id);

              // Depolarizing noise
              depolarizing *noise_type = dynamic_cast<depolarizing*>(current_channel.noise_type());

              // convert to pointer
              std::vector<double> p = noise_type->get_p();

              unsigned short n = current_channel.state_type()->get_n();
              unsigned int state_size = current_channel.state_type()->get_state_size();

              // For each bell state, we calculate Prob(B_j,|Psi), then we store each of those probabilities in an array,
              // with the index being the respective bell state. Then, we choose that element based on the probability, and the
              // resulting index is the bell state
              double distribution[state_size];

              // Perform our vector transformation using our encoding pattern
              // Loop through possible output states to map probabilities to each
              for(unsigned int i = 0; i < state_size; i++) {
                distribution[i] = p[::quantum_manager::instance()->mod(i - current_state, n) +
                    n * ::quantum_manager::instance()->mod(floor(i/n) - floor(current_state/n), n)];
              }

              // We were able to calculate the state transformation
              indicator = true;
              return ::quantum_manager::instance()->pick_weighted_number(distribution, state_size);
            }
          }

          // We weren't able to do anything here
          indicator = false;
          return 0;
        }

      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
