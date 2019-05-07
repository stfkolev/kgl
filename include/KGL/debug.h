/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   debug.h - Functions, which are useful for debugging 
//
//==========================================================================
// $Id: debug.h,v 1.8 2001/10/10 08:30:00 chris Exp $

#ifndef KGL_DEBUG_H
#define KGL_DEBUG_H

#include <KGL/KGL.h>

#include <iostream>

__KGL_BEGIN_NAMESPACE

//
// If _DEBUG is defined the funtions defined here will produce output.
// You can either define _DEBUG here (or undef it) or you can set it as 
// option of your compiler.
//
//#define _DEBUG 1
//#undef _DEBUG
//

/**
 * @internal
 */
class KGL_EXTERN KGL_debug {
public:
    static void debug_message (const char*, ...); 
    static void init_debug();
    static void close_debug();
    static ostream& os ()
	{ return *KGL_err; }

private:
	static ostream* KGL_err;
};

__KGL_END_NAMESPACE

#endif // KGL_DEBUG_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
