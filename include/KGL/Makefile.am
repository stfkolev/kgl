#===========================================================================
#
#   include/KGL/Makefile.am
#
#===========================================================================
# $Id: Makefile.am,v 1.28 2019/05/07 08:58:08 chris Exp $

BUILT_SOURCES = version.h

pkginclude_HEADERS =				\
	KGL_.h					\
	algorithm.h				\
	bfs.h					\
	biconnectivity.h			\
	debug.h					\
	dfs.h					\
	edge.h					\
	edge_data.h				\
	edge_map.h				\
	embedding.h				\
	kml_parser.h				\
	kml_scanner.h				\
	graph.h					\
	ne_map.h				\
	node.h					\
	node_data.h				\
	node_map.h				\
	planarity.h				\
	pq_node.h				\
	pq_tree.h				\
	st_number.h				\
	symlist.h				\
	topsort.h				\
	maxflow_ff.h                		\
	maxflow_pp.h                      	\
	maxflow_sap.h				\
	components.h 				\
	fm_partition.h                          \
	ratio_cut_partition.h	                \
	min_tree.h	 			\
	dijkstra.h	                        \
	bellman_ford.h				\
	bin_heap.h				\
	bid_dijkstra.h

nodist_pkginclude_HEADERS =			\
	version.h                               


dist-hook: version.h
	cp version.h $(distdir)

#---------------------------------------------------------------------------
#   end of file
#---------------------------------------------------------------------------

