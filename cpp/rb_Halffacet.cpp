#include "rb_Halffacet.h"

Array facet_cycles(Halffacet hf){
	vector<Halffacet_cycle> hfcs;
	Halffacet_cycle hfc;
	for (hfc = hf->facet_cycles_begin(); hfc != hf->facet_cycles_end(); ++hfc){
		hfcs.push_back(hfc);
	}
	Array cycles(hfcs.begin(), hfcs.end());
	return cycles;
}

Plane_3 plane(Halffacet hf){
	return hf->plane();
}

bool mark(Halffacet hf){ return hf->mark(); }
Halffacet twin(Halffacet hf){ return hf->twin(); }

Data_Type<Halffacet> define_Halffacet(Rice::Module rb_mCGAL ) {

	Data_Type<Halffacet> rb_cHalffacet =
		define_class_under<Halffacet>(rb_mCGAL, "Halffacet")
		.define_method("facet_cycles", &facet_cycles)
		.define_method("mark", &mark)	
		.define_method("twin", &twin)
		.define_method("plane", &plane)
	;

	return rb_cHalffacet;
}