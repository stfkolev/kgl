### BEGIN KGL.spec
# Note that this is NOT a relocatable package

Name: KGL
Summary: The Kolev Graph Standard Template
Version: 1.0.3
Release: 1
Group: Development/Libraries
Copyright: Copyright (C) 2019 Stf Kolev
Packager: Stf Kolev <inkyzfx@gmail.com>
Prefix: /usr
BuildRoot: /var/tmp/%{name}-%{version}-root

%description

There are some basic data structures and algorithms that are frequently
used in many programs. This includes container classes such as vectors,
sets and lists.

Many commercial but some free libraries have implemented these data
structures and algorithms in a general way. This makes them usable for
many purposes.

One of these libraries is the Standard Template Library (STL), an
extremely flexible implementation of many container classes and standard
algorithms. STL is supposed to become a part of the C++ standard library
and therefore is an ideal basis when writing portable programs.

Unfortunately, STL has no support for graphs and graph
algorithms. However, graphs are widely used for complex relational
structures.

Since I had a coursework based on graphs, and was said to make it STL-like, I
decided to implement KGL, a graph library based on STL. KGL contains the
classes needed to work with graphs, nodes and edges and some basic
algorithms as building blocks for more complex graph algorithms. Further
algorithms are not finished.'

%changelog
- Initial packaging.

%prep
%setup
#%patch -p0

%build
CXXFLAGS=-O3 CPPFLAGS="" CFLAGS="" ./configure --enable-static --prefix=/usr 
make

%install
make prefix=$RPM_BUILD_ROOT%{prefix} install
strip $RPM_BUILD_ROOT%{prefix}/lib/libKGL-1.0.3.so $RPM_BUILD_ROOT%{prefix}/lib/libKGL.a

%clean
rm -rf $RPM_BUILD_ROOT

%post
PATH="$PATH:/sbin" ldconfig -n /usr/lib

%files
%doc README  
%doc INSTALL
%doc doc/latex/KGL.ps
%doc doc/html
/usr/include/KGL
/usr/lib
###END KGL.spec
