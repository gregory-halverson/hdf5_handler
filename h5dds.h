////////////////////////////////////////////////////////////////////////////////
/// \file h5dds.h
/// \brief Data structure and retrieval processing header
///
/// This file is part of h5_dap_handler, A C++ implementation of the DAP handler
/// for HDF5 data.
///    
/// It defines functions that describe and retrieve group/dataset from HDF5 files.
/// 
/// \author Hyo-Kyung Lee <hyoklee@hdfgroup.org>
/// \author Muqun Yang <ymuqun@hdfgroup.org>
///
/// Copyright (C) 2007	HDF Group, Inc.
///
/// Copyright (C) 1999 National Center for Supercomputing Applications.
///
/// All rights reserved.
////////////////////////////////////////////////////////////////////////////////

/// Maximum size of error message buffer.
#define MAX_ERROR_MESSAGE 512

#include <H5Gpublic.h>
#include <H5Fpublic.h>
#include <H5Ipublic.h>
#include <H5Tpublic.h>
#include <H5Spublic.h>
#include <H5Apublic.h>
#include <H5public.h>

#include "cgi_util.h" 
#include "DDS.h"
#include "DODSFilter.h"
#include "common.h"

#include "HDF5Int32.h"
#include "HDF5UInt32.h"
#include "HDF5UInt16.h"
#include "HDF5Int16.h"
#include "HDF5Byte.h"
#include "HDF5Array.h"
#include "HDF5Str.h"
#include "HDF5Float32.h"
#include "HDF5Float64.h"
#include "HDF5Grid.h"
#include "HDF5Url.h"

using namespace libdap ;

#if 0
#include "h5util.h"
#endif

bool   depth_first(hid_t, char *, DDS &, const char *);
string return_type(hid_t type);
void   read_objects(DDS &dds, const string &varname, const string& filename);
#ifdef SHORT_PATH
string get_short_name(string name);
#endif

