// This file is part of the hdf5_handler implementing for the CF-compliant
// Copyright (c) 2011-2016 The HDF Group, Inc. and OPeNDAP, Inc.
//
// This is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This software is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.
// You can contact The HDF Group, Inc. at 1800 South Oak Street,
// Suite 203, Champaign, IL 61820  

/////////////////////////////////////////////////////////////////////////////
/// \file HDFEOS5CFMissNonLLCVArray.cc
/// \brief The implementation of the retrieval of the missing lat/lon values for HDFEOS5 products
///
/// \author Kent Yang <myang6@hdfgroup.org>
///
/// Copyright (C) 2011-2016 The HDF Group
///
/// All rights reserved.

#include "config_hdf5.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <BESDebug.h>
#include "InternalErr.h"

#include "HDFEOS5CFMissNonLLCVArray.h"
#include "HDF5RequestHandler.h"

BaseType *HDFEOS5CFMissNonLLCVArray::ptr_duplicate()
{
    return new HDFEOS5CFMissNonLLCVArray(*this);
}

bool HDFEOS5CFMissNonLLCVArray::read()
{
    BESDEBUG("h5","Coming to HDFEOS5CFMissNonLLCVArray read "<<endl);

    // Don't use cache since the calculation is fairly small.
    read_data_NOT_from_mem_cache(false,NULL);
#if 0
    if(NULL == HDF5RequestHandler::get_srdata_mem_cache())                                          
        read_data_NOT_from_mem_cache(false,NULL);                                                   
    else {                                                                                          
        // Notice for this special fake variable case, we just use the info. from DAP.
        // dataset() is the file name and name() is the HDF5 unique var name.
        string cache_key = dataset() + name();
        handle_data_with_mem_cache(H5INT32,tnumelm,1,cache_key);             
    }
#endif
 
    return true;
}

void HDFEOS5CFMissNonLLCVArray::read_data_NOT_from_mem_cache(bool /*add_cache*/, void* /*buf*/)
{
    BESDEBUG("h5","Coming to HDFEOS5CFMissNonLLCVArray: read_data_NOT_from_mem_cache "<<endl);
    write_nature_number_buffer(rank,tnumelm);
 
    return;
}
