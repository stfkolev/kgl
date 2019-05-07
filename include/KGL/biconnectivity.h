/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   biconnectivity.h
//
//==========================================================================
// $Id: biconnectivity.h,v 1.18 2019/05/07 13:37:14 raitner Exp $

#ifndef KGL_BICONNECTIVITY_H
#define KGL_BICONNECTIVITY_H

#include <KGL/KGL.h>
#include <KGL/dfs.h>

#include <list>
#include <stack>

__KGL_BEGIN_NAMESPACE

/**
 * $Date: 2019/05/07 13:37:14 $
 * $Revision: 1.18 $
 * 
 * @brief Biconnectivity-test and low-numbers.
 *
 * Obviously there is a close relationship between DFS and the testing of
 * biconnectivity. Thus this test takes advantage of the possibility to 
 * add pieces of code to the DFS-class in order to calculate the
 * low-numbers. 
 * 
 * As default no biconnected components will be stored and no edges 
 * will be added to make the graph biconnected. The test will run on the
 * whole graph, even if it is not connected. 
 */

class KGL_EXTERN biconnectivity : public dfs 
{
public:
    /**
     * @brief Creates biconnectivity algorithm object.
     * 
     * @see dfs::dfs
     */
    biconnectivity ();

    /**
     * @brief Destroys biconnectivity algorithm object.
     *
     * @see dfs::~dfs
     */
    virtual ~biconnectivity () {}

    /**
     * @brief Checks whether the algorithm can be applied.
     * 
     * Necessary preconditions:
     *   - G is undirected.
     *   - storing of predecessors is enabled.
     *   - DFS may be applied 
     * 
     * @param G graph.
     * @return algorithm::KGL_OK if binconnectivity-test can
     * be applied to @a G.
     * @sa dfs::scan_whole_graph, dfs::store_preds
     */
    [[nodiscard]]
    virtual auto __cdecl check (graph& G) -> int;

    virtual auto __cdecl reset () -> void;

    /**
     * @brief low-number. 
     *
     * @param n node.
     * @return low-number of n.
     */
    [[nodiscard]]
    auto __cdecl low_number (const node& n) const -> int
	{return low_num[n];}

    /**
     * @brief Biconnectivity-test. 
     * 
     * @return true iff graph is biconnected.
     */
    [[nodiscard]]
    auto __cdecl is_biconnected () const -> bool
	{return num_of_components == 1;}

    /**
     * @brief Returns whether the storing of components is enabled.
     * 
     * @return true iff storing of components is enabled.
     * @sa biconnectivity::components_begin, biconnectivity::components_end
     */
    [[nodiscard]]
    auto __cdecl store_components () const -> bool
	{ return store_comp; }

    /**
     * @brief Enables or disables the storing of biconnected components.
     *
     * If this feature is enabled, the whole graph will be scanned
     * in order to get all the biconnected components even if the graph
     * isn't connected. By default this feature is disabled.
     * 
     * @param set if true each biconnected component will be stored.
     * @sa biconnectivity::components_begin, biconnectivity::components_end
     */
    auto __cdecl store_components (bool set) -> void
	{ store_comp  = set; if (set) scan_whole_graph (set); }
    
    /**
     * @brief If enabled edges will be added to the graph in order to make it 
     * biconnected, if cutpoints are discovered.
     * 
     * The list of added edges can be accessed via additional_begin and
     * additional_end.
     *
     * @param set if true additional edges will we inserted
     *    to make the graph biconnected.
     * @sa biconnectivity::additional_begin, biconnectivity::additional_end
     */
    auto __cdecl make_biconnected (bool set) -> void
	{ add_edges = set; if (set) scan_whole_graph (set); }
    
    /**
     * @brief Returns whether addition of edges neccessary to make graph
     * biconnected is enabled. 
     * 
     * @return true iff addition edges is enabled.
     * @sa biconnectivity::additional_begin, biconnectivity::additional_end
     */
    [[nodiscard]]
    auto __cdecl make_biconnected () const -> bool
	{ return add_edges; }
    
    /**
     * @brief Begin of edges added to make graph biconnected.
     * 
     * @return begin of additional edges
     * @sa biconnectivity::make_biconnected
     */
    [[nodiscard]]
    auto __cdecl additional_begin () -> list<edge>::iterator
	{ return additional.begin (); }

    /**
     * @brief End of edges added to make graph biconnected
     * 
     * @return end of additional edges
     * @sa biconnectivity::make_biconnected
     */
    [[nodiscard]]
    auto __cdecl additional_end () -> list<edge>::iterator
	{ return additional.end (); }
    
    /**
     * @internal
     */
    typedef list<node>::iterator cutpoint_iterator;

    /**
     * @brief Start iteration over all cutpoints found.
     *
     * A cutpoints is a node whose removal will disconnect the graph,
     * thus a graph with no cutpoints is biconnected and vice versa.
     * 
     * @return iterator to first cutpoint.
     * @sa biconnectivity::cut_points_end
     */
    [[nodiscard]]
    auto __cdecl cut_points_begin () -> cutpoint_iterator
	{ return cut_points.begin(); }

    /**
     * @brief End of iteration over all cutpoints.
     * 
     * @return one-past-the-end iterator.
     * @sa biconnectivity::cut_points_begin
     */
    [[nodiscard]]
    auto __cdecl cut_points_end () -> cutpoint_iterator
	{ return cut_points.end(); }


    /**
     * @internal
     */
    typedef list<pair<list<node>, list<edge> > >::iterator component_iterator;

    /**
     * @brief Start iteration over all biconnected components (if enabled during
     * last call to run).
     *
     * Components are represented as a pair consisting of
     * a list of nodes and a list of edges,
     * i.e. if it is of type component_iterator
     * then *it is of type 
     * pair&lt;list&lt;node&gt;,list&lt;edge&gt; &gt;. 
     *
     * @return iterator to first component
     * @sa biconnectivity::store_components
     */
    [[nodiscard]]
    auto __cdecl components_begin () -> component_iterator
	{ return components.begin(); }


    /**
     * @brief End of iteration over all biconnected components.
     *
     * @return end of iteration over biconnected components
     * @sa biconnectivity::store_components
     */
    auto __cdecl components_end () -> component_iterator
	{ return components.end(); }

    /**
     * @brief Number von biconnected components detected during the last run.
     * 
     * @return number of biconnected components.
     */
    [[nodiscard]]
    auto __cdecl number_of_components () const -> int
	{return num_of_components; }

    //-----------------------------------------------------------------------
    //   Handler used to extend dfs to biconnectivity
    //-----------------------------------------------------------------------
    /**
     * @internal
     */
    virtual auto __cdecl init_handler (graph&) -> void;

    /**
     * @internal
     */
    virtual auto __cdecl entry_handler (graph&, node&, node&) -> void;

    /**
     * @internal
     */
    virtual auto __cdecl before_recursive_call_handler (graph&, edge&, node&) -> void;

    /**
     * @internal
     */
    virtual auto __cdecl after_recursive_call_handler (graph&, edge&, node&) -> void;

    /**
     * @internal
     */
    virtual auto __cdecl old_adj_node_handler (graph&, edge&, node&) -> void;

    /**
     * @internal
     */
    virtual auto __cdecl new_start_handler (graph&, node&) -> void;    

    /**
     * @internal
     */
    virtual auto __cdecl leave_handler (graph&, node&, node&) -> void;    

    /**
     * @internal
     */
    virtual auto __cdecl end_handler (graph&) -> void;    


protected:
    /**
     * @internal
     */
    list<edge> self_loops;

    /**
     * @internal
     */
    node_map<component_iterator> in_component;

    /**
     * @internal
     */
    node_map<int> low_num;
    /**
     * @internal
     */
    int num_of_components;
    /**
     * @internal
     */
    bool store_comp;
    /**
     * @internal
     */
    bool add_edges;
    /**
     * @internal
     */
    node last;
    /**
     * @internal
     */
    stack<node> node_stack;
    /**
     * @internal
     */
    stack<edge> edge_stack;
    /**
     * @internal
     */
    list<pair<list<node>, list<edge> > > components;
    /**
     * @internal
     */
    list<node> cut_points;
    /**
     * @internal
     */
    node_map<int> cut_count;
    /**
     * @internal
     */
    list<edge> additional;
    /**
     * @internal
     */
    node_map<node> first_child;
};

__KGL_END_NAMESPACE

#endif // KGL_BICONNECTIVITY_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
