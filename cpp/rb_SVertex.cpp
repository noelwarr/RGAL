#include "rb_SVertex.h"

/*Point_3 point(SVertex sv){
	Point_3 p(sv->point().x(),
						sv->point().y(),
						sv->point().z());
	return p;
}*/

Data_Type<SVertex> define_SVertex(Rice::Module rb_mCGAL ) {

	Data_Type<SVertex> rb_cSVertex =
		define_class_under<SVertex>(rb_mCGAL, "SVertex")
		//.define_method("point", point)
	;
	return rb_cSVertex;
}