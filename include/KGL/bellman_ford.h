/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   bellman_ford.h
//
//==========================================================================
// $Id: bellman_ford.h,v 1.5 2019/05/07 15:58:54 raitner Exp $ 

#ifndef KGL_BELLMAN_FORD_H
#define KGL_BELLMAN_FORD_H

#include <KGL/KGL.h>
#include "algorithm.h"
#include <KGL/node_map.h>
#include <KGL/node_data.h>

__KGL_BEGIN_NAMESPACE


/**
 * $Date: 2019/05/07 15:58:54 $
 * $Revision: 1.5 $
 *
 * @brief Bellman Ford %algorithm.
 *
 * Implementation of the single source shortest path due to
 * Bellman and Ford. Unlike Dijkstra's SSSP %algorithm this one
 * allows negative edge weights, as long as there are no cycles
 * with negative weight. If there are negative cycles this
 * implementation finds them.
 */ 

class KGL_EXTERN bellman_ford : public algorithm 
{
public:

    /**
     * @brief Constructor. 
     */
    bellman_ford();

    /**
     * @brief Destructor.
     */
    virtual ~bellman_ford();

    /**
     * @brief Checks whether the preconditions for Bellman Ford
     * are satisfied.
     * 
     * The Precondition are that the weights of the edges
     * have been set and that the graph has at least one node.
     *
     * @param G graph.
     * @retval algorithm::KGL_OK if %algorithm can be applied
     * @retval algorithm::KGL_ERROR otherwise.
     */
    [[nodiscard]]
    auto __cdecl check (graph& G) -> int;

    [[nodiscard]]
    auto __cdecl run (graph& G) -> int;

    /**
     * @brief Resets the algorithm. 
     * 
     * The weights are not reset. You can apply this algorithms
     * twice without setting the weights for the second call.
     */
    auto __cdecl reset () -> void;

    /**
     * @brief Sets source. 
     * 
     * The default source is the invalid %node (node::node()),
     * in this case an arbitrary %node is chosen and stored when
     * this algorithm is run.
     *
     * @param n source.
     */
    inline auto __cdecl source (const node& n) -> void {s = n;}    

    /**
     * @brief Returns source.
     *
     * @return source.
     */
    [[nodiscard]]
    auto __cdecl source () const -> node {return s;}

    /**
     * @brief Sets weights of the edges. 
     * 
     * This method @b must be called before run. 
     *
     * @param w weights of the edges.
     */
    auto __cdecl weights (const edge_map<double>& weight) -> void {w = weight; vars_set = true; }
    
    /**
     * @brief Enables or disables the storing of predecessors. 
     * 
     * If enabled for every %node the predecessor on the shortest
     * path from will be stored.
     *
     * @param set if true predecessors will be stored.
     * @sa bellman_ford::predecessor_node,
     * bellman_ford::predecessor_edge
     */
    auto __cdecl store_preds (bool set) -> void;

    /**
     * @brief Returns whether the storing of predecessors is enabled.
     * 
     * @retval true iff the storing of predecessors is enabled.  
     * 
     * @sa bellman_ford::predecessor_node,
     * bellman_ford::predecessor_edge
     */
    [[nodiscard]]
    auto __cdecl store_preds () const -> bool {return preds != 0;}

    /**
     * @brief Returns whether is reachable from source.
     * 
     * @param n node
     */    
    [[nodiscard]]
    auto __cdecl reached (const node& n) const -> bool {return !inf[n];}

    /**
     * @brief Returns the distance from source to @a n
     * 
     * @param n node
     */
    [[nodiscard]]
    auto __cdecl distance (const node& n) const -> double {return d[n];}

    /**
     * @brief edge to predecessor of %node @a n on the shortest
     * path from source
     * 
     * If @a n is a root or wasn't reached the return value is
     * the invalid %edge edge::edge().
     * 
     * @em Please @em note that this requires that this option
     * was enabled during last run.
     *
     * @param n node.
     * @return predecessor of @a n.
     * @sa bellman_ford::store_preds
     */
    [[nodiscard]]
    auto __cdecl predecessor_edge (const node& n) const -> edge
	{assert (preds); return (*preds)[n];}

    /**
     * @brief predecessor of %node @a n on the shortest
     * path from source
     * 
     * If @a n is a root or wasn't reached the return value is
     * the invalid %node node::node().
     * 
     * @em Please @em note that this requires that this option
     * was enabled during last run.
     *
     * @param n node.
     * @return predecessor of @a n.
     * @sa bellman_ford::store_preds
     */
    node predecessor_node (const node& n) const
	{edge e = predecessor_edge(n); return e == edge() ? node() : e.opposite(n); }

    /**
     * @brief Returns whether there is a cycle with negative
     * weight.
     */
    [[nodiscard]]
    auto __cdecl negative_cycle() const -> bool
	{return cycle;}

private:

    
    /** 
     * @brief Main method for Bellman Ford
     * 
     * @param e edge to be relaxed
     */
    auto __cdecl relax (const edge& e, bool dir) -> void;

    /**
     * @brief Stores source.
     * 
     * @sa bellman_ford::source.
     */
    node s;

    /**
     * @brief Stores the weights of the edges.
     * 
     * @sa bellman_ford::weights.
     */
    edge_map<double> w;
    
    /**
     * @brief Indicates whether weights were set.
     * 
     * @sa bellman_ford::weights.
     */
    bool vars_set; 

    /**
     * @brief distance from source s.
     * 
     * @sa bellman_ford::distance.
     */
    node_map<double> d; 

    /**
     * @brief Indicates whether the node has distance infinity
     * 
     * @sa bellman_ford::distance.
     */
    node_map<bool> inf;

    /**
     * @brief Stores father of each %node (if enabled)
     * 
     * @sa bellman_ford::store_preds
     */
    node_map<edge>* preds;

    /**
     * @brief Indicates whether there is a cycle with negative
     * weight
     * 
     * @sa bellman_ford::negative_cycle.
     */
    bool cycle; 
};

__KGL_END_NAMESPACE

#endif // KGL_BELLMAN_FORD_H
