/* This software is distributed under the GNU Lesser General Public License */
//==========================================================================
//
//   algorithm.h 
//
//==========================================================================
// $Id: algorithm.h,v 1.14 2019/05/07 15:58:54 raitner Exp $

#ifndef KGL_ALGORITHM_H
#define KGL_ALGORITHM_H

#include "KGL/KGL.h"
#include "KGL/graph.h"

__KGL_BEGIN_NAMESPACE

/**
 * $Date: 2019/05/07 15:58:54 $
 * $Revision: 1.14 $
 *
 * @brief Abstract baseclass for all algorithm-classes.
 */
class KGL_EXTERN algorithm {
public:
    /** 
     * @var algorithm::KGL_OK 
     * Used as (positive) return value of algorithm::check and 
     * algorithm::run.
     */

    /** 
     * @var algorithm::KGL_ERROR 
     * Used as (negative) return value of algorithm::check and 
     * algorithm::run.
     */

    /**
     * @brief Return values for algorithm::check and algorithm::run
     */
    enum {
	KGL_OK = 1,
	KGL_ERROR = 0
    };

    /**
     * @brief Creates an algorithm object.
     */
    algorithm () { };
    
    /**
     * @brief Destroys the algorithm object.
     */
    virtual ~algorithm () { };    

    /**
     * @brief Applies %algorithm to %graph g. 
     * 
     * @param g %graph
     * @retval algorithm::KGL_OK on success
     * @retval algorithm::KGL_ERROR otherwise
     */
    [[nodiscard]]
    virtual auto __cdecl run (graph& g) = 0 -> int;
    
    /**
     * @brief Checks whether all preconditions are satisfied.
     * 
     * @em Please @em note: It is
     * definitly required (and #run relies on it),
     * that this method was called in advance.
     * 
     * @param g %graph
     * @retval algorithm::KGL_OK if %algorithm can be applied
     * @retval algorithm::KGL_ERROR otherwise.
     */
    [[nodiscard]]
    virtual auto __cdecl check (graph& g) = 0 -> int;
    
    /**
     * @brief Resets %algorithm 
     * 
     * Prepares the %algorithm to be applied to
     * another %graph. @em Please @em note: The options an
     * %algorithm may support do @em not get reset by
     * this. It is just to reset internally used datastructures.
     */
    virtual auto __cdecl reset () = 0 -> void;
};

__KGL_END_NAMESPACE

#endif // KGL_ALGORITHM_H

//--------------------------------------------------------------------------
//   end of file
//--------------------------------------------------------------------------
