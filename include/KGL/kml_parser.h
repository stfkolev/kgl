/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   kml_parser.h 
//
//==========================================================================
// $Id: kml_parser.h,v 1.7 2000/01/05 16:32:36 raitner Exp $

#ifndef KGL_KML_PARSER_H
#define KGL_KML_PARSER_H

#include <KGL/KGL.h>
#include <KGL/kml_scanner.h>

__KGL_BEGIN_NAMESPACE

/**
 * @internal
 */
union KGL_EXTERN KML_pair_val {
    long integer;
    double floating;
    char* str;
    struct KML_pair* list;
};

/**
 * @internal
 */
struct KGL_EXTERN KML_pair {
    char* key;
    KML_value kind;
    union KML_pair_val value;
    struct KML_pair* next;
};

/**
 * @internal
 */
struct KGL_EXTERN KML_list_elem {
    char* key;
    struct KML_list_elem* next;
};

/**
 * @internal
 */
struct KGL_EXTERN KML_stat {
    struct KML_error err;
    struct KML_list_elem* key_list;
};

/*
 * returns list of KEY - VALUE pairs. Errors and a pointer to a list
 * of key-names are returned in KML_stat. Previous information contained
 * in KML_stat, i.e. the key_list, will be *lost*. 
 */

KGL_EXTERN KML_pair* KML_parser (FILE*, KML_stat*, int);

/*
 * free memory used in a list of KML_pair
 */

KGL_EXTERN void KML_free_list (KML_pair*, KML_list_elem*);


/*
 * debugging 
 */

KGL_EXTERN void KML_print_list (KML_pair*, int);

__KGL_END_NAMESPACE

#endif // KGL_KML_PARSER_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
