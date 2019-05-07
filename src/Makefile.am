#===========================================================================
#
#   src/Makefile.am
#
#===========================================================================
# $Id: Makefile.am,v 1.37 2019/05/07 08:58:09 Exp $

lib_LTLIBRARIES = libKGL.la

INCLUDES = \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/include

libKGL_la_LDFLAGS = \
	-version-info $(GENERIC_LIBRARY_VERSION) 

libKGL_la_SOURCES =        \
        kml_scanner.cpp    \
        kml_parser.cpp     \
        edge.cpp           \
        graph.cpp          \
        node.cpp           \
	dfs.cpp 	   \
	biconnectivity.cpp \
	bfs.cpp            \
	topsort.cpp        \
	st_number.cpp      \
	embedding.cpp	   \
	pq_node.cpp	   \
	pq_tree.cpp	   \
	planarity.cpp 	   \
	maxflow_ff.cpp     \
	maxflow_pp.cpp     \
	maxflow_sap.cpp    \
	debug.cpp          \
	components.cpp     \
	fm_partition.cpp   \
	ratio_cut_partition.cpp \
	min_tree.cpp \
	dijkstra.cpp \
	bellman_ford.cpp	\
	bid_dijkstra.cpp

#---------------------------------------------------------------------------
#   end of file
#---------------------------------------------------------------------------

