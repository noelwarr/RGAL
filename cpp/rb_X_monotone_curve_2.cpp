#include "rb_X_monotone_curve_2.h"

Point_2 source(X_monotone_curve_2 xmc){
	X_monotone_curve_2::Point_2 pt = xmc.source();
	Point_2 point(CGAL::to_double(pt.x()),
								CGAL::to_double(pt.y()));
	return point;
}
Point_2 target(X_monotone_curve_2 xmc){
	X_monotone_curve_2::Point_2 pt = xmc.target();
	Point_2 point(CGAL::to_double(pt.x()),
								CGAL::to_double(pt.y()));
	return point;
}
Point_2 center(X_monotone_curve_2 xmc){
	Kernel::Circle_2 circle = xmc.supporting_circle();
	return circle.center();
}
double radius(X_monotone_curve_2 xmc){
	Kernel::Circle_2 circle = xmc.supporting_circle();
	return sqrt(CGAL::to_double(circle.squared_radius()));
}
String orientation(X_monotone_curve_2 xmc){
	CGAL::Orientation orientation = xmc.orientation();
	if (orientation == CGAL::CLOCKWISE){
		return "clockwise";
	}
	else if (orientation == CGAL::COUNTERCLOCKWISE){
		return "counter";
	}
	else {
		return "nil";
	}
}


Data_Type<X_monotone_curve_2> define_X_monotone_curve_2(Rice::Module rb_mCGAL ) {

	Data_Type<X_monotone_curve_2> rb_cX_monotone_curve_2 =
		define_class_under<X_monotone_curve_2>(rb_mCGAL, "X_monotone_curve_2")
		.define_method("linear?", &X_monotone_curve_2::is_linear)
		.define_method("circular?", &X_monotone_curve_2::is_circular)
		.define_method("orientation", &orientation)			
		.define_method("radius", &radius)
		.define_method("source", &source)
		.define_method("target", &target)
		.define_method("center", &center)
		;

	return rb_cX_monotone_curve_2;
}


