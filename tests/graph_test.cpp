/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   graph_test.cpp
//
//==========================================================================
// $Id: graph_test.cpp,v 1.1 2019/05/07 16:50:46 raitner Exp $ 

#include <iostream>

#include <KGL/graph.h>
#include <KGL/node_map.h>

#ifdef __KGL_MSVCC
#   ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#   endif   // _DEBUG
#endif	// __KGL_MSVCC

int main (int argc, char* argv[])
{
    cout << "Loading graph and preserving ids" << endl;
    graph G;
    if (G.load("test.kgd", true).err_num != KML_OK) {
	cout << "Loading failed" << endl;
	exit(1);
    }

    cout << "Loading OK" << endl;

    if (G.number_of_ids(node()) != 20) {
	cout << "Wrong number of ids: " << G.number_of_ids(node()) << endl;
	exit(1);
    }

    cout << "Number of ids OK" << endl;

    cout << "Loading graph and preserving ids" << endl;
    
    graph G1;
    if (G.load("test.kgd", false).err_num != KML_OK) {
	cout << "Loading failed" << endl;
	exit(1);
    }

    cout << "Loading OK" << endl;

    if (G.number_of_ids(node()) != 2) {
	cout << "Wrong number of ids: " << G.number_of_ids(node()) << endl;
	exit(1);
    }

    cout << "Number of ids OK" << endl;
}
