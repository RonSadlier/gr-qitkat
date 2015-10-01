/* -*- c++ -*- */
/* 
 * Copyright 2011-2013 Travis S. Humble - Oak Ridge National Laboratory
 * Copyright 2013-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

#ifndef INCLUDED_QITKAT_ENTROPY_BF_IMPL_H
#define INCLUDED_QITKAT_ENTROPY_BF_IMPL_H

#include <qitkat/entropy_bf.h>

namespace gr {
	namespace qitkat {
		/**
		 * \brief todo.
		 */
		class entropy_bf_impl : public entropy_bf {
		 public:
			entropy_bf_impl(int num_items);
			~entropy_bf_impl();
			
			void forecast(int noutput_items, gr_vector_int &ninput_items_required);
			int general_work(int noutput_items,
					gr_vector_int &ninput_items,
					gr_vector_const_void_star &input_items,
					gr_vector_void_star &output_items);
		
		 private:
			/**
			 * Number of items to use for entropy calculation.
			 */
			unsigned int d_num_items;
			
			float single_entropy(void* in, const std::size_t size);
			float joint_entropy(void* in0, void* in1, const std::size_t size);
		};
	}
}

#endif

