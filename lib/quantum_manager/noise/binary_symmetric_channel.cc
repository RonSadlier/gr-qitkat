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

#include "binary_symmetric_channel.h"
#include <vector>

using namespace std;

namespace gr {
  namespace qitkat {
    namespace quantum_manager {
      namespace noise {

        void binary_symmetric_channel::set_raw_p(unsigned char* data, unsigned int length) {
          set_p(vector<double>(data, data+length));
        }

      } // namspace noise
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
