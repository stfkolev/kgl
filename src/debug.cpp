/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   debug.cpp
//
//==========================================================================
// $Id: debug.cpp,v 1.10 2001/11/07 13:58:09 pick Exp $

#include <KGL/debug.h>

#include <fstream>
#include <cstdarg>
#include <cstdio>

#ifdef __KGL_MSVCC
#   ifdef _DEBUG
#	ifndef SEARCH_MEMORY_LEAKS_ENABLED
#	error SEARCH NOT ENABLED
#	endif
#	define new DEBUG_NEW
#	undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#   endif   // _DEBUG
#endif	// __KGL_MSVCC

__KGL_BEGIN_NAMESPACE

ostream* KGL_debug::KGL_err = 0;

void KGL_debug::debug_message (const char* message, ...) 
{
#ifdef _DEBUG
    va_list arg_list;
    va_start(arg_list, message);

    char buf[1024];
    vsprintf(buf, message, arg_list);
    if (KGL_err) {
	os() << buf;
    }
#endif
}

void KGL_debug::init_debug () 
{
    if (!KGL_err) {
#ifdef __KGL_MSVCC
	KGL_err = new ofstream ("ERRLOG.txt", ios::out | ios::app);
#else
	KGL_err = &cerr;
#endif
    }
}

void KGL_debug::close_debug () 
{
    if (KGL_err) {
#ifdef __KGL_MSVCC 
	((ofstream*) KGL_err)->close();
	delete KGL_err;
	KGL_err = 0;
#endif
    }
}

__KGL_END_NAMESPACE

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
