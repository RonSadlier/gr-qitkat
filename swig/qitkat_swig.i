/* -*- c++ -*- */

#define QITKAT_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "qitkat_swig_doc.i"

%{
#include "qitkat/sdc_encode_bb.h"
%}


%include "qitkat/sdc_encode_bb.h"
GR_SWIG_BLOCK_MAGIC2(qitkat, sdc_encode_bb);
