#include "rb_Halfedge.h"

Vertex source(Halfedge he){ return he->source();}
Vertex target(Halfedge he){ return he->target(); }
bool mark(Halfedge he){ return he->mark(); }
bool is_isolated(Halfedge he){ return he->is_isolated(); }
Vertex center_vertex(Halfedge he){ return he->target(); }
Halfedge twin(Halfedge he){ return he->twin(); }
SFace incident_sface(Halfedge he){ return he->incident_sface(); }

Data_Type<Halfedge> define_Halfedge(Rice::Module rb_mCGAL ) {

	Data_Type<Halfedge> rb_cHalfedge =
		define_class_under<Halfedge>(rb_mCGAL, "Halfedge")
		.define_method("source", &source)
		.define_method("target", &target)
		.define_method("mark", &mark)
		.define_method("isolated?", &is_isolated)
		.define_method("center_vertex", &center_vertex)
		.define_method("twin", &twin)
		.define_method("incident_sface", &incident_sface)
	;
	return rb_cHalfedge;
}