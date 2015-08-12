# 
# Copyright 2014-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

########################################################################
# Install public header files
########################################################################
install(FILES
	api.h
	sdc_encode_bb.h
	sdc_decode_bb.h
	ber_bf.h
	bsc_bb.h
	entropy_bf.h
	terminal_display_b.h
	ecc_repetition_encode_bb.h
	ecc_repetition_decode_bb.h
	ecc_hamming74_encode_bb.h
	ecc_hamming74_decode_bb.h
	ecc_golay2412_encode_bb.h
	ecc_golay2412_decode_bb.h
	get_hardware_data.h
	filter_timestamps.h
	send_hardware_data.h
	extract_hardware_sdc.h DESTINATION include/qitkat
)
