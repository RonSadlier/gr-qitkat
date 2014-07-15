#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2014 Ronald Sadlier - Oak Ridge National Laboratory
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import qitkat_swig as qitkat

class qa_ecc_hamming74_decode_bb(gr_unittest.TestCase):

  def setUp(self):
    self.tb = gr.top_block()

  def tearDown(self):
    self.tb = None

  def test_001(self):
    # Input Source from: www.demonstrations.wolfram.com/TheHamming74Code/
    src_data = (0, 0, 105, 0, 42, 0, 67, 0, 76, 0, 37, 0, 102, 0, 15, 0,
      112, 0, 25, 0, 90, 0, 51, 0, 60, 0, 85, 0, 22, 0, 127, 0, 105, 105,
      90, 76, 60, 37, 85, 15, 0, 60, 105, 127, 127, 127)
    # Output
    # 1: 00000001, 2: 00000010 ... 15: 00001111
    # 17: 00010001; 74: 01001010; 92: 01011100; 125: 01111101; 192: 11000000; 241: 11110001; 255: 11111111
    expected_result = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 74, 92, 125, 192, 241, 255)
    src = blocks.vector_source_b(src_data)
    hamming74_decode = qitkat.ecc_hamming74_decode_bb()
    dst = blocks.vector_sink_b()
    self.tb.connect(src, hamming74_decode)
    self.tb.connect(hamming74_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_002(self):
    # 1 Bit-flip error per output byte
    # Input Source from: www.demonstrations.wolfram.com/TheHamming74Code/
    src_data = (0, 0, 97, 0, 43, 0, 3, 0, 77, 0, 39, 0, 102, 1, 31, 0,
      112, 1, 24, 0, 91, 0, 55, 0, 60, 0, 84, 0, 23, 0, 126, 0, 104, 105,
      90, 77, 60, 39, 85, 31, 0, 60, 105, 63, 127, 119)
    # Output
    # 1: 00000001, 2: 00000010 ... 15: 00001111
    # 17: 00010001; 74: 01001010; 92: 01011100; 125: 01111101; 192: 11000000; 241: 11110001; 255: 11111111
    expected_result = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 74, 92, 125, 192, 241, 255)
    src = blocks.vector_source_b(src_data)
    hamming74_decode = qitkat.ecc_hamming74_decode_bb()
    dst = blocks.vector_sink_b()
    self.tb.connect(src, hamming74_decode)
    self.tb.connect(hamming74_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

if __name__ == '__main__':
  gr_unittest.run(qa_ecc_hamming74_decode_bb, "qa_ecc_hamming74_decode_bb.xml")
