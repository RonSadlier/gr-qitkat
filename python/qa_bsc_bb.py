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

class qa_bsc_bb(gr_unittest.TestCase):

    def setUp(self):
      self.tb = gr.top_block()
      self.num_items = 10000
      self.accuracy = 2

    def tearDown(self):
      self.tb = None

    def bsc_compare(self, src_data, error_rate, bit_mask):
      src = blocks.vector_source_b(src_data)
      bsc = qitkat.bsc_bb(error_rate, 1, bit_mask)
      # Data is sink
      data = blocks.vector_sink_b()
      self.tb.connect(src, bsc)
      self.tb.connect(bsc, data)
      self.tb.run()
    
      # Compute bit error rate
      ber = 0
      for i in range(len(data.data())):
        ber = ber + ((src_data[i] ^ data.data()[i]) & bit_mask)
      # Observed error rate
      obs = (1.0*ber)/(len(src_data)*bit_mask)
      # Expected error rate
      self.assertAlmostEqual(obs, error_rate, self.accuracy)

    def test_001_qitkat(self):
      # Error rate of 0.0, bit mask of 255
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.0, 255)

    def test_002_qitkat(self):
      # Error rate of 1.0, bit mask of 255
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 1.0, 255)

    def test_003_qitkat (self):
      # Error rate of 0.5, bit mask of 255
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.5, 255)


    def test_004_qitkat(self):
      # Error rate of 0.17, bit mask of 255
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.17, 255)

    def test_005_qitkat(self):
      # Error rate of 0.0, bit mask of 63
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.0, 63)

    def test_006_qitkat(self):
      # Error rate of 1.0, bit mask of 63
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 1.0, 63)

    def test_007_qitkat (self):
      # Error rate of 0.5, bit mask of 63
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.5, 63)

    def test_008_qitkat(self):
      # Error rate of 0.17, bit mask of 63
      src = []
      for i in range(self.num_items):
        src.append(random.randint(0,1))
      self.bsc_compare(src, 0.17, 63)

if __name__ == '__main__':
    gr_unittest.run(qa_bsc_bb, "qa_bsc_bb.xml")
