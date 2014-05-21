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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_SPECIAL_CASE_OPTIMIZATION_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_SPECIAL_CASE_OPTIMIZATION_H

#include "../quantum_manager.h"
#include "noise_type.h"

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        /**
         * List of functions mirroring the list of measurement functions in quantum_manager,
         * optimized for specific circumstances.
         */
        class special_case_optimization {
         public:
          static unsigned char projective_bell_measurement(::gr::qitkat::quantum_manager::quantum_channel& current_channel,
              unsigned int state_id, bool& indicator);
        };

      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_SPECIAL_CASE_OPTIMIZATION_H */
