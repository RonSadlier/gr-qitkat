/* -*- c++ -*- */

#define QITKAT_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "qitkat_swig_doc.i"

%{
#include "qitkat/sdc_encode_bb.h"
#include "qitkat/sdc_decode_bb.h"
#include "qitkat/ber_bf.h"
#include "qitkat/bsc_bb.h"
#include "qitkat/entropy_bf.h"
#include "qitkat/terminal_display_b.h"
#include "qitkat/ecc_repetition_encode_bb.h"
#include "qitkat/ecc_repetition_decode_bb.h"
#include "qitkat/ecc_hamming74_encode_bb.h"
%}


%include "qitkat/sdc_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, sdc_encode_bb);
%include "qitkat/sdc_decode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, sdc_decode_bb);
%include "qitkat/ber_bf.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, ber_bf);
%include "qitkat/bsc_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, bsc_bb);
%include "qitkat/entropy_bf.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, entropy_bf);
%include "qitkat/terminal_display_b.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, terminal_display_b);
%include "qitkat/ecc_repetition_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, ecc_repetition_encode_bb);
%include "qitkat/ecc_repetition_decode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, ecc_repetition_decode_bb);
%include "qitkat/ecc_hamming74_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, ecc_hamming74_encode_bb);
