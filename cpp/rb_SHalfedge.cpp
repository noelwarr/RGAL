#include "rb_SHalfedge.h"

Point_3 source(SHalfedge she){
	return she->source()->point();
}

Point_3 target(SHalfedge she){
	return she->target()->point();
}

SFace incident_sface(SHalfedge she){
	return she->incident_sface();
}

Data_Type<SHalfedge> define_SHalfedge(Rice::Module rb_mCGAL ) {

	Data_Type<SHalfedge> rb_cSHalfedge =
		define_class_under<SHalfedge>(rb_mCGAL, "SHalfedge")
		.define_method("source", &source)
		.define_method("target", &target)
		.define_method("incident_sface", &incident_sface)
	;

	return rb_cSHalfedge;
}


