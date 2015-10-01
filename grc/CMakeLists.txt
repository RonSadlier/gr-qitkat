# 
# Copyright 2013-2015 Ronald J. Sadlier - Oak Ridge National Laboratory
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

install(FILES
	qitkat_sdc_encode_bb.xml
	qitkat_sdc_decode_bb.xml
	qitkat_ber_bf.xml
	qitkat_bsc_bb.xml
	qitkat_entropy_bf.xml
	qitkat_terminal_display_b.xml
	qitkat_ecc_bit_permute_bb.xml
	qitkat_ecc_repetition_encode_bb.xml
	qitkat_ecc_repetition_decode_bb.xml
	qitkat_ecc_hamming74_encode_bb.xml
	qitkat_ecc_hamming74_decode_bb.xml
	qitkat_ecc_golay2412_encode_bb.xml
	qitkat_ecc_golay2412_decode_bb.xml
	qitkat_get_hardware_data.xml
	qitkat_filter_timestamps.xml
	qitkat_send_hardware_data.xml
	qitkat_extract_hardware_sdc.xml
	qitkat_qrng_source_i.xml DESTINATION share/gnuradio/grc/blocks
)
