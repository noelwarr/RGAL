#include "rb_Plane_3.h"

bool face_up(Plane_3 plane){
	return plane.orthogonal_vector()[2] > 0;
}

bool face_down(Plane_3 plane){
	return plane.orthogonal_vector()[2] < 0;
}

Data_Type<Plane_3> define_Plane_3(Rice::Module rb_mCGAL ) {

	Data_Type<Plane_3> rb_cPlane_3 =
		define_class_under<Plane_3>(rb_mCGAL, "Plane_3")
		.define_method("face_up?", &face_up)
		.define_method("face_down?", &face_down)
	;

	return rb_cPlane_3;
}


