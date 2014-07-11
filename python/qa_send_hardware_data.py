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
import SocketServer
import threading
import socket
from time import sleep
from random import randint
import struct

#This has to be outside the class
inputData = list()
received = [0]*1000

for i in range(1000):
  inputData.append(randint(0,3))

class qa_send_hardware_data(gr_unittest.TestCase):

  host = "localhost"
  port = 12345

  class TestTCPServer(SocketServer.StreamRequestHandler):
    timeout = 10
    def handle(self):
      global received
      temp = self.request.recv(1003)
      # We sent 100 flags, but we have 103 bytes, since there are 3 "counter" bytes at the beginning
      for i in range(3,len(received)+3):
        received[i-3] = struct.unpack("<B", temp[i])[0]

  def createServer(self):
    SocketServer.TCPServer.allow_reuse_address = True
    server = SocketServer.TCPServer((self.host, self.port), self.TestTCPServer)
    server.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    SocketServer.TCPServer.allow_reuse_address = True
    server.handle_request()

  def launchServer(self):
    thread = threading.Thread(target=self.createServer)
    thread.setDaemon(True)
    thread.start()

  def setUp(self):
    self.tb = gr.top_block()
    self.launchServer()

  def tearDown(self):
    self.tb = None

  def test_001(self):
    # Ensure our server is ready by waiting a second
    sleep(1)
    global inputData
    src0 = blocks.vector_source_b(inputData)
    v2s0 = blocks.vector_to_stream(gr.sizeof_char, 1)
    sendHardwareData = qitkat.send_hardware_data(self.host, self.port)
    self.tb.connect(src0, v2s0)
    self.tb.connect(v2s0, sendHardwareData)
    self.tb.run()
    global received
    self.assertEqual(received, inputData)

if __name__ == '__main__':
  gr_unittest.run(qa_send_hardware_data, "qa_send_hardware_data.xml")
