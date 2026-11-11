#ifndef GTSVECTOR3D_HH
#define GTSVECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Declaration of a template instance
 */

namespace g3d {
  /*!
   * \brief Coordinate names
   */
  enum CooordNames { x_coord = 0, y_coord = 1, z_coord = 2 };
  
  /*!
   * \brief An instance of the template Vector<typename,int> for
   *        3D space
   */
  typedef geom::Vector<double,3>  Vector;
}

#endif
