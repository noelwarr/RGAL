#include "rb_Circle_2.h"


Circle_2 build_halfcircle(Point_2 p, Point_2 q){
	Circle_2 circle(p, q);
	return circle;
}


Data_Type<Circle_2> define_Circle_2(Rice::Module rb_mCGAL ) {

	Data_Type<Circle_2> rb_cCircle_2 =
		define_class_under<Circle_2>(rb_mCGAL, "Circle_2")
		.define_singleton_method("build_halfcircle", &build_halfcircle)
		.define_method("center", &Circle_2::center)
	;

	return rb_cCircle_2;
}
