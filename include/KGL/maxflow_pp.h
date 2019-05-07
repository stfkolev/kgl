/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   maxflow_pp.h
//
//==========================================================================
// $Id: maxflow_pp.h,v 1.5 2019/05/07 08:15:05 chris Exp $

#ifndef KGL_MAXFLOW_PP_H
#define KGL_MAXFLOW_PP_H

#include <KGL/KGL.h>
#include <KGL/graph.h>
#include <KGL/node_map.h>
#include <KGL/edge_map.h>
#include <KGL/algorithm.h>

#include <queue>

__KGL_BEGIN_NAMESPACE

/**
 * @short Maximum flow algorithm (Malhotra, Kumar, Maheshwari).
 */
class KGL_EXTERN maxflow_pp : public algorithm
{
public:
    /**
     * Default constructor. Enables only the calculation of
     * maximum flow.
     * 
     * @see algorithm#algorithm
     */
    maxflow_pp();

    /**
     * Destructor.
     * 
     * @see algorithm#~algorithm
     */
    virtual ~maxflow_pp();

    /**
     * Sets capacity of every edge for maximum flow calculation
     * where artificial start-node and end_node will be computed
     * automatically.
     *
     * @param edge_capacity capacity of every edge
     */
    void set_vars(const edge_map<double>& edge_capacity);

    /**
     * Sets capacity of every edge for maximum flow calculation
     *
     * @param edge_capacity capacity of every edge
     * @param net_source start-node
     * @param net_target end-node
     */
    void set_vars(
	const edge_map<double>& edge_capacity, 
	const node& net_source, const node& net_target);

    /**
     * Checks whether following preconditions are satisfied:
     * <ul>
     * <li> @ref maxflow_pp#set_vars has been executed before.
     * <li> only edge_capacities >= 0 are applied.
     * <li> <code>G</code> is directed.
     * <li> <code>G</code> is connected.
     * <li> <code>G</code> has at least one edge and two nodes.
     * <li> if not applied, start-nodes and end-nodes exists.
     * <li> if applied, start-node is not the same node as end-node.
     * </ul>
     * 
     * @param G graph
     * @return <code>algorithm::KGL_OK</code> on success 
     * <code>algorithm::KGL_ERROR</code>
     * otherwise
     * @see algorithm#check
     */
    virtual int check(graph& G);

    /**
     * Computes maximum flow of graph <code>G</code>.
     * 
     * @param G graph
     * @return <code>algorithm::KGL_OK</code> on success 
     * <code>algorithm::KGL_ERROR</code> otherwise 
     * @see algorithm#run
     */
    int run(graph& G);

    /**
     * Returns the maximum flow of an edge.
     *
     * @param e edge of a graph @c G
     * @return maximum flow value
     */
    double get_max_flow(const edge& e) const;

    /**
     * Returns the maximum flow of the whole graph @c G.
     *
     * @return maximum flow value
     */
    double get_max_flow() const;

    /**
     * Returns the remaining free capacity of an edge.
     *
     * @param e edge of a graph G
     * @return remaining capacity
     */
    double get_rem_cap(const edge& e) const;

    /**
     * Resets maximum flow algorithm, i.e. prepares the
     * algorithm to be applied to another graph. 
     * @see algorithm#reset
     */
    virtual void reset();
protected:
    /**
     * @internal
     */
    enum {TARGET_FROM_SOURCE_REACHABLE = 2, TARGET_FROM_SOURCE_NOT_REACHABLE = 3};

    /**
     * @internal
     */
    bool artif_source_target;

    /**
     * @internal
     */
    bool set_vars_executed;

    /**
     * @internal
     */
    double max_graph_flow;

    /**
     * @internal
     */
    node net_source;

    /**
     * @internal
     */
    node net_target;

    /**
     * @internal edges to remove from G after run
     */
    list<edge> edges_not_org;

    /**
     * @internal original edge or inserted back edge
     */
    edge_map<bool> edge_org;

    /**
     * @internal
     */
    edge_map<bool> back_edge_exists;

    /**
     * @internal every edge knows its back edge
     */
    edge_map<edge> back_edge;

    /**
     * @internal
     */
    edge_map<double> edge_capacity;

    /**
     * @internal
     */
    edge_map<double> edge_max_flow;

    /**
     * @internal
     */
    edge_map<double> flow_update;

    /**
     * @internal
     */
    list<edge> full_edges;
		
    /**
     * @internal
     */
    list<node> temp_unvisible_nodes;
		
    /**
     * @internal
     */
    list<edge> temp_unvisible_edges;
		
    /**
     * @internal
     */
    void create_artif_source_target(graph& G);

    /**
     * @internal
     */
    void prepare_run(const graph& G);

    /**
     * @internal
     */
    int leveling(graph& G);

    /**
     * @internal
     */
    void hide_unreachable_nodes(graph& G);

    /**
     * @internal
     */
    void store_temp_unvisible_edges(const node& cur_node);

    /**
     * @internal
     */
    void min_throughput_node(const graph& G, node& min_tp_node, double& min_value);

    /**
     * @internal
     */
    double comp_min_throughput(const node cur_node) const;

    /**
     * @internal every node knows its predecessor then
     */
    void get_sp_ahead(const graph& G, const node& start_node, 
	node_map<edge>& last_edge);

    /**
     * @internal every node knows its successor then
     */
    void get_sp_backwards(const graph& G, const node& start_node, 
	node_map<edge>& prev_edge);

    /**
     * @internal
     */
    void push(graph& G, const node& start_node, const double flow_value);

    /**
     * @internal
     */
    void pull(graph& G, const node& start_node, const double flow_value);

    /**
     * @internal
     */
    void comp_rem_net(graph& G);

    /**
     * @internal
     */
    void single_edge_update(graph& G, edge cur_edge);

    /**
     * @internal
     */
    double extra_charge_ahead(const node& start_node, const 
	node_map<edge>& last_edge) const;

    /**
     * @internal
     */
    double extra_charge_backwards(const node& start_node, 
	const node_map<edge>& prev_edge) const;

    /**
     * @internal
     */
    void create_back_edge(graph& G, const edge& org_edge);

    /**
     * @internal
     */
    void comp_max_flow(const graph& G);

    /**
     * @internal
     */
    void restore_graph(graph& G);
private:
};

__KGL_END_NAMESPACE

#endif // KGL_MAXFLOW_PP_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
