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

#ifndef HEADER_QUANTUM_MANAGER_QUANTUM_MANAGER_SERVER_H
#define HEADER_QUANTUM_MANAGER_QUANTUM_MANAGER_SERVER_H

#include "quantum_manager.h"
#include "state/state_map.h"
#include "noise/noise_map.h"

#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace gr {
  namespace qitkat {
    namespace quantum_manager {

      /**
       * A packet is what is sent between client and server.
       * Header:
       * [0] = parameter flag
       * [1] = channel id
       * [2-3] = body length
       *
       * parameter flag options:
       * 0 - create managed qudits
       * 10 - projective bell measurement
       * 255 - initialization request or server response
       * NOTE: a parameter flag of 255 indicates an initialization request from a client
       * or a response from a server.
       */
      struct packet {
       public:
        const static unsigned short header_length = 4;
        const static unsigned short max_body_length = 1024;

        packet() : body_length_(0) {
          memset(data_, 0, header_length + max_body_length);
        }

        unsigned char* data() {
          return data_;
        }

        unsigned short data_length() {
          return header_length + body_length_;
        }

        unsigned char parameter_flag() {
          return data_[0];
        }

        void set_parameter_flag(unsigned char parameter_flag) {
          data_[0] = parameter_flag;
        }

        unsigned char channel_id() {
          return data_[1];
        }

        void set_channel_id(unsigned char channel_id) {
          data_[1] = channel_id;
        }

        unsigned char* body() {
          return data_ + header_length;
        }

        unsigned short body_length() {
          return body_length_;
        }

        void set_header_body_length(unsigned short length) {
          data_[2] = length;
          data_[3] = length << 8;
        }

        bool decode_header() {
          // Pack chars into short to determine body length.
          body_length_ = (data_[2] << 8) + data_[3];
          if (body_length_ > max_body_length) {
            body_length_ = 0;
            return false;
          }
          return true;
        }

        std::vector<int> decode_body() {
          std::vector<int> returnbody;
          if(body_length_ == 0) {
            // Header was not decoded yet
            std::cerr << "Header was not decoded on packet before decoding body" << std::endl;
            return returnbody;
          } else {
            //return *channel_id(), std::vector<int> &returnbody)
            return returnbody;
          }
        }

        void clear() {
          memset(data_, 0, header_length + max_body_length);
          body_length_ = 0;
        }

       private:
        unsigned char data_[header_length + max_body_length];
        unsigned short body_length_;
      };

      /**
       * An individual session between client and server.
       */
      struct session {
       public:
        boost::asio::ip::tcp::socket socket;

        session(boost::asio::io_service& io_service) : socket(io_service) {
        }

        /**
         * Start the server listening for data.
         */
        void start() {
          boost::asio::async_read(socket,
            boost::asio::buffer(incoming_packet.data(), packet::header_length),
              boost::bind(&session::handle_read_header, this,
              boost::asio::placeholders::error));
        }

        /**
         * Read the header from the packet and begin to read the body.
         */
        void handle_read_header(const boost::system::error_code& error) {
          if(!error && incoming_packet.decode_header()) {
            // We read the header, now we read the body.
            boost::asio::async_read(socket,
              boost::asio::buffer(incoming_packet.data(), incoming_packet.body_length()),
              boost::bind(&session::handle_read_body, this,
                boost::asio::placeholders::error));
          } else {
             std::cerr << "Error: Could not read incoming packet header." << std::endl;
            delete this;
          }
        }

        /**
         * Read the body and process the request accordingly.
         */
        void handle_read_body(const boost::system::error_code& error) {
          if(!error) {
            outgoing_packet.clear();
            // We read the body, now we perform the proper actions and return the results
            // to the client.

            if(incoming_packet.parameter_flag() == 255) {
              // Initialization request

              /* Our initialization data is within the body of our packet.
               * It should look something like this:
               * [HEADER]
               * [0] = statetype
               * [1] = n
               * [2] = m
               * [3] = noisemodel
               * [4:n^2] = noiseparameters
               */
              state::state_type* state_type = state::get_statetype(incoming_packet.body()[0]);
              state_type->set_state_size(incoming_packet.body()[1], incoming_packet.body()[2]);
              noise::noise_type* noise_type = noise::get_noisetype(incoming_packet.body()[3]);
              noise_type->set_raw_p(&incoming_packet.body()[4], pow(incoming_packet.body()[1], incoming_packet.body()[2]));

              quantum_manager::instance()->create_channel(incoming_packet.channel_id(), state_type, noise_type);
              
            } else {
              // Normal request

              int unit = quantum_manager::instance()->get_channel(incoming_packet.channel_id())->state_type()->get_state_byte_size();
              int div = incoming_packet.body_length() / unit;

              switch(incoming_packet.parameter_flag()) {
                case 0:
                  // Create a managed qudit.
                  if (div*unit != incoming_packet.body_length()) {
                    std::cerr << "Incoming packet body length mismatch to state size" << std::endl;                
                  } else {
                    std::vector<int> generated_ids;
                    for(int i = 0; i < incoming_packet.body_length(); i+=unit) {
                      generated_ids.push_back(quantum_manager::instance()->
                        create_managed_qudits(incoming_packet.channel_id(), &incoming_packet.body()[i]));

                      // Add our data into our outgoing packet
                      char *pid = (char*)&generated_ids[i];
                      outgoing_packet.body()[i*4+0] = pid[0];
                      outgoing_packet.body()[i*4+1] = pid[1];
                      outgoing_packet.body()[i*4+2] = pid[2];
                      outgoing_packet.body()[i*4+3] = pid[3];
                    };

                    outgoing_packet.set_header_body_length((unsigned short)generated_ids.size());
                    outgoing_packet.set_parameter_flag(255);
                    outgoing_packet.set_channel_id(incoming_packet.channel_id());
                  }
                  break;
                case 10:
                  // Projective Bell Measurement
                  // Size of int in GR is 4.
                  if(incoming_packet.body_length()/4 == (int)(incoming_packet.body_length()/4)) {
                    std::cerr << "Incoming packet body length mismatch to id size" << std::endl;
                  } else {
                    std::vector<unsigned char> outgoing;

                    for(int current = 4; current < incoming_packet.body_length()/4; current += 4) {
                      outgoing.push_back(quantum_manager::instance()->
                          projective_bell_measurement(incoming_packet.channel_id(), *(unsigned int*)&incoming_packet.body()[current]));
                    };

                    outgoing[0] = 255;
                    outgoing[1] = incoming_packet.channel_id();
                    outgoing[2] = incoming_packet.body_length()/4 - (unsigned short)packet::header_length;
                    outgoing[3] = incoming_packet.body_length()/4 - (unsigned short)packet::header_length << 8; 
                  }
                  break;
                default:
                  std::cerr << "Unkown parameter flag in incoming_packet" << std::endl;
                  break;
              }

              // Write our outgoing packet
              boost::asio::async_write(socket,
                  boost::asio::buffer(outgoing_packet.data(), outgoing_packet.data_length()),
                  boost::bind(&session::handle_write, this,
                      boost::asio::placeholders::error));
            }

            incoming_packet.clear();
          } else {
            delete this;
          }
        }

        /**
         * Start reading again.
         */
        void handle_write(const boost::system::error_code& error) {
          if(!error) {
            boost::asio::async_read(socket,
              boost::asio::buffer(incoming_packet.data(), packet::header_length),
                boost::bind(&session::handle_read_header, this,
                boost::asio::placeholders::error));
          } else {
            delete this;
          }
        }

       private:
        // These packets are reused during the session if we need to manage multiple packets.
        packet incoming_packet;
        packet outgoing_packet;
      };


      /**
       * This server acts as an interface to the quantum simulation server.
       */
      class quantum_manager_server {
       public:
        quantum_manager_server(unsigned short listenport);
        ~quantum_manager_server() {}

        void listen();
        void handle_accept(session* new_session, const boost::system::error_code& error);
        void start_accept();

       private:
        unsigned short listenport;

        void listen_for_exit();

        // Boost networking things
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor;
      };

    } // namespace quantum_manager
  } // namespace qitkat
} // namespace gr
#endif /* HEADER_QUANTUM_MANAGER_QUANTUM_MANAGER_SERVER_H */
