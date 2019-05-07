/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   edge_data.h - Internal header: DO NO USE IT DIRECTLY !!!
//
//==========================================================================
// $Id: edge_data.h,v 1.9 2000/02/03 12:49:50 raitner Exp $

#ifndef KGL_EDGE_DATA_H
#define KGL_EDGE_DATA_H

#include <KGL/KGL.h>
#include <KGL/node.h>
#include <KGL/edge.h>

#include <list>

__KGL_BEGIN_NAMESPACE

/**
 * @internal
 */
class KGL_EXTERN edge_data
{
public:
    int id;				// internal numbering
    list<node> nodes[2]; 		// nodes[0] = sources,
    					// nodes[1] = targets
    list<list<edge>::iterator> adj_pos[2];// positions in the adjacency lists
					// of sources and targets
    list<edge>::iterator pos;		// position in the list of all edges
    bool hidden;
    graph* owner;
};

__KGL_END_NAMESPACE

#endif // KGL_EDGE_DATA_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
