/* -*- c++ -*- */
/*
 * Copyright 2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_RECEIVE_MESSAGE_B_H
#define INCLUDED_QITKAT_RECEIVE_MESSAGE_B_H

#include <qitkat/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
	namespace qitkat {
		/*!
		 * \brief \todo
		 * \ingroup qitkat
		 *
		 */
		class QITKAT_API receive_message_b : virtual public gr::sync_block {
		 public:
			typedef boost::shared_ptr<receive_message_b> sptr;
			
			/*!
			 * \brief Return a shared_ptr to a new instance of qitkat::receive_message_b.
			 *
			 * To avoid accidental use of raw pointers, qitkat::receive_message_b's
			 * constructor is in a private implementation
			 * class. qitkat::receive_message_b::make is the public interface for
			 * creating new instances.
			 */
			static sptr make(const std::string endpoint,
					const unsigned int timeout, 
					const unsigned int receivedMax);
		};
	}
}

#endif
