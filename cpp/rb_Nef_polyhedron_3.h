#ifndef RB_NEF_POLYHEDRON_3_H
#define RB_NEF_POLYHEDRON_3_H

#include "defs.h"

#include <CGAL/basic.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/IO/Qt_widget_Nef_3.h>
#include <qapplication.h>

using namespace std;
using namespace Rice;

Data_Type<Nef_polyhedron_3> define_Nef_polyhedron_3(Rice::Module rb_mCGAL);
 
#endif
