#include "rb_Vertex.h"

Point_3 point(Vertex v){ return v->point(); }
bool mark(Vertex v){ return v->mark(); }

Data_Type<Vertex> define_Vertex(Rice::Module rb_mCGAL ) {

	Data_Type<Vertex> rb_cVertex =
		define_class_under<Vertex>(rb_mCGAL, "Vertex")
		.define_method("point", &point)
		.define_method("mark", &point)
	;
	return rb_cVertex;
}


