/* -*- c++ -*- */
/*
 * Copyright 2014-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_FILTER_TIMESTAMPS_H
#define INCLUDED_QITKAT_FILTER_TIMESTAMPS_H

#include <qitkat/api.h>
#include <gnuradio/block.h>

namespace gr {
	namespace qitkat {
		/*!
		 * \brief Remove all data except raw timestamps.
		 * \ingroup qitkat
		 */
		class QITKAT_API filter_timestamps : virtual public gr::block {
		 public:
			typedef boost::shared_ptr<filter_timestamps> sptr;

			/*!
			 * \brief Return a shared_ptr to a new instance of qitkat::filter_timestamps.
			 *
			 * To avoid accidental use of raw pointers, qitkat::filter_timestamps's
			 * constructor is in a private implementation
			 * class. qitkat::filter_timestamps::make is the public interface for
			 * creating new instances.
			 */
			static sptr make();
		};
	}
}

#endif
