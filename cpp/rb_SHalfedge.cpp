#include "rb_SHalfedge.h"

SVertex source(SHalfedge she){
	return she->source();
}

SVertex target(SHalfedge she){
	return she->target();
}

Data_Type<SHalfedge> define_SHalfedge(Rice::Module rb_mCGAL ) {

	Data_Type<SHalfedge> rb_cSHalfedge =
		define_class_under<SHalfedge>(rb_mCGAL, "SHalfedge")
		.define_method("source", source)
		.define_method("target", target)
	;

	return rb_cSHalfedge;
}


