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

class qa_ecc_repetition_decode_bb(gr_unittest.TestCase):

  def setUp(self):
    self.tb = gr.top_block()

  def tearDown(self):
    self.tb = None

  def test_001(self):
    # Repetition = 1, no errors
    src_data = (0, 1, 255, 74, 23)
    expected_result = (0, 1, 255, 74, 23)
    src = blocks.vector_source_b(src_data)
    repetition_decode = qitkat.ecc_repetition_decode_bb(1)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, repetition_decode)
    self.tb.connect(repetition_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_002(self):
    # Repetition = 2 (even case), no errors
    src_data = (0, 0, 1, 1, 255, 255, 74, 74, 23, 23)
    expected_result = (0, 1, 255, 74, 23)
    src = blocks.vector_source_b(src_data)
    repetition_decode = qitkat.ecc_repetition_decode_bb(2)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, repetition_decode)
    self.tb.connect(repetition_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_003(self):
    # Repetition = 3 (odd case), no errors
    src_data = (0, 0, 0, 1, 1, 1, 255, 255, 255, 74, 74, 74, 23, 23, 23)
    expected_result = (0, 1, 255, 74, 23)
    src = blocks.vector_source_b(src_data)
    repetition_decode = qitkat.ecc_repetition_decode_bb(3)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, repetition_decode)
    self.tb.connect(repetition_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

  def test_004(self):
    # Repetition = 3 (odd case), 1 error each
    src_data = (0, 0, 5, 1, 45, 1, 255, 12, 255, 34, 74, 74, 12, 23, 23)
    expected_result = (0, 1, 255, 74, 23)
    src = blocks.vector_source_b(src_data)
    repetition_decode = qitkat.ecc_repetition_decode_bb(3)
    dst = blocks.vector_sink_b()
    self.tb.connect(src, repetition_decode)
    self.tb.connect(repetition_decode, dst)
    self.tb.run()
    result_data = dst.data()
    self.assertEqual(expected_result, result_data)

if __name__ == '__main__':
  gr_unittest.run(qa_ecc_repetition_decode_bb, "qa_ecc_repetition_decode_bb.xml")
