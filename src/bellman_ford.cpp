//==========================================================================
//
//   bellman_ford.cpp
//
//==========================================================================
// $Id: bellman_ford.cpp,v 1.4 2019/05/07 17:50:56 raitner Exp $

#include "KGL/bellman_ford.h"

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

bellman_ford::bellman_ford()
{
    vars_set = false;
    preds = 0;
}

bellman_ford::~bellman_ford()
{
    if (preds) delete preds;
}

void bellman_ford::store_preds (bool set)
{
    if (set && !preds) {
	preds = new node_map<edge>;
    } else if (!set && preds) {
	delete preds;
	preds = 0;
    }
}


int bellman_ford::check(graph& G)
{
    if (!vars_set) 
    {
	return algorithm::KGL_ERROR;
    }

    if (G.nodes_begin() == G.nodes_end()) 
    {
	return algorithm::KGL_ERROR;
    }

    return algorithm::KGL_OK;
}

int bellman_ford::run(graph& G)
{
    if (s == node()) 
    {
	s = *(G.nodes_begin());
    }

    //----------------------------------------------------------------------
    //   initialize
    //----------------------------------------------------------------------

    inf.init (G, true);
    
    if (preds) {
	preds->init (G, edge());
    }

    inf[s] = false;
    d[s] = 0;
    cycle = false;

    //----------------------------------------------------------------------
    //   relax
    //----------------------------------------------------------------------

    graph::edge_iterator it, end;

    for (int i = 1; i < G.number_of_nodes(); ++i)
    {	
	for (it = G.edges_begin(), end = G.edges_end(); it != end; ++it)
	{
            relax (*it, true);

            if (G.is_undirected())
            {
                relax(*it, false);
            }
	}
    }

    //----------------------------------------------------------------------
    //   cycle detection
    //----------------------------------------------------------------------    

    for (it = G.edges_begin(), end = G.edges_end(); it != end; ++it)
    {
	node u = (*it).source();
	node v = (*it).target();

	if(!inf[u] && !inf[v]) 
	{
	    if (d[v] > d[u] + w[*it]) 
	    {
		cycle = true;
	    }
	}
    }

    return algorithm::KGL_OK;
}

void bellman_ford::reset()
{
}

void bellman_ford::relax(const edge& e, bool dir )
{
    node u = e.source();
    node v = e.target();

    if (!dir) {
        node tmp = u;
        u = v;
        v = tmp;
    }        
    
    if (!inf[u] && (inf[v] || (d[v] > d[u] + w[e]))) 
    {
	d[v] = d[u] + w[e];
	inf[v] = false;
	
	if (preds) 
	{
	    (*preds)[v] = e;
	} 
    }
}



__KGL_END_NAMESPACE
