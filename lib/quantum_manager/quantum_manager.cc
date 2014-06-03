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

#include "quantum_manager.h"
#include "noise/special_case_optimization.h"
#include "noise/binary_symmetric_channel.h"

namespace gr {
  namespace qitkat {
    namespace quantum_manager {

      quantum_manager* quantum_manager::pInstance = NULL;

      quantum_manager* quantum_manager::instance() {
        // Singleton: return this instance if it exists, if not created it
        if (!pInstance) {
          pInstance = new quantum_manager;
        }
        return pInstance;
      }

      quantum_manager::quantum_manager() {
      }

      /**
       * The mathematical definition of mod.
       */
      int quantum_manager::mod(int a, int b) {
        return (a%b+b)%b;
      }

      /**
       * Return a random number based on a weighted PDF.
       * Each element in distribution is a weight for its corresponding index, ie:
       * distribution = {.5,.5} has a probability of picking 0 and 1 with a 50% chance each.
       * Size is the number of elements in distribution, or 2^size = dimension.
       * From: http://www.boost.org/doc/libs/1_46_0/libs/random/example/weighted_die.cpp
       */
      unsigned int quantum_manager::pick_weighted_number(double distribution[], unsigned int size) {
        std::vector<double> cumulative;
        std::partial_sum(&distribution[0], &distribution[0] + size, std::back_inserter(cumulative));
        boost::uniform_real<> dist(0, cumulative.back());
        boost::variate_generator<boost::mt19937&, boost::uniform_real<> > die(gen, dist);
        return (unsigned int)(std::lower_bound(cumulative.begin(), cumulative.end(), die()) - cumulative.begin());
      }

      /**
       * Create a quantum channel with a desired channel_id and parameters.
       */
      void quantum_manager::create_channel(unsigned char channel_id, state::state_type* state_type, noise::noise_type* noise_type) {
        std::pair<std::map<unsigned char, quantum_channel>::iterator, bool> ret;
        ret = quantum_channels.insert(
            std::pair<unsigned char, quantum_channel>(channel_id, quantum_channel(state_type, noise_type)));

        // Check if the channel already exists.
        if(ret.second == false) {
          std::cerr << "WARNING: quantum channel cannot be created, channel_id already in use: " << (int)channel_id << std::endl;
        }
      }

      /**
       * Return a quantum channel with a given channel_id.
       */
      quantum_channel* quantum_manager::get_channel(unsigned char channel_id) {
        return &quantum_channels[channel_id];
      }

      /**
       * Create managed qudits on a channel.
       */
      unsigned int quantum_manager::create_managed_qudits(unsigned char channel_id, unsigned char* state) {
        if(quantum_channels.find(channel_id) == quantum_channels.end()) {
          // Channel not found
          std::cerr << "WARNING: managed qudits cannot be created, channel_id not found: " << (int)channel_id << std::endl;
          return 0;
        } else {
          // Insert the state data
          return quantum_channels.at(channel_id).state_type()->insert_state_element(state);
        }
      }

      //
      // Measurements
      //

      /**
       * Perform a projective measurement to the bell basis.
       */
      unsigned char quantum_manager::projective_bell_measurement(unsigned char channel_id, unsigned int state_id) {
        quantum_channel& current_channel = quantum_channels.at(channel_id);

        // Used with our custom optimizations. If it is true after running through them, then we have done our work.
        // If it is false after running through our optimizations, we must manually perform the math.
        bool optimize_indicator = false;

        unsigned char return_state = noise::special_case_optimization::projective_bell_measurement(current_channel, state_id, optimize_indicator);

        if(!optimize_indicator) {
          // Check if we can use vector notation
          if(current_channel.state_type()->is_vector_compatible()) {
            // We can use the vector state
            std::vector<std::complex<double> > state = current_channel.state_type()->get_state_vector(state_id);
            current_channel.noise_type()->apply_noise(&state);

            // Perform projective measurement

            // TODO: Perform projective measurement

          } else {
            // We have to use the density matrix
            boost::numeric::ublas::matrix<std::complex<double> > state = current_channel.state_type()->get_density_matrix(state_id);
            current_channel.noise_type()->apply_noise(&state);

            // Perform projective measurement

            // TODO: Perform projective measurement
          }
        }

        return return_state;
      }
    }
  }
}
