/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   min_tree.cpp
//
//==========================================================================
// $Id: min_tree.h,v 1.3 2001/06/21 10:55:08 chris Exp $

#ifndef KGL_MIN_TREE_H
#define KGL_MIN_TREE_H

#include <KGL/KGL.h>
#include <KGL/algorithm.h>
#include <KGL/edge_map.h>
#include <set>

__KGL_BEGIN_NAMESPACE

/**
 * @brief Kruskal's %algorithm for finding minimal spanning tree
 * of a %graph.  
 * 
 * @author Stf Kolev 
 */
class min_tree: public algorithm { 

public:

    /**
     * @brief Constructor
     */
    min_tree ();

    /**
     * @brief Destructor
     */
    virtual ~min_tree () {};

    /**
     * @brief Checks whether %algorithm can be applied.
     * 
     * The %graph must
     *    - be undirected 
     *    - be connected
     *    - have more than 2 nodes
     * 
     * Additionally the weights of the edges must have been set 
     * in advance using min_tree::set_distances.
     * 
     * @param g graph
     * @return algorithm::KGL_OK if %algorithm can be applied
     * algorithm::KGL_ERROR otherwise.
     */
    int check (graph& g);

    int run (graph& g);
    
    virtual void reset ();

    /**
     * @brief Sets %edge weights.
     * 
     * Setting of %edge weights must be done before calling
     * min_tree::check and min_tree::run.
     * 
     * @param dist %edge weigths.
     */
    void set_distances (const edge_map<int>& dist);

    /**
     * @brief Edges of minimal spanning tree calculated in the
     * last call of min_tree::run.
     * 
     * @return Set of edges of representing the minimal spanning
     * tree 
     */
    set<edge> get_min_tree();
    
    /**
     * @brief Weight of minimal spanning tree.
     * 
     * @return weight of minimal spanning tree.
     */
    int get_min_tree_length();
    
private:
    typedef pair<int, node::adj_edges_iterator> TSP_A_VALUE;

    class input_comp {
    public:
	bool operator()(TSP_A_VALUE x, TSP_A_VALUE y)
	    { return x.first > y.first;}
    };

    edge_map<int> dist;
    int weight;
    set<edge> tree;
    bool is_set_distances;
};

__KGL_END_NAMESPACE

#endif // KGL_MIN_TREE_H





