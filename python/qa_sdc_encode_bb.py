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

class qa_sdc_encode_bb(gr_unittest.TestCase):

  def setUp(self):
    self.tb = gr.top_block ()

  def tearDown(self):
    self.tb = None

  def test_001_n2(self):
    # The number of input bytes must be in multiples of 1
    # (00000000, 00000001, 01010101, 10101010, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 255)
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 0, 0, 3, 3, 3, 3)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(2)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_002_n3(self):
    # The number of input bytes must be in multiples of 3
    # (00000000, 00000001, 01010101, 10101010, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 255)
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (5, 2, 5, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 4, 2, 5)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(3)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_003_n4(self):
    # The number of input bytes must be in multiples of 1
    # (00000000, 00000001, 01010101, 10101010, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 255)
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (0, 0, 1, 0, 5, 5, 10, 10, 15, 0, 15, 15)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(4)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_004_n5(self):
    # The number of input bytes must be in multiples of 1
    # (00000000, 00000001, 01010101, 10101010, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 255)
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (0, 0, 1, 0, 5, 5, 10, 10, 15, 0, 15, 15)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(5)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_005_n6(self):
    # The number of input bytes must be in multiples of 5
    # (00000000, 00000001, 01010101, 10101010, 00001111, 01010101, 10101010, 00001111, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 85, 170, 15, 15, 255) 
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (15, 16, 10, 11, 21, 0, 0, 0, 31, 31, 3, 30, 0, 21, 22, 10)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(6)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_006_n7(self):
    # The number of input bytes must be in multiples of 5
    # (00000000, 00000001, 01010101, 10101010, 00001111, 01010101, 10101010, 00001111, 00001111, 11111111)
    src_data = (0, 1, 85, 170, 15, 85, 170, 15, 15, 255) 
    # For output, bit pair ordering is from right to left, while the bit ordering is from left to right
    # So for example (if n=2): (00000001) => (01,00,00,00)
    expected_result = (15, 16, 10, 11, 21, 0, 0, 0, 31, 31, 3, 30, 0, 21, 22, 10)
    src = blocks.vector_source_b(src_data)
    sdc_encode = qitkat.sdc_encode_bb(7)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, sdc_encode)
    self.tb.connect(sdc_encode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

if __name__ == '__main__':
  gr_unittest.run(qa_sdc_encode_bb, "qa_sdc_encode_bb.xml")
