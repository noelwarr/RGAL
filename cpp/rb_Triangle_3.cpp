#include "rb_Triangle_3.h"


Triangle_3 build(Point_3 p1, Point_3 p2, Point_3 p3){
	return Triangle_3(p1, p2, p3);
}

bool is_degenerate(Triangle_3 triangle){
	return triangle.is_degenerate();
}

Data_Type<Triangle_3> define_Triangle_3(Rice::Module rb_mCGAL ) {

	Data_Type<Triangle_3> rb_cTriangle_3 =
		define_class_under<Triangle_3>(rb_mCGAL, "Triangle_3")
		.define_singleton_method("build", &build)
		.define_method("degenerate?", &Triangle_3::is_degenerate)
	;
	return rb_cTriangle_3;
}