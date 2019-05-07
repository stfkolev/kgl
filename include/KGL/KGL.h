/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   KGL_.h - Internal header: DO NO USE IT DIRECTLY !!!
//
//==========================================================================
// $Id: KGL_.h,v 1.29 2019/05/07 18:17:08 chris Exp $

#ifndef KGL_KGL_H
#define KGL_KGL_H

#include <KGL/version.h>

//--------------------------------------------------------------------------
//   Generic iteration over container elements
//--------------------------------------------------------------------------
//
// elem: loop variable
// cont: container to iterate over
// iter_t: iterator type
// iter: prefix for begin() and end()
//
// contains a hack for Microsoft Visual C++ 5.0, because code like
//
//   for(int i=0; i<10; ++i) { ... do something ... }
//   for(int i=0; i<10; ++i) { ... do something again ... }
//
// is illegal with Microsoft Extensions enabled, but without Microsoft
// Extensions, the Microsoft STL does not work :-(.
// So we code the line number (__LINE__) into our loop variables.

#define KGL_CONCAT(x, y) x##y
#define KGL_FORALL_VAR(y) KGL_CONCAT(KGL_FORALL_VAR, y)

#define KGL_FORALL(elem, cont, iter_t, iter)			\
if ((cont).iter##begin() != (cont).iter##end())			\
    (elem) = *((cont).iter##begin());				\
for (iter_t KGL_FORALL_VAR(__LINE__) = (cont).iter##begin();    \
    KGL_FORALL_VAR(__LINE__) != (cont).iter##end();             \
    (elem) = (++KGL_FORALL_VAR(__LINE__)) ==                    \
        (cont).iter##end() ? (elem) : *KGL_FORALL_VAR(__LINE__))

//--------------------------------------------------------------------------
//   Configuration for GCC >= 2.8.0
//--------------------------------------------------------------------------

//
// Using namespaces is the default; may be unset by one of the 
// following configurations.
//
 
#define __KGL_USE_NAMESPACES

#ifdef __GNUC__

#  define __KGL_GCC

#  if __GNUC__ == 2 && __GNUC_MINOR__ >= 8

#    undef __KGL_USE_NAMESPACES

#  elif __GNUC__ < 3

#    error "Need at least version 2.8.0 of GCC to compile KGL_."

#  endif

// 
// 2/3/2019 chris:
//
// Enable comparison of iterators in debug mode
//

#  if __GNUC__ >= 4
#    undef _GLIBCXX_DEBUG
#  endif
#endif

//--------------------------------------------------------------------------
//    Configuration for Microsoft Visual C++ 5.0
//--------------------------------------------------------------------------

#ifdef _MSC_VER

#  if _MSC_VER >= 1400 // Visual Studio 2019

#    define _HAS_ITERATOR_DEBUGGING 0
#    define _CRT_SECURE_NO_DEPRECATE 1
#    define _SECURE_SCL 0

#  endif

#  if _MSC_VER >= 1100
    
#    define __KGL_USE_NAMESPACES
#    define __KGL_MSVCC

#    pragma warning( disable : 4786 )
#    pragma warning( disable : 4251 )

#    if defined(KGL_STATIC)
#      define KGL_EXTERN
#    elif defined(KGL_EXPORTS)
#      define KGL_EXTERN __declspec(dllexport)
#    else
#      define KGL_EXTERN __declspec(dllimport)
#    endif

#  else

#    error "Need at least version 5.0 of MS Visual C++ to compile KGL_."

#  endif
#else

#   define KGL_EXTERN

#endif

//--------------------------------------------------------------------------
//   Namespaces
//--------------------------------------------------------------------------

#ifdef __KGL_USE_NAMESPACES

#  define __KGL_BEGIN_NAMESPACE namespace KGL_ {
#  define __KGL_END_NAMESPACE }

#else

#  define __KGL_BEGIN_NAMESPACE
#  define __KGL_END_NAMESPACE

#endif

//--------------------------------------------------------------------------
//   Temporary hack until Graphlet (i.e. gcc) supports Namespaces
//--------------------------------------------------------------------------

#ifdef __KGL_USE_NAMESPACES

namespace KGL_ {};
using namespace KGL_;

namespace std {};
using namespace std;

#endif // __KGL_USE_NAMESPACES

//--------------------------------------------------------------------------
//   Bugfix for EGCS & GCC < 2.95
//--------------------------------------------------------------------------

#if defined(__GNUC__) && __GNUC__ == 2 && __GNUC_MINOR__ < 95

#include <map>
#include <memory>

/**
 * @internal
 */
template <class T>
class allocator : public alloc
{
};

#endif

//--------------------------------------------------------------------------
//   MSVC 6 does not define min and max in <algorithm>
//--------------------------------------------------------------------------

#if defined(__KGL_MSVCC) && _MSC_VER < 1300

#ifndef min
template<class T>
const T& min(const T& x, const T& y)
{
    return ( x < y ? x : y);
}
#endif

#ifndef max
template<class T>
const T& max(const T& x, const T& y)
{
    return ( x > y ? x : y);
}
#endif

#endif

//--------------------------------------------------------------------------
//  enable debugging of memory leaks in debug mode of MSVC
//--------------------------------------------------------------------------

#ifdef __KGL_MSVCC
#   ifdef _DEBUG
#	define WINVER 0xA00	// compatibility with at least WinNT4
	// usually the followin two lines are defined in Microsoft's
	// generated stdafx.h
#	define VC_EXTRALEAN // do not include rarely used parts
#	include <afxwin.h>  // MFC core und standard components
	// extra definition for check whether all needed headers are included
#	undef SEARCH_MEMORY_LEAKS_ENABLED
#	define SEARCH_MEMORY_LEAKS_ENABLED
#   endif   // _DEBUG
#endif	// __KGL_MSVCC

#endif // KGL_KGL_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
