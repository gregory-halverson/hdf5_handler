/////////////////////////////////////////////////////////////////////////////
//  This file is part of the hdf5 data handler for the OPeNDAP data server.
//
// Author:   Hyo-Kyung Lee <hyoklee@hdfgroup.org>
//
// Copyright (c) 2007-2016 The HDF Group, Inc. and OPeNDAP, Inc.
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

#include "HE5Parser.h"
#include <InternalErr.h>
#include <HDF5CFUtil.h>
#include <stdlib.h>

using namespace std;

HE5Parser::HE5Parser()
{
    structure_state = -1;       // Za/Swath/Grid state 
    parser_state = 0;           // Parser's current state 
    err_msg = "";               // error message.
}

HE5Parser::~HE5Parser()
{
}


void HE5Parser::print()
{
    unsigned int i = 0;

    if(err_msg != ""){
        cerr<< "Parse error:" << err_msg << endl;
    }
    cout << "ZA Size=" << za_list.size() << endl;
    for(i=0; i < za_list.size(); i++) {
        HE5Za z = za_list.at(i);
        cout << "ZA Name=" << z.name << endl;
        cout << "ZA Dim Size=" << z.dim_list.size() << endl;
        unsigned int j = 0;
        for(j=0; j < z.dim_list.size(); j++) {
            HE5Dim d = z.dim_list.at(j);
            cout << "ZA Dim Name=" << d.name;
            cout << " Size=" << d.size << endl;
        }

        cout << "ZA Var Size=" << z.data_var_list.size() 
             << endl;
        for(j=0; j < z.data_var_list.size(); j++) {
            HE5Var v = z.data_var_list.at(j);
            cout << "ZA Var Name=" << v.name << endl;
            cout << "ZA Var Dim Size=" << v.dim_list.size() << endl;
            unsigned int k = 0;
            for(k=0; k < v.dim_list.size(); k++) {
                HE5Dim d = v.dim_list.at(k);
                cout << "ZA Var Dim Name=" << d.name << endl;
            }
        }
    }

    cout << "Swath Size=" << swath_list.size() << endl;
    for(i=0; i < swath_list.size(); i++) {
        HE5Swath s = swath_list.at(i);
        cout << "Swath Name=" << s.name << endl;
        cout << "Swath Dim Size=" << s.dim_list.size() << endl;
        unsigned int j = 0;
        for(j=0; j < s.dim_list.size(); j++) {
            HE5Dim d = s.dim_list.at(j);
            cout << "Swath Dim Name=" << d.name;
            cout << " Size=" << d.size << endl;
        }

        cout << "Swath Geo Var Size=" << s.geo_var_list.size() 
             << endl;
        for(j=0; j < s.geo_var_list.size(); j++) {
            HE5Var v = s.geo_var_list.at(j);
            cout << "Swath Geo Var Name=" << v.name << endl;
            cout << "Swath Geo Var Dim Size=" << v.dim_list.size() << endl;
            unsigned int k = 0;
            for(k=0; k < v.dim_list.size(); k++) {
                HE5Dim d = v.dim_list.at(k);
                cout << "Swath Geo Var Dim Name=" << d.name;
                cout << " Size=" << d.size << endl;
            }
        }

        cout << "Swath Data Var Size=" << s.data_var_list.size() 
             << endl;
        for(j=0; j < s.data_var_list.size(); j++) {
            HE5Var v = s.data_var_list.at(j);
            cout << "Swath Data Var Name=" << v.name << endl;
            cout << "Swath Data Var Number Dim =" << v.dim_list.size() << endl;
            unsigned int k = 0;
            for(k=0; k < v.dim_list.size(); k++) {
                HE5Dim d = v.dim_list.at(k);
                cout << "Swath Data Var Dim Name=" << d.name << endl;
                cout <<"Swath Data Var Dim Size= "<< d.size<<endl;
            }
// UNCOMMENT OUT the block below to retrieve the maximum dimension list. ALSO NEED TO ADD MAX_DIMENSION_LIST at  he5dds.lex.
#if 0
            for(k=0; k < v.max_dim_list.size(); k++) {
                HE5Dim d = v.max_dim_list.at(k);
                cout << "Swath Data Var Max Dim Name=" << d.name << endl;
                cout <<"Swath Data Var Dim Size= "<< d.size<<endl;
            }
#endif
        }
    }

    cout << "Grid Size=" << grid_list.size() << endl;
    for(i=0; i < grid_list.size(); i++) {
        HE5Grid g = grid_list.at(i);
        cout << "Grid Name=" << g.name << endl;

        cout << "Grid point_lower=" << g.point_lower << endl;
        cout << "Grid point_upper=" << g.point_upper << endl;
        cout << "Grid point_left="  << g.point_left  << endl;
        cout << "Grid point_right=" << g.point_right << endl;
        cout << "Grid Sphere code =" <<g.sphere <<endl;

        cout << "Grid Dim Size=" << g.dim_list.size() << endl;
        unsigned int j = 0;
        for(j=0; j < g.dim_list.size(); j++) {
            HE5Dim d = g.dim_list.at(j);
            cout << "Grid Dim Name=" << d.name;
            cout << " Size=" << d.size << endl;
        }

        cout << "Grid Var Size=" << g.data_var_list.size() 
             << endl;
        for(j=0; j < g.data_var_list.size(); j++) {
            HE5Var v = g.data_var_list.at(j);
            cout << "Grid Var Name=" << v.name << endl;
            cout << "Grid Var Dim Size=" << v.dim_list.size() << endl;
            unsigned int k = 0;
            for(k=0; k < v.dim_list.size(); k++) {
                HE5Dim d = v.dim_list.at(k);
                cout << "Grid Var Dim Name=" << d.name << endl;
            }
#if 0
            for(k=0; k < v.max_dim_list.size(); k++) {
                HE5Dim d = v.max_dim_list.at(k);
                cout << "Grid Var Max Dim Name=" << d.name << endl;
            }
#endif
       }
        cout << "Grid pixelregistration=" << 
            g.pixelregistration
             << endl;
        cout << "Grid origin=" << 
            g.gridorigin
             << endl;
        cout << "Grid projection=" << 
            g.projection
             << endl;

        cout <<"Grid zone= "<< g.zone<<endl;
        cout <<"Grid sphere= "<<g.sphere<<endl;

        cout<<"Grid projection parameters are "<<endl;
        for(int j= 0;j<13;j++) 
            cout<<g.param[j]<<endl;
    }
    
}

void HE5Parser::add_projparams(const string & st_str) {

    string projparms = "ProjParams=(";
    char parms_end_marker = ')';
    size_t parms_spos = st_str.find(projparms);
    int grid_index = 0;
    while(parms_spos!=string::npos) {
        size_t parms_epos = st_str.find(parms_end_marker,parms_spos);
        if(parms_epos == string::npos)
            throw libdap::InternalErr(__FILE__,__LINE__,"HDF-EOS5 Grid ProjParms syntax error: ProjParams doesn't end with ')'. ");
        string projparms_raw_values = st_str.substr(parms_spos+projparms.size(),parms_epos-parms_spos-projparms.size());
        vector<string> projparms_values;
        HDF5CFUtil::Split(projparms_raw_values.c_str(),',',projparms_values);

        for(unsigned int i = 0; i<projparms_values.size();i++) {
            grid_list[grid_index].param[i] = strtod(projparms_values[i].c_str(),NULL);
        }
#if 0
for(vector<string>::iterator istr=projparms_values.begin();istr!=projparms_values.end();++istr)
cerr<<"projparms value is "<<*istr<<endl;
#endif
        parms_spos = st_str.find(projparms,parms_epos);
        grid_index++;
    }

}
