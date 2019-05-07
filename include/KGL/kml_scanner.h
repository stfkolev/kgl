/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   kml_scanner.h 
//
//==========================================================================
// $Id: kml_scanner.h,v 1.11 2000/03/06 15:16:52 raitner Exp $

#ifndef KGL_KML_SCANNER_H
#define KGL_KML_SCANNER_H

#include <KGL/KGL.h>

#include <cstdio>

__KGL_BEGIN_NAMESPACE

/*
 * start-size of buffers for reading strings. If too small it will be enlarged
 * dynamically
 */

#define INITIAL_SIZE 1024

KGL_EXTERN typedef enum {
    KML_KEY, KML_INT, KML_DOUBLE, KML_STRING, KML_L_BRACKET, 
    KML_R_BRACKET, KML_END, KML_LIST, KML_ERROR
} KML_value; 


/**
 * Possible errors while parsing a GML file. 
 */
KGL_EXTERN typedef enum {
    KML_UNEXPECTED, KML_SYNTAX, KML_PREMATURE_EOF, KML_TOO_MANY_DIGITS,
    KML_OPEN_BRACKET, KML_TOO_MANY_BRACKETS, KML_OK, KML_FILE_NOT_FOUND
} KML_error_value;


/**
 * @short Reason and position of an error in a GML file. 
 *
 * When an error occurs while parsing the structure of a GML file 
 * <code>KML_error</code> is used to return the type and position 
 * of the error detected. Position is specified by
 * <code>line</code> and <code>column</code>, but might be
 * somewhat imprecise. However at least the line number should
 * not differ too much from the real position. 
 *
 * @see graph#load
 */
struct KGL_EXTERN KML_error {
    /**
     * Contains the error description as symbolic constant:
     * <ul> 
     *   <li><code>KML_FILE_NOT_FOUND</code>: A file with that name
     *       doesn't exist.</li>
     *   <li><code>KML_OK</code>: No error :-)</li>
     *   <li><code>KML_TOO_MANY_BRACKETS</code>: A mismatch of
     *       brackets was detected, i.e. there were too many closing 
     *       brackets (<code>]</code>).</li>
     *   <li><code>KML_OPEN_BRACKET</code>: Now, there were too many
     *       opening brackets (<code>[</code>)</li>
     *   <li><code>KML_TOO_MANY_DIGITS</code>: The number of digits a 
     *       integer or floating point value can have is limited to
     *       1024, this should be enough :-)</li>
     *   <li><code>KML_PREMATURE_EOF</code>: An EOF occured, where it 
     *       wasn't expected, e.g. while scanning a string.</li>
     *   <li><code>KML_SYNTAX</code>: The file isn't a valid GML file,
     *       e.g. a mismatch in the key-value pairs.</li>
     *   <li><code>KML_UNEXPECTED</code>: A character occured, where
     *       it makes no sense, e.g. non-numerical characters in
     *       numbers or keys beginning with numbers</li>
     * </ul>
     * 
     */
    KML_error_value err_num;
    
    /**
     * Contains the line, where the error was detected. This will
     * usually be near the line where the error really is
     * located.
     */
    int line;

    /**
     * Contains the column, where the error was detected.
     */
    int column;
};


union KGL_EXTERN KML_tok_val {
    long integer;
    double floating;
    char* str;
    struct KML_error err;
};

/**
 * @internal
 */
struct KGL_EXTERN KML_token { 
    KML_value kind;
    union KML_tok_val value;
};

/*
 * global variables
 */

KGL_EXTERN extern unsigned int KML_line;
KGL_EXTERN extern unsigned int KML_column;

/*
 * if you are interested in the position where an error occured it is a good
 * idea to set KML_line and KML_column back. 
 * This is what KML_init does.
 */
 
KGL_EXTERN void KML_init ();

/*
 * returns the next token in file. If an error occured it will be stored in 
 * KML_token.
 */

KGL_EXTERN struct KML_token KML_scanner (FILE*);

KGL_EXTERN extern const char* KML_table[];

__KGL_END_NAMESPACE

#endif // KGL_KML_SCANNER_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
