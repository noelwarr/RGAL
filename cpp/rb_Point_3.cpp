#include "rb_Point_2.h"




Array to_a(Point_3 p){
	Array point;
	point.push( CGAL::to_double(p.hx()) );
	point.push( CGAL::to_double(p.hy()) );
	point.push( CGAL::to_double(p.hz()) );
	return point;
}

double x(Point_3 p){
	return CGAL::to_double(p.hx());
}

double y(Point_3 p){
	return CGAL::to_double(p.hy());
}

double z(Point_3 p){
	return CGAL::to_double(p.hz());
}

Point_3 build_point_3(float x, float y, float z) {
	return Point_3(x,y,z);
}

// TODO Relocate this method to a more general file, perhaps with general util functions?
/*
 * Returns the orientation of four points in 3D space: whether s is above, below or on the plane defined by (p,q,r)
 * 
 * Returns the int variant of the CGAL::Orientation enum
 * 	-1 for ON_NEGATIVE_SIDE
 *       1 for ON_POSITIVE_SIDE
 *       0 for COPLANAR 
 * 
 */
int orientation(Point_3 p, Point_3 q, Point_3 r, Point_3 s) {
  CGAL::Orientation result = CGAL::orientation(p,q,r,s);
  return (int) result;
}



Data_Type<Point_3> define_Point_3(Rice::Module rb_mCGAL ) {

	Data_Type<Point_3> rb_cPoint_3 =
			define_class_under<Point_3>(rb_mCGAL, "Point_3")
			.define_singleton_method("build", &build_point_3)
			.define_singleton_method("orientation", &orientation)
			.define_method("to_a", &to_a)
			.define_method("x", &x)
			.define_method("y", &y)
			.define_method("z", &z)
		;

	return rb_cPoint_3;
}


