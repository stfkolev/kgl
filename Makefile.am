#===========================================================================
#
#   Makefile.am
#
#===========================================================================
# $Id: Makefile.am,v 1.17 2019/05/07 12:48:16 raitner Exp $

#---------------------------------------------------------------------------
#   General Settings
#---------------------------------------------------------------------------

SUBDIRS = doc src include tests

AUTOMAKE_OPTIONS = dist-zip dist-bzip2 dist-zip

EXTRA_DIST =				\
	KGL_.spec			\
	README.Irix			\
	README.win			\
	src/KGL_.dsw			\
	src/KGL_dynamic.dsp		\
	src/KGL_static.dsp		\
	src/KGL_.sln			\
	src/KGL_dynamic.vcproj		\
	src/KGL_static.vcproj

#---------------------------------------------------------------------------
#   Goal for building documentation
#---------------------------------------------------------------------------

.PHONY: doc runtests

runtests:
	cd tests; $(MAKE) runtests

doc:
	cd doc; $(MAKE) doc

#---------------------------------------------------------------------------
#   end of file
#---------------------------------------------------------------------------
