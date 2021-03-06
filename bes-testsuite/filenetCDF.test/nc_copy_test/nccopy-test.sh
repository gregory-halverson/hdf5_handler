#!/bin/sh

#The path BES is installed must be provided explicitly.
if [ -z "$BESPATH" ]; then
    echo Environment variable BESPATH should be set. It should be the BES path the handler is linked with.
    exit
fi

#FNC_NOCLEANUP="yes"

# Use this path to figure out the location of besstandalone, bes.conf and the data.
BESCONF="$BESPATH/etc/bes/bes.conf"
BESH5SHARE="$BESPATH/share/hyrax/data/hdf5"
NCCOPY="$BESPATH/deps/bin/nccopy"
NCDUMP="$BESPATH/deps/bin/ncdump"
#1. Remember the current directory
CURDIR=`pwd`
echo $CURDIR

#2. Obtain HDF5 files
cd $BESH5SHARE
SHAREDIR=`pwd`
echo $SHAREDIR
GET=""
command -v  wget > /dev/null && GET="wget -N --retr-symlinks"
if [ -z "$GET" ]; then
  command -v  curl > /dev/null && GET="curl -O"
fi

if [ -z "$GET" ]; then
  echo "Neither wget nor curl found in your system."
  exit
fi

NC_CP_TEST="nccp_test"
mkdir $NC_CP_TEST
cd $NC_CP_TEST
HDF5_FILE_DIR=`pwd`
$GET https://gamma.hdfgroup.org/ftp/pub/outgoing/opendap/data/HDF5/hdf5_handler/grid_1_2d.h5 
$GET https://gamma.hdfgroup.org/ftp/pub/outgoing/opendap/data/HDF5/hdf5_handler/dim_scale.h5 
$GET https://gamma.hdfgroup.org/ftp/pub/outgoing/opendap/data/HDF5/hdf5_handler/t_2d_2dll.nc4.h5

#3. Use Unidata's nccopy to generate the netCDF-3 and the netCDF-4
cd $CURDIR

#nccopy -k 'classic' http://alpaca:8080/opendap/data/hdf5/hdf5-files/fake-files-for-handler/t_2d_2dll.nc4.h5 t_2d_2dll.nc
#nccopy -k 'netCDF-4 classic model' http://alpaca:8080/opendap/data/hdf5/hdf5-files/fake-files-for-handler/t_2d_2dll.nc4.h5 t_2d_2dll.nc4
#/opt/kent/opendap/bes-dev/opendapbin/bin/besstandalone -c /opt/kent/opendap/bes-dev/opendapbin/etc/bes/bes.conf -i grid_1_2d.nc.bescmd >grid_1_2d.h5.nc
echo "Generate netcdf-3 and netcdf-4 files by using nccopy"
nccopy -k 'classic' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/t_2d_2dll.nc4.h5 t_2d_2dll.nc
nccopy -k 'classic' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/grid_1_2d.h5 grid_1_2d.nc
nccopy -k 'classic' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/dim_scale.h5 dim_scale.nc
nccopy -k 'netCDF-4 classic model' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/t_2d_2dll.nc4.h5 t_2d_2dll.nc4
nccopy -k 'netCDF-4 classic model' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/grid_1_2d.h5 grid_1_2d.nc4
nccopy -k 'netCDF-4 classic model' http://localhost:8080/opendap/data/hdf5/$NC_CP_TEST/dim_scale.h5 dim_scale.nc4


echo "Compare ncdump output (ncdump -h for big files) for nc and nc-4 files"
command -v $NCDUMP >/dev/null
if [ "$?" -ne "0" ]
then 
	echo "ncdump is not provided by the Hyrax dependencies under BESPATH. Won't check ncdump output."
        echo "Abort the program"
        cd ..
       	if [ -z "$FNC_NOCLEANUP" ]; then 
       		rm -rf $HDF5_FILE_DIR
                rm -rf *.nc
                rm -rf *.nc4
	fi
	exit 1
fi


for NCF in *.nc
do 
        NCF_NO_SUFFIX=${NCF%.nc}
	$NCDUMP $NCF > $NCF_NO_SUFFIX.ndp3
	if [ "$?" -ne "0" ]
	then 
		echo "ncdump FAIL to dump $NCF"
        	echo "Abort the program"
	       	if [ -z "$FNC_NOCLEANUP" ]; then 
       			rm -rf $HDF5_FILE_DIR
                        rm -rf *.nc
                        rm -rf *.nc4
		fi
         	exit 1
	fi
done

for NCF in *.nc4
do 
        NCF_NO_SUFFIX=${NCF%.nc4}
	$NCDUMP $NCF > $NCF_NO_SUFFIX.ndp4
	if [ "$?" -ne "0" ]
	then 
		echo "ncdump FAIL to dump $NCF"
        	echo "Abort the program"
        	cd ..
       		if [ -z "$FNC_NOCLEANUP" ]; then 
       			rm -rf $HDF5_FILE_DIR
                        rm -rf *.nc
                        rm -rf *.nc4
			rm -rf *.ndp3
		fi
        	exit 1
	fi
done

for NCF in *.nc
do 
        NCF_NO_SUFFIX=${NCF%.nc}
	diff -I  ":history = " $NCF_NO_SUFFIX.ndp3 $NCF_NO_SUFFIX.ndp4
	if [ "$?" -ne "0" ]
	then 
		echo "ncdump output comparsion FAIL for  $NCF_NO_SUFFIX"
        	echo "Abort the program"
        	cd ..
       		if [ -z "$FNC_NOCLEANUP" ]; then 
       			rm -rf $HDF5_FILE_DIR
                        rm -rf *.nc
                        rm -rf *.nc4
			rm -rf *.ndp3
			rm -rf *.ndp4
		fi
        	exit 1
	fi

done

echo "All default tests get PASSED"
#Remove all the HDF5 files under BES hyrax share directory and the generated NC files
if [ -z "$FNC_NOCLEANUP" ]; then 
   rm -rf $HDF5_FILE_DIR
   rm -rf *.nc
   rm -rf *.nc4
   rm -rf *.ndp3
   rm -rf *.ndp4
	
fi
<<'COMMENT'
COMMENT
