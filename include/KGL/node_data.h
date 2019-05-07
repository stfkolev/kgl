/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   node_data.h - Internal header: DO NO USE IT DIRECTLY !!!
//
//==========================================================================
// $Id: node_data.h,v 1.7 2000/01/05 16:32:38 raitner Exp $

#ifndef KGL_NODE_DATA_H
#define KGL_NODE_DATA_H

#include <KGL/KGL.h>
#include <KGL/node.h>
#include <KGL/edge.h>

#include <list>

__KGL_BEGIN_NAMESPACE

class graph;

/**
 * @internal
 */
class KGL_EXTERN node_data
{
public:
    int id;			// internal numbering
    graph *owner;		// graph containing this node
    list<node>::iterator pos;	// position in the list of all nodes
    list<edge> edges[2];	// edges incident to this node
				// edges[0] = in_edges, edges[1] = out_edges
    bool hidden;
};
    
__KGL_END_NAMESPACE

#endif // KGL_NODE_DATA_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
