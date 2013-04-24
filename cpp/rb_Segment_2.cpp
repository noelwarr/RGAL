#include "rb_Segment_2.h"

Point_2 source(Segment_2 xmc){
	Segment_2::Point_2 pt = xmc.source();
	Point_2 point(CGAL::to_double(pt.x()),
								CGAL::to_double(pt.y()));
	return point;
}
Point_2 target(Segment_2 xmc){
	Segment_2::Point_2 pt = xmc.target();
	Point_2 point(CGAL::to_double(pt.x()),
								CGAL::to_double(pt.y()));
	return point;
}
Point_2 center(Segment_2 xmc){
	Kernel::Circle_2 circle = xmc.supporting_circle();
	return circle.center();
}
double radius(Segment_2 xmc){
	Kernel::Circle_2 circle = xmc.supporting_circle();
	return sqrt(CGAL::to_double(circle.squared_radius()));
}
String orientation(Segment_2 xmc){
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

Segment_2 build_curve(Circle_2 c, Point_2 s, Point_2 t, Symbol orientation){
	const Circle_2 cconst = c;
	const Point_2 sconst = s;
	const Point_2 tconst = t;
	Segment_2 seg = Segment_2();//cconst, sconst, tconst, c.orientation(), (unsigned int)1);
	return seg;
}

Data_Type<Segment_2> define_Segment_2(Rice::Module rb_mCGAL ) {

	Data_Type<Segment_2> rb_cSegment_2 =
		define_class_under<Segment_2>(rb_mCGAL, "Segment_2")
		.define_singleton_method("build_curve", &build_curve)
		.define_method("linear?", &Segment_2::is_linear)
		.define_method("circular?", &Segment_2::is_circular)
		.define_method("orientation", &orientation)			
		.define_method("radius", &radius)
		.define_method("source", &source)
		.define_method("target", &target)
		.define_method("center", &center)
		;

	return rb_cSegment_2;
}


