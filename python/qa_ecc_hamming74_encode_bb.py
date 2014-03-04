#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2014 - 2014 Ronald Sadlier - Oak Ridge National Laboratory
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

class qa_ecc_hamming74_encode_bb(gr_unittest.TestCase):

  def setUp(self):
    self.tb = gr.top_block()

  def tearDown(self):
    self.tb = None

  def test_001(self):
    # Lower half of the input byte: 0000xxxx
    src_data = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
    # Output Source from: www.demonstrations.wolfram.com/TheHamming74Code/
    expected_result = (0, 0, 105, 0, 42, 0, 67, 0, 76, 0, 37, 0, 102, 0, 15, 0,
      112, 0, 25, 0, 90, 0, 51, 0, 60, 0, 85, 0, 22, 0, 127, 0)
    src = blocks.vector_source_b(src_data)
    hamming74_encode = qitkat.ecc_hamming74_encode_bb()
    dst = blocks.vector_sink_b()
    self.tb.connect(src, hamming74_encode)
    self.tb.connect(hamming74_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_002(self):
    # Upper half of the input byte: xxxx0000
    src_data = (0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240)
    # Output Source from: www.demonstrations.wolfram.com/TheHamming74Code/
    expected_result = (0, 0, 0, 105, 0, 42, 0, 67, 0, 76, 0, 37, 0, 102, 0, 15, 0, 112,
      0, 25, 0, 90, 0, 51, 0, 60, 0, 85, 0, 22, 0, 127)
    src = blocks.vector_source_b(src_data)
    hamming74_encode = qitkat.ecc_hamming74_encode_bb()
    dst = blocks.vector_sink_b()
    self.tb.connect(src, hamming74_encode)
    self.tb.connect(hamming74_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_003(self):
    # Mixed
    # 17: 00010001; 74: 01001010; 92: 01011100; 125: 01111101; 192: 11000000; 241: 11110001; 255: 11111111 
    src_data = (17, 74, 92, 125, 192, 241, 255)
    # Output Source from: www.demonstrations.wolfram.com/TheHamming74Code/
    expected_result = (105, 105, 90, 76, 60, 37, 85, 15, 0, 60, 105, 127, 127, 127)
    src = blocks.vector_source_b(src_data)
    hamming74_encode = qitkat.ecc_hamming74_encode_bb()
    dst = blocks.vector_sink_b()
    self.tb.connect(src, hamming74_encode)
    self.tb.connect(hamming74_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

if __name__ == '__main__':
  gr_unittest.run(qa_ecc_hamming74_encode_bb, "qa_ecc_hamming74_encode_bb.xml")
