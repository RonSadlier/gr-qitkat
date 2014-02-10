#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2011 - 2014 Travis S. Humble - Oak Ridge National Laboratory
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
import random

class qa_ber_bf(gr_unittest.TestCase):
  def setUp(self):
    self.tb = gr.top_block()
    self.accuracy = 2

  def tearDown(self):
    self.tb = None

  def ber_calculate(self, src_data0, src_data1, exp_data, frame_length, bit_mask, is_almost):
    src0 = blocks.vector_source_b(src_data0)
    src1 = blocks.vector_source_b(src_data1)
    ber = qitkat.ber_bf(frame_length, bit_mask)
    # Data is sink
    data = blocks.vector_sink_f()
    self.tb.connect(src0, (ber, 0))
    self.tb.connect(src1, (ber, 1))
    self.tb.connect(ber, data)
    self.tb.run()
    result_data = data.data()
    if is_almost:
      for (exp_item, result_item) in zip(exp_data, result_data):
        self.assertAlmostEqual(exp_item, result_item, self.accuracy)
    else:
      self.assertEqual(exp_data, result_data)

  def test_001(self):
    # Frame length of 1, BER of 0.0, bitmask of 255
    src_data0 = (0, 1, 85, 170, 15, 255)
    src_data1 = (0, 1, 85, 170, 15, 255)
    expected_result = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 255, False)

  def test_002(self):
    # Frame length of 2, BER of 0.0, bitmask of 255
    src_data0 = (0, 1, 85, 170, 15, 255)
    src_data1 = (0, 1, 85, 170, 15, 255)
    expected_result = (0.0, 0.0, 0.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 255, False)

  def test_003(self):
    # Frame length of 1, BER of 0.0, bitmask of 7
    src_data0 = (0, 1, 2, 3, 4, 5)
    src_data1 = (0, 1, 2, 3, 4, 5)
    expected_result = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 7, False)

  def test_004(self):
    # Frame length of 2, BER of 0.0, bitmask of 7
    src_data0 = (0, 1, 2, 3, 4, 5)
    src_data1 = (0, 1, 2, 3, 4, 5)
    expected_result = (0.0, 0.0, 0.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 7, False)

  def test_005(self):
    # Frame length of 1, BER of 0.125, bitmask of 255
    src_data0 = (0, 1, 85, 170, 15, 255)
    src_data1 = (1, 3, 84, 171, 14, 254)
    expected_result = (0.125, 0.125, 0.125, 0.125, 0.125, 0.125)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 255, False)

  def test_006(self):
    # Frame length of 2, BER of 0.125, bitmask of 255
    src_data0 = (0, 1, 85, 170, 13, 255)
    src_data1 = (1, 3, 84, 171, 12, 254)
    expected_result = (0.125, 0.125, 0.125)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 255, False)

  def test_007(self):
    # Frame length of 1, BER of 0.25, bitmask of 15
    src_data0 = (0, 1, 85, 170, 15, 255)
    src_data1 = (1, 3, 84, 171, 14, 254)
    expected_result = (0.25, 0.25, 0.25, 0.25, 0.25, 0.25)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 15, False)

  def test_008(self):
    # Frame length of 2, BER of 0.25, bitmask of 15
    src_data0 = (0, 1, 85, 170, 15, 255)
    src_data1 = (1, 3, 84, 171, 13, 254)
    expected_result = (0.25, 0.25, 0.25)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 15, False)

  def test_009(self):
    # Frame length of 1, BER of 0.5, bitmask of 255
    src_data0 = (240, 85)
    src_data1 = (255, 255)
    expected_result = (0.5, 0.5)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 255, False)

  def test_010(self):
    # Frame length of 2, BER of 0.5, bitmask of 255
    src_data0 = (240, 85, 91, 51)
    src_data1 = (255, 255, 254, 255)
    expected_result = (0.5, 0.5)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 255, False)

  def test_011(self):
    # Frame length of 1, BER of 0.5, bitmask of 15
    src_data0 = (15, 10, 11, 7)
    src_data1 = (3, 15, 13, 2)
    expected_result = (0.5, 0.5, 0.5, 0.5)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 15, False)

  def test_012(self):
    # Frame length of 2, BER of 0.5, bitmask of 15
    src_data0 = (0, 15, 11, 7)
    src_data1 = (3, 3, 13, 2)
    expected_result = (0.5, 0.5)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 15, False)

  def test_013(self):
    # Frame length of 1, BER of 1.0, bitmask of 255
    src_data0 = (0, 170, 240, 221)
    src_data1 = (255, 85, 15, 34)
    expected_result = (1.0, 1.0, 1.0, 1.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 255, False)

  def test_014(self):
    # Frame length of 2, BER of 1.0, bitmask of 255
    src_data0 = (0, 170, 240, 221)
    src_data1 = (255, 85, 15, 34)
    expected_result = (1.0, 1.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 255, False)

  def test_015(self):
    # Frame length of 1, BER of 1.0, bitmask of 15
    src_data0 = (0, 10, 3, 1)
    src_data1 = (15, 5, 12, 14)
    expected_result = (1.0, 1.0, 1.0, 1.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 1, 15, False)

  def test_016(self):
    # Frame length of 2, BER of 1.0, bitmask of 15
    src_data0 = (0, 10, 3, 1)
    src_data1 = (15, 5, 12, 14)
    expected_result = (1.0, 1.0)
    self.ber_calculate(src_data0, src_data1, expected_result, 2, 15, False)

  def test_017(self):
    # Frame length of 15000, BER of 0.17, bitmask of 255
    # Look for the average BER over all samples
    num_items = 15000
    src_data0 = []
    src_data1 = []
    for i in range(num_items):
      byte = random.randint(0,255)
      src_data0.append(byte)
      # Perform errors at a rate of 0.17
      if(random.randint(0,99) < 17):
        src_data1.append(byte ^ 255)
      else:
        src_data1.append(byte)
    expected_result = (0.17,)
    self.ber_calculate(src_data0, src_data1, expected_result, num_items, 255, True)

if __name__ == '__main__':
    gr_unittest.run(qa_ber_bf, "qa_ber_bf.xml")
