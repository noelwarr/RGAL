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

Data_Type<Point_3> define_Point_3(Rice::Module rb_mCGAL ) {

	Data_Type<Point_3> rb_cPoint_3 =
			define_class_under<Point_3>(rb_mCGAL, "Point_3")
			.define_singleton_method("build", &build_point_3)
			.define_method("to_a", &to_a)
			.define_method("x", &x)
			.define_method("y", &y)
			.define_method("z", &z)
		;

	return rb_cPoint_3;
}


