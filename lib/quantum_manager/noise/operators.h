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

#ifndef INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_OPERATORS_H
#define INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_OPERATORS_H

#include <complex>
#include "../storage_adaptors.h"
#include <boost/numeric/ublas/matrix.hpp>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      class operators {
       public:
        // Most frequently used operators are hardcoded
        static boost::numeric::ublas::matrix<std::complex<double> > i() {
          return boost::numeric::ublas::make_matrix_from_pointer(2, 2, &(_i[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > x() {
          return boost::numeric::ublas::make_matrix_from_pointer(2, 2, &(_x[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > y() {
          return boost::numeric::ublas::make_matrix_from_pointer(2, 2, &(_y[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > z() {
          return boost::numeric::ublas::make_matrix_from_pointer(2, 2, &(_z[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > i_i() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_i_i[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > x_i() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_x_i[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > y_i() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_y_i[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > z_i() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_z_i[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > i_x() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_i_x[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > i_y() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_i_y[0][0]));
        }

        static boost::numeric::ublas::matrix<std::complex<double> > i_z() {
          return boost::numeric::ublas::make_matrix_from_pointer(4, 4, &(_i_z[0][0]));
        }

        // TODO: Functions to calculate operators of any size

       private:
        // Most frequently used operators are hardcoded
        static const std::complex<double> _i[2][2];
        static const std::complex<double> _x[2][2];
        static const std::complex<double> _y[2][2];
        static const std::complex<double> _z[2][2];
        static const std::complex<double> _i_i[2][2]; // I Kron I
        static const std::complex<double> _x_i[2][2]; // X Kron I
        static const std::complex<double> _y_i[2][2]; // Y Kron I
        static const std::complex<double> _z_i[2][2]; // Z Kron I
        static const std::complex<double> _i_x[2][2]; // I Kron X
        static const std::complex<double> _i_y[2][2]; // I Kron Y
        static const std::complex<double> _i_z[2][2]; // I Kron Z
      };
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* INCLUDED_QITKAT_QUANTUM_MANAGER_NOISE_OPERATORS_H */
