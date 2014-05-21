/* -*- c++ -*- */
/* 
 * Copyright 2013-2014 Ronald Sadlier - Oak Ridge National Laboratory
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "quantum_manager_server.h"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

namespace gr {
  namespace qitkat {
    namespace quantum_manager {

      quantum_manager_server::quantum_manager_server(unsigned short listenport)
        : listenport(listenport), acceptor(io_service, tcp::endpoint(tcp::v4(), listenport)) {
      }

      typedef boost::shared_ptr<tcp::socket> socket_ptr;

      void quantum_manager_server::start_accept() {
        gr::qitkat::quantum_manager::session* new_session = new session(io_service);
          acceptor.async_accept(new_session->socket,
            boost::bind(&quantum_manager_server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
      }

      void quantum_manager_server::handle_accept(session* new_session, const boost::system::error_code& error) {
        if(!error) {
          new_session->start();
        } else {
          delete new_session;
        }
        start_accept();
      }

      void quantum_manager_server::listen() {
        std::cout << "Entering listen()" << std::endl;

        // Create exit listen thread
        boost::thread exitlistenThread(boost::bind(&quantum_manager_server::listen_for_exit, this));

        try {
          std::cout << "Initializing Server..." << std::endl;
          // Setup our server	
          socket_ptr sock(new tcp::socket(io_service));
          start_accept();
          io_service.run();
        } catch(std::exception& e) {
          std::cerr << "Error: " << e.what() << std::endl;
        }
      }

      void quantum_manager_server::listen_for_exit() {
        std::cout << "Enter 'c' to close" << std::endl;
        char input;
        do {
          input = getchar();
        } while (input != 'c');
        std::cout << "Closing..." << std::endl;
        exit(0);
      }
    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
