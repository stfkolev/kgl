/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   KML_parser.cpp - parser for the KML-file-format specified in:
//                    Michael Himsolt, KML: Graph Modelling Language,
//                    21.01.1997 
//
//==========================================================================
// $Id: KML_parser.cpp,v 1.9 2001/11/07 13:58:10 pick Exp $

#include <KGL/KML_parser.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <string.h>

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

struct KML_pair* KML_parser (FILE* source, struct KML_stat* stat, int open) {
    
    struct KML_token token;
    struct KML_pair* pair;
    struct KML_pair* list;
    struct KML_pair* tmp = NULL;
    struct KML_list_elem* tmp_elem;

    assert (stat);

    pair = (struct KML_pair*) malloc (sizeof (struct KML_pair));
    pair->next = NULL;
    list = pair;

    for (;;) {
	token = KML_scanner (source);
	
	if (token.kind == KML_END) {
	    if (open) {
		stat->err.err_num = KML_OPEN_BRACKET;
		stat->err.line = KML_line;
		stat->err.column = KML_column;
		free (pair);

		if (tmp == NULL) {
		  return NULL;
		} else {
		  tmp->next = NULL;
		  return list;
		}
	    }

	    break;

	} else if (token.kind == KML_R_BRACKET) {
	    if (!open) {
		stat->err.err_num = KML_TOO_MANY_BRACKETS;
		stat->err.line = KML_line;
		stat->err.column = KML_column;
		free (pair);

		if (tmp == NULL) {
		  return NULL;
		} else {
		  tmp->next = NULL;
		  return list;
		}
	    }

	    break;

	} else if (token.kind == KML_ERROR) {
	    stat->err.err_num = token.value.err.err_num;
	    stat->err.line = token.value.err.line;
	    stat->err.column = token.value.err.column;
	    free (pair);
	      
	    if (tmp == NULL) {
		return NULL;
	    } else {
		tmp->next = NULL;
		return list;
	    }

	} else if (token.kind != KML_KEY) {
	    stat->err.err_num = KML_SYNTAX;
	    stat->err.line = KML_line;
	    stat->err.column = KML_column;
	    free (pair);
	   
	    if (token.kind == KML_STRING) {
		free (token.value.str);
	    }

	    if (tmp == NULL) {
		return NULL;
	    } else {
		tmp->next = NULL;
		return list;
	    }
	}
	   
	if (!stat->key_list) {
	    stat->key_list = (struct KML_list_elem*) 
		malloc (sizeof (struct KML_list_elem));
	    stat->key_list->next = NULL;
	    stat->key_list->key = token.value.str;
	    pair->key = token.value.str;
	
	} else {
	    tmp_elem = stat->key_list;
	    
	    while (tmp_elem) {
		if (!strcmp (tmp_elem->key, token.value.str)) {
		    free (token.value.str);
		    pair->key = tmp_elem->key;
		    break;
		}
		
		tmp_elem = tmp_elem->next;
	    }
	
	    if (!tmp_elem) {
		tmp_elem = (struct KML_list_elem*)
		    malloc (sizeof (struct KML_list_elem));
		tmp_elem->next = stat->key_list;
		stat->key_list = tmp_elem;
		tmp_elem->key = token.value.str;
		pair->key = token.value.str;
	    }
	}
	
	token = KML_scanner (source);

	switch (token.kind) {
	case KML_INT:
	    pair->kind = KML_INT;
	    pair->value.integer = token.value.integer;
	    break;

	case KML_DOUBLE:
	    pair->kind = KML_DOUBLE;
	    pair->value.floating = token.value.floating;
	    break;

	case KML_STRING:
	    pair->kind = KML_STRING;
	    pair->value.str = token.value.str;
	    break;

	case KML_L_BRACKET:
	    pair->kind = KML_LIST;
	    pair->value.list = KML_parser (source, stat, 1);
	    
	    if (stat->err.err_num != KML_OK) {
		return list;
	    }

	    break;

	case KML_ERROR:
	    stat->err.err_num = token.value.err.err_num;
	    stat->err.line = token.value.err.line;
	    stat->err.column = token.value.err.column;
	    free (pair);
		
	    if (tmp == NULL) {
		return NULL;
	    } else {
		tmp->next = NULL;
		return list;
	    }

	default:    
	    stat->err.line = KML_line;
	    stat->err.column = KML_column;
	    stat->err.err_num = KML_SYNTAX;
	    free (pair);

	    if (tmp == NULL) {
		return NULL;
	    } else {
		tmp->next = NULL;
		return list;
	    }
	}

	tmp = pair;
	pair = (struct KML_pair*) malloc (sizeof (struct KML_pair));
	tmp->next = pair;
	pair->next = NULL;
    }

    stat->err.err_num = KML_OK;
    free (pair);
    
    if (tmp == NULL) {
	return NULL;
    } else {
	tmp->next = NULL;
	return list;
    }
}
	

void KML_free_list (struct KML_pair* list, struct KML_list_elem* keys) {
    
    struct KML_pair* tmp = list;
    struct KML_list_elem* tmp_key;

    while (keys) {
	free (keys->key);
	tmp_key = keys->next;
	free (keys);
	keys = tmp_key;
    }

    while (list) {
	
	switch (list->kind) {
	case KML_LIST:
	    KML_free_list (list->value.list, NULL);
	    break;

	case KML_STRING:
	    free (list->value.str);
	    break;

	default:
	    break;
	}
	
	tmp = list->next;
	free (list);
	list = tmp;
    }
}
	


void KML_print_list (struct KML_pair* list, int level) {
    
    struct KML_pair* tmp = list;
    int i;

    while (tmp) {
	
	for (i = 0; i < level; i++) {
	    printf ("    ");
	}

	printf ("*KEY* : %s", tmp->key);

	switch (tmp->kind) {
	case KML_INT:
	    printf ("  *VALUE* (long) : %ld \n", tmp->value.integer);
	    break;

	case KML_DOUBLE:
	    printf ("  *VALUE* (double) : %f \n", tmp->value.floating);
	    break;

	case KML_STRING:
	    printf ("  *VALUE* (string) : %s \n", tmp->value.str);
	    break;
	    
	case KML_LIST:
	    printf ("  *VALUE* (list) : \n");
	    KML_print_list (tmp->value.list, level+1);
	    break;

	default:
	    break;
	}
	
	tmp = tmp->next;
    }
}
	
__KGL_END_NAMESPACE

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
