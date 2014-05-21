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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_QUANTUM_NOISE_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_QUANTUM_NOISE_H

#include "noise_type.h"
#include <vector>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        /**
         * The direct child of noise_type. This is the real parent
         * of each noise type.
         */
        template <class T> class quantum_noise : public noise_type {
         public:
          std::vector<T> get_p() {
            return p;
          }

          std::vector<T> *pget_p() {
            return &p;
          }

          virtual void set_raw_p(unsigned char* data, unsigned int length) = 0;

          // TODO: The rest of the virtual functions needed for noise types

         protected:
          void set_p(std::vector<T> p) {
            this->p = p;
          }

         private:
          std::vector<T>  p;
        };

      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_QUANTUM_NOISE_H */
