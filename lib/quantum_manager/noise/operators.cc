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

#include "operators.h"
#include <complex>

using namespace std;

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      static std::complex<double> i[2][2] = {{1, 0}, {0, 1}};
      static std::complex<double> x[2][2] = {{0, 1}, {1, 0}};
      static std::complex<double> y[2][2] = {{0, complex<double>(0, -1)}, {complex<double>(0, 1), 0}};
      static std::complex<double> z[2][2] = {{1, 0}, {0, -1}};
      static std::complex<double> i_i[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
      static std::complex<double> x_i[4][4] = {{0, 0, 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}};
      static std::complex<double> y_i[4][4] = {{0, 0, complex<double>(0, -1), 0}, {0, 0, 0, complex<double>(0, -1)}, { complex<double>(0, 1), 0, 0, 0}, {0, complex<double>(0, 1), 0, 0}};
      static std::complex<double> z_i[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, -1}};
      static std::complex<double> i_x[4][4] = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
      static std::complex<double> i_y[4][4] = {{0, complex<double>(0, -1), 0, 0}, {complex<double>(0, 1), 0, 0, 0}, {0, 0, 0, complex<double>(0, -1)}, {0, 0, complex<double>(0, 1), 0}};
      static std::complex<double> i_z[4][4] = {{1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, -1}};
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
