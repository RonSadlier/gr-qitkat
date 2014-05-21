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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_TYPE_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_TYPE_H

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        /**
         * This class is the base for all types of quantum noises.
         *
         * This class should be kept empty. All "parent" code should be in
         * quantum_noise. All children should inherit from quantum_noise.
         * This naming convention is funky because great attention should be
         * given when editing state files. When creating a polymorphic state
         * object, this class should be used, e.g.
         *    noise_type* = ..
         * The guts of the parent code is more suited to be in the template file.
         */
        class noise_type {
         public:
          noise_type() {}
          ~noise_type() {}
          virtual void set_raw_p(unsigned char* data, unsigned int length) = 0;

          // TODO: The rest of the virtual functions needed for noise types

        };
      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_NOISE_TYPE_H */
