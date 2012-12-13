#include "rb_Halffacet.h"

Array facet_cycles(Halffacet hf){
	Array cycles;
	Nef_polyhedron_3::Halffacet_cycle_const_iterator hfcci;
	for (hfcci = hf->facet_cycles_begin(); hfcci != hf->facet_cycles_end(); ++hfcci){
		if (hfcci.is_shalfedge()){
			SHalfedge she(hfcci);
			vector<SHalfedge> she_vector;
			for (SHalfedge i = she->next(); i->source() != she->source(); i = i->next()){
				she_vector.push_back(i);
			}
			Array she_array(she_vector.begin(), she_vector.end());
			cycles.push(she_array);
		}
  }
	return cycles;
}

bool mark(Halffacet hf){ return hf->mark(); }
Halffacet twin(Halffacet hf){ return hf->twin(); }

Data_Type<Halffacet> define_Halffacet(Rice::Module rb_mCGAL ) {

	Data_Type<Halffacet> rb_cHalffacet =
		define_class_under<Halffacet>(rb_mCGAL, "Halffacet")
		.define_method("facet_cycles", &facet_cycles)
		.define_method("mark", &mark)	
		.define_method("twin", &twin)	
	;

	return rb_cHalffacet;
}