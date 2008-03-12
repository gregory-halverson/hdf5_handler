Summary:         HDF5 data handler for the OPeNDAP Data server
Name:            hdf5_handler
Version:         1.2.1
Release:         1
License:         LGPLv2+
Group:           System Environment/Daemons 
Source0:         http://www.opendap.org/pub/source/%{name}-%{version}.tar.gz
URL:             http://www.opendap.org/

BuildRoot:       %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:   libdap-devel >= 3.8.0
BuildRequires:	 bes-devel >= 3.6.0

%description
This is the hdf5 data handler for our data server. It reads HDF5
files and returns DAP responses that are compatible with DAP2 and the
dap-server software.

%prep 
%setup -q

%build
%configure --disable-dependency-tracking --disable-static --enable-cf --enable-short-path
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install INSTALL="install -p"

rm $RPM_BUILD_ROOT%{_libdir}/*.la
rm $RPM_BUILD_ROOT%{_libdir}/*.so
rm $RPM_BUILD_ROOT%{_libdir}/bes/*.la

# rm $RPM_BUILD_ROOT%{_libdir}/bes/libhdf5_module.la

%post
libtool --finish %{_libdir}/bes/

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_bindir}/dap_h5_handler
%{_bindir}/bes-hdf5-data.sh
%{_libdir}/libhdf5_handler.so.*
%{_libdir}/bes/libhdf5_module.so
%{_datadir}/hyrax/
%doc COPYING NEWS README INSTALL

%changelog
* Wed Mar 12 2008 James Gallagher <jgallagher@opendap.org> - 1.2.1-1
- Update and copy hdf4_handler.spec features.

* Mon Jun 19 2006 James Gallagher <jimg@zoe.opendap.org> - 
- Initial build.

