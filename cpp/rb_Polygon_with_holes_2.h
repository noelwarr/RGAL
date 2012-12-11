#ifndef RB_POLYGON_WITH_HOLES_2_H
#define RB_POLYGON_WITH_HOLES_2_H

#include "defs.h"

#include<vector>

#include<boost/shared_ptr.hpp>


#include<CGAL/Polygon_with_holes_2.h>

using namespace std;
using namespace Rice;

Data_Type<Polygon_with_holes_2> define_Polygon_with_holes_2(Rice::Module rb_mCGAL );
 
#endif
