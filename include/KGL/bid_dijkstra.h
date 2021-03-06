/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   bid_dijkstra.h
//
//==========================================================================
// $Id: bid_dijkstra.h,v 1.3 2019/05/07 15:58:54 raitner Exp $

#ifndef KGL_BID_DIJKSTRA_H
#define KGL_BID_DIJKSTRA_H

#include <KGL/KGL.h>
#include <KGL/graph.h>
#include <KGL/node_map.h>
#include <KGL/edge_map.h>
#include <KGL/algorithm.h>

__KGL_BEGIN_NAMESPACE

/**
 * $Date: 2019/05/07 15:58:54 $
 * $Revision: 1.3 $
 * 
 * @brief Dijkstra's Algorithm for computing a shortest path from a single
 * source to a single target.
 *
 * This class implements Dijkstra's algorithm in a bidirectional manner for
 * computing a shortest path from a single source to a single target in
 * \f$\mathcal{O}((|V| + |E|) log |V|)\f$ worst case.
 *
 * @sa dijkstra
 * @sa bellman_ford
 *
 *@author Stf Kolev inkyzfx@gmail.com
 */
class KGL_EXTERN bid_dijkstra : public algorithm
{
public:
    /**
     * @brief Iterator type for traversing %nodes on one shortest path.
     */
    typedef list<node>::const_iterator shortest_path_node_iterator;

    /**
     * @brief Iterator type for traversing %edges on one shortest path.
     */
    typedef list<edge>::const_iterator shortest_path_edge_iterator;

    /**
     * @internal
     */
    enum node_color {white, grey, black};

    /**
     * @brief Default constructor.
     *
     * Enables only the calculation of shortest paths.
     * 
     * @sa algorithm::algorithm
     */
    bid_dijkstra();

    /**
     * @brief Destructor.
     *
     * @sa algorithm::~algorithm
     */
    virtual ~bid_dijkstra();

    /**
     * @brief Sets source and target %node.
     *
     * Must be executed every time before check and run of this %algorithm.
     * 
     * @param s source %node
     * @param t target %node
     */
    auto __cdecl source_target(const node& s, const node& t) -> void;

    /**
     * @brief Sets weights of the edges. 
     * 
     * This method @b must be called before check and run. 
     *
     * @param weight weights of the %edges
     */
    auto __cdecl weights(const edge_map<double>& weight) -> void;
    
    /**
     * @brief Enables or disables the storing of the shortest path. 
     * 
     * If enabled for every %node and edge on the shortest path from source
     * to target will be stored.
     *
     * @param set true if path should be stored
     *
     * @sa dijkstra::predecessor_node
     * @sa dijkstra::predecessor_edge
     */
    auto __cdecl store_path(bool set) -> void;

    /**
     * @brief Checks whether the preconditions for bidirectional Dijkstra are
     * satisfied.
     * 
     * The Precondition are that the weights of the edges have been set and
     * that the graph has at least one %node. Additionally all %edge weights
     * must be \f$\ge 0\f$ and and source and target %nodes must be found in
     * @p G.
     *
     * @param G graph
     *
     * @retval algorithm::KGL_OK if %algorithm can be applied 
     * @retval algorithm::KGL_ERROR otherwise
     *
     * @sa dijkstra::source
     * @sa dijkstra::weigths
     * @sa algorithm::check
     */
    [[nodiscard]]
    virtual auto __cdecl check(graph& G) -> int;
	    
    /**
     * @brief Runs shortest path algorithm on @p G.
     *
     * This should return always algorithm::KGL_OK. The return value only
     * tracks errors that might occur.
     * Afterwards the result of the test can be accessed via access methods.
     *
     * @param G graph
     *
     * @retval algorithm::KGL_OK on success
     * @retval algorithm::KGL_ERROR otherwise
     *
     * @sa algorithm::run
     */
    [[nodiscard]]
    auto __cdecl run(graph& G) -> int;

    /**
     * @brief Returns source %node.
     *
     * @return source %node
     */
    [[nodiscard]]
    auto __cdecl source() const -> node;

    /**
     * @brief Returns target %node if set, <code>node::node()</code> else.
     *
     * @return target %node
     */
    [[nodiscard]]
    auto __cdecl target() const -> node;

    /**
     * @brief Returns whether the storing of the shortest path is enabled.
     * 
     * @return @c true iff the storing of path is enabled.
     *
     * @sa dijkstra::predecessor
     */
    [[nodiscard]]
    auto __cdecl store_path() const -> bool;

    /**
     * @brief Returns whether target is reachable from source.
     *
     * @return @c true iff target was reached from source
     */    
    [[nodiscard]]
    auto __cdecl reached() const -> bool;

    /**
     * @brief Returns the distance from source %node to target %node.
     *
     * @return distance if target is bid_dijkstra::reached, <code>-1.0</code>
     * else
     */
    [[nodiscard]]
    auto __cdecl distance() const -> double;

    /**
     * @brief Returns an iterator to the beginning (to the source %node) of
     * the shortest %node path to target %node.
     *
     * @return beginning %node iterator of the shortest path
     *
     * @sa bid_dijkstra::store_path
     *
     * @note The method requires that path calculation option was
     * enabled during last run.
     */
    [[nodiscard]]
    auto __cdecl shortest_path_nodes_begin() -> shortest_path_node_iterator;

    /**
     * @brief Returns an iterator one after the end (one after target
     * %node) of the shortest %node path to target %node.
     *
     * @return shortest path end %node iterator
     *
     * @sa bid_dijkstra::store_path
     *
     * @note The method requires that path calculation option was
     * enabled during last run.
     */
    [[nodiscard]]
    auto __cdecl shortest_path_nodes_end() -> shortest_path_node_iterator;

    /**
     * @brief Returns an iterator to the beginning %edge of the shortest
     * %edge path to target %node.
     *
     * @sa bid_dijkstra::store_path
     *
     * @return beginning %edge iterator of the shortest path
     *
     * @note The method requires that path calculation option was
     * enabled during last run.
     */
    [[nodiscard]]
    auto __cdecl shortest_path_edges_begin() -> shortest_path_edge_iterator;

    /**
     * @brief Returns an iterator one after the end of a shortest %edge path
     * to target %node.
     *
     * @sa bid_dijkstra::store_path
     *
     * @return shortest path end %edge iterator
     *
     * @note The method requires that predecessor calculation option was
     * enabled during last run.
     */
    [[nodiscard]]
    auto __cdecl shortest_path_edges_end() -> shortest_path_edge_iterator;

    /**
     * @brief Resets Dijkstra's bidirectional algorithm.
     *
     * It prepares the algorithm to be applied again, possibly to another
     * graph.
     *
     * @note The weights are not reset. You can apply this algorithms
     *
     * @sa algorithm::reset
     */
    virtual auto __cdecl reset() -> void;
private:
    /**
     * @internal
     * Stores source.
     * 
     * @sa bid_dijkstra::source.
     */
    node s;

    /**
     * @internal
     * Stores target.
     * 
     * @sa bid_dijkstra::source.
     */
    node t;

    /**
     * @internal
     * Indicates whether weights were set.
     * 
     * @sa bid_dijkstra::weights.
     */
    bool weights_set;

    /**
     * @internal
     * Indicates whether predecessors should be computed.
     * 
     * @sa bid_dijkstra::store_preds.
     */
    bool path_set;

    /**
     * @internal
     * Stores the weights of the %edges.
     * 
     * @sa bid_dijkstra::weights.
     */
    edge_map<double> weight;

    /**
     * @internal
     * Stores distance between @s and @t.
     * (default: -1.0)
     */
    double dist;

    /**
     * @internal
     * Stores if @a t can be reached from @s.
     * (default: false)
     */
    bool reached_t;

    /**
     * @internal
     * Stores predecessor of each %node in shortest path.
     * (default: edge() (if enabled))
     */
    node_map<edge> pred;

    /**
     * @internal
     * Stores successor of each %node in shortest path tree.
     * (default: edge() (if enabled))
     */
    node_map<edge> succ;

    /**
     * @internal
     * Indicates the current %node status.
     * (default: black)
     */
    node_map<int> source_mark;

    /**
     * @internal
     * Indicates the current %node status.
     * (default: black)
     */
    node_map<int> target_mark;

    /**
     * @internal
     * Distance from source @a s.
     * (default: -1.0)
     */
    node_map<double> source_dist;

    /**
     * @internal
     * Distance to target @a t.
     * (default: -1.0)
     */
    node_map<double> target_dist;

    /**
     * @internal
     * Stores for target %node @a t a list of nodes on the shortest path
     * from source @a s to it.
     * (default: empty)
     *
     * @sa dijkstra::shortest_path_nodes_begin
     * @sa dijkstra::shortest_path_nodes_end
     */
    list<node> shortest_path_node_list;

    /**
     * @internal
     * Stores for target %node @a t a list of edges on the shortest path
     * from source @a s to it.
     * (default: empty)
     *
     * @sa dijkstra::shortest_path_edges_begin
     * @sa dijkstra::shortest_path_edges_end
     */
    list<edge> shortest_path_edge_list;

    /**
     * @internal
     * Prepares the %algorithm to be applied once again.
     */
    auto __cdecl reset_algorithm() -> void;
    
    /**
     * @internal
     * Inits data structure.
     */
    auto __cdecl init(graph& G) -> void;

    /**
     * @internal
     * Fills ordered lists @a shortest_path_node_list and @a
     * shortest_path_edge_list with nodes respective edges of shortest path
     * from @a s to @a t. Calculates distance.
     *
     * @param n first white node of the two directions
     */
    auto __cdecl fill_node_edge_lists(const node& n) -> void;
};

__KGL_END_NAMESPACE

#endif // KGL_BID_DIJKSTRA_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
