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

#ifndef INCLUDED_QITKAT_EXTRACT_HARDWARE_SDC_H
#define INCLUDED_QITKAT_EXTRACT_HARDWARE_SDC_H

#include <qitkat/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
	namespace qitkat {
		/*!
		 * \brief Extract SDC flags from hardware data returned.
		 * \ingroup qitkat
		 */
		class QITKAT_API extract_hardware_sdc : virtual public gr::sync_decimator {
		 public:
			typedef boost::shared_ptr<extract_hardware_sdc> sptr;

			/*!
			 * \brief Return a shared_ptr to a new instance of qitkat::extract_hardware_sdc.
			 *
			 * To avoid accidental use of raw pointers, qitkat::extract_hardware_sdc's
			 * constructor is in a private implementation
			 * class. qitkat::extract_hardware_sdc::make is the public interface for
			 * creating new instances.
			 */
			static sptr make();
		};
	}
}

#endif
