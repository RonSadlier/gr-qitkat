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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_MAP_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_MAP_H

#include "binary_symmetric_channel.h"
#include "depolarizing.h"

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        // This maps numerical values to our C++ noise types.
        static noise_type* get_noisetype(unsigned char id) {
          // Unmanaged memory
          noise_type* returnnoise;

          switch(id) {
            case 0:
              returnnoise = dynamic_cast<noise_type*>(new binary_symmetric_channel());
              return returnnoise;
              break;

            case 10:
              returnnoise = dynamic_cast<noise_type*>(new depolarizing());
              return returnnoise;
              break;
          }
        }
      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_MAP_H */
