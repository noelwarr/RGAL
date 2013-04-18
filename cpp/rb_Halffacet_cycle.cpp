#include "rb_Halffacet_cycle.h"

Array points(Halffacet_cycle cycle){
	Array points;
	if (cycle.is_shalfedge()){
		SHalfedge she(cycle);
		Nef_polyhedron_3::SHalfedge_around_facet_const_circulator hc_start(she);
		Nef_polyhedron_3::SHalfedge_around_facet_const_circulator hc_end(hc_start);
		CGAL_For_all(hc_start,hc_end) {
			points.push(hc_start->source()->center_vertex()->point());
		}
	}
	return points;
}

Data_Type<Halffacet_cycle> define_Halffacet_cycle(Rice::Module rb_mCGAL ) {

	Data_Type<Halffacet_cycle> rb_cHalffacet_cycle =
		define_class_under<Halffacet_cycle>(rb_mCGAL, "Halffacet_cycle")
		.define_method("points", &points)
	;

	return rb_cHalffacet_cycle;
}


