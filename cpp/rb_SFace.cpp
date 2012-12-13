#include "rb_Halfedge.h"

Data_Type<SFace> define_SFace(Rice::Module rb_mCGAL ) {

	Data_Type<SFace> rb_cSFace =
		define_class_under<SFace>(rb_mCGAL, "SFace")

	;
	return rb_cSFace;
}