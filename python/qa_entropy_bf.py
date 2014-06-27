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

class qa_entropy_bf(gr_unittest.TestCase):

  rounddigits = 3

  def setUp(self):
    self.tb = gr.top_block()
    self.num_items = 15000
    self.window = (self.num_items/2)
    self.precision = 3

  def tearDown(self):
    self.tb = None

  def entropy_single(self, src_vector, expected_entropy, window):
    src = blocks.vector_source_b(src_vector)
    v2s = blocks.vector_to_stream(gr.sizeof_char, 1)
    entropy = qitkat.entropy_bf(window)
    data = blocks.vector_sink_f()
    self.tb.connect(src, v2s)
    self.tb.connect(v2s, entropy)
    self.tb.connect(entropy, data)
    self.tb.run()
    obs = data.data()
    exp = expected_entropy
    for i in range(len(obs)):
      self.assertAlmostEqual(exp, round(obs[i], self.rounddigits), self.precision)

  def entropy_joint(self, src_vector0, src_vector1, expected_entropy, window):
    src0 = blocks.vector_source_b(src_vector0)
    src1 = blocks.vector_source_b(src_vector1)
    v2s0 = blocks.vector_to_stream(gr.sizeof_char, 1)
    v2s1 = blocks.vector_to_stream(gr.sizeof_char, 1)
    entropy = qitkat.entropy_bf(window)
    data = blocks.vector_sink_f()
    self.tb.connect(src0, v2s0)
    self.tb.connect(v2s0, (entropy, 0))
    self.tb.connect(src1, v2s1)
    self.tb.connect(v2s1, (entropy, 1))
    self.tb.connect(entropy, data)
    self.tb.run()
    obs = data.data()
    exp = expected_entropy
    for i in range(len(obs)):
      self.assertAlmostEqual(exp,round(obs[i], self.rounddigits), self.precision)

  def test_001(self):
    # Test for alternating sequence
    src_vector = []
    for i in range((self.num_items/2)):
      src_vector.append(0)
      src_vector.append(1)
    expected_entropy = 1.0
    self.entropy_single(src_vector, expected_entropy, self.window)

  def test_002(self):
    # Test for constant sequence of 0
    src_vector = []
    for i in range((self.num_items)):
      src_vector.append(0)
    expected_entropy = 0.0
    self.entropy_single(src_vector, expected_entropy, self.window)


  def test_003(self):
    # Test for constant sequence of 1
    src_vector = []
    for i in range((self.num_items)):
      src_vector.append(1)
    expected_entropy = 0.0
    self.entropy_single(src_vector, expected_entropy, self.window)


  def test_004(self):
    # Test for perfectly correlated pair
    src_vector0 = []
    src_vector1 = []
    for i in range(self.num_items):
      src_vector0.append(1)
      src_vector1.append(src_vector0[i])
    expected_entropy = 0.0
    self.entropy_joint(src_vector0, src_vector1, expected_entropy, self.window)


  def test_005(self):
    # Test for perfectly uncorrelated pair
    src_vector0 = []
    src_vector1 = []
    for i in range(self.num_items):
      src_vector0.append(random.randint(0,1))
      src_vector1.append(random.randint(0,1))
    expected_entropy = 1.0
    self.entropy_joint(src_vector0, src_vector1, expected_entropy, self.window)

  def test_006_qitkat (self):
    # Test for perfectly anti-correlated pair
    src_vector0 = []
    src_vector1 = []
    for i in range(self.num_items):
      src_vector0.append(1)
      src_vector0.append(0)
    expected_entropy = 1.0
    self.entropy_joint(src_vector0, src_vector1, expected_entropy, self.window)

if __name__ == '__main__':
  gr_unittest.run(qa_entropy_bf, "qa_entropy_bf.xml")
