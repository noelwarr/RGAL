#include "rb_Halffacet.h"

Array cycles(Halffacet hf){
	vector<SHalfedge> oh;
	Nef_polyhedron_3::Halffacet_cycle_iterator hfci;
	for (hfci = hf.facet_cycles_begin(); hfci != hf.facet_cycles_end(); ++hfci){
		if (hfci.is_shalfedge()){
			SHalfedge she(hfci);
			oh.push_back(she);
			for (SHalfedge i = she->next(); i->source() != she->source(); i = i->next()){
				oh.push_back(i);
			}
		}
  }
	Array out(oh.begin(), oh.end());
	return out;
}

Data_Type<Halffacet> define_Halffacet(Rice::Module rb_mCGAL ) {

	Data_Type<Halffacet> rb_cHalffacet =
		define_class_under<Halffacet>(rb_mCGAL, "Halffacet")
		.define_method("shalfedges", &cycles)	
	;

	return rb_cHalffacet;
}


