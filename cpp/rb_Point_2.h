#ifndef RB_POINT_2_H
#define RB_POINT_2_H
 
#include "rice/Data_Type.hpp"
#include "rice/Enum.hpp"
#include "rice/Constructor.hpp"
#include "rice/Class.hpp"
#include "rice/to_from_ruby.hpp"

#include "defs.h"

using namespace std;
using namespace Rice;

Data_Type<Point_2> define_Point_2(Rice::Module rb_mCGAL);
 
#endif
