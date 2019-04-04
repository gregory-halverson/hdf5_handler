// This file is part of hdf5_handler a HDF5 file handler for the OPeNDAP
// data server.

// Author: Hyo-Kyung Lee <hyoklee@hdfgroup.org> and Muqun Yang
// <myang6@hdfgroup.org> 

// Copyright (c) 2009-2016 The HDF Group, Inc. and OPeNDAP, Inc.
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

#ifndef _hdf5Int64_h
#define _hdf5Int64_h 1

#include <string>

#include <H5Ipublic.h>

#include "Int64.h"
#include "h5get.h"


/// \file HDF5Int64.h
/// \brief This class provides a way to map HDF5 Int64 to DAP Int64 for the default option.
/// 
///
/// \author Hyo-Kyung Lee   (hyoklee@hdfgroup.org)
/// \author Kent Yang       (ymuqun@hdfgroup.org)
/// \author James Gallagher (jgallagher@opendap.org)
///

class HDF5Int64:public libdap::Int64 {

  private:
//    hid_t dset_id;
//    hid_t ty_id;
    std::string var_path;

  public:
    /// Constructor
    HDF5Int64(const std::string &n, const std::string &vpath,const std::string &d);
    virtual ~ HDF5Int64() { }

    /// Clone this instance.
    ///
    /// Allocate a new instance and copy *this into it. This method must perform a deep copy.
    /// \return A newly allocated copy of this class  
    virtual libdap::BaseType *ptr_duplicate();

    /// Reads HDF5 Int64 data into local buffer
    virtual bool read();

    /// See return_type function defined in h5dds.cc.
    friend std::string return_type(hid_t datatype);

    /// returns HDF5 dataset id.  
//    hid_t get_did();

    /// returns HDF5 datatype id.
//    hid_t get_tid();

    /// remembers HDF5 dataset id.
//    void set_did(hid_t dset);

    /// remembers HDF5 datatype id.
//    void set_tid(hid_t type);

};

#endif
