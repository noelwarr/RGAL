#include "rb_Point_2.h"

Array to_a(Point_2 p){
	Array point;
	point.push( CGAL::to_double(p.hx()) );
	point.push( CGAL::to_double(p.hy()) );
	return point;
}

double x(Point_2 p){
	return CGAL::to_double(p.hx());
}

double y(Point_2 p){
	return CGAL::to_double(p.hy());
}

Point_2 build_point_2(float x, float y) {
	return Point_2(x,y);
}


/*
 * Returns the orientation of three points in 2D: whether p,q,r turns left, right or are colinear
 * Return value:
 *  	RIGHT_TURN = -1, LEFT_TURN = 1, COLINEAR = 0
 * 
 */
int orientation(Point_2 p, Point_2 q, Point_2 r) {
  CGAL::Orientation result = CGAL::orientation(p,q,r);
  return (int) result;
}

Data_Type<Point_2> define_Point_2(Rice::Module rb_mCGAL ) {

	Data_Type<Point_2> rb_cPoint_2 =
			define_class_under<Point_2>(rb_mCGAL, "Point_2")
			.define_singleton_method("build", &build_point_2)
			.define_singleton_method("orientation", &orientation)
			.define_method("to_a", &to_a)
			.define_method("x", &x)
			.define_method("y", &y)
		;

	return rb_cPoint_2;
}


