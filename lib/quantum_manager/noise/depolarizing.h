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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_DEPOLARIZING_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_DEPOLARIZING_H

#include "quantum_noise.h"

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        class depolarizing : public quantum_noise<double> {
         public:
          depolarizing() {}
          ~depolarizing() {}

          void set_raw_p(unsigned char* data, unsigned int length);
          void apply_noise(std::vector<std::complex<double> >* state);
          void apply_noise(boost::numeric::ublas::matrix<std::complex<double> >* state);
        };
      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_DEPOLARIZING_H */
