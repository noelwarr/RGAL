#include "rb_Polygon_with_holes_2.h"

Polygon_2 outer_boundary(Polygon_with_holes_2 pwh) {
	Polygon_2 polygon = pwh.outer_boundary();
	return polygon;
}
Array holes(Polygon_with_holes_2 pwh) {
	Array p2;
	Polygon_2 polygon;
	Polygon_with_holes_2::Hole_const_iterator vci;
  for (vci = pwh.holes_begin(); vci != pwh.holes_end(); ++vci){
		polygon = *vci;
		p2.push(polygon);
  }
	return p2;
}
Array to_a(Polygon_with_holes_2 pwh){
	Array p2;
	Polygon_2 polygon = pwh.outer_boundary();
	p2.push(polygon);
	Polygon_with_holes_2::Hole_const_iterator vci;
  for (vci = pwh.holes_begin(); vci != pwh.holes_end(); ++vci){
		polygon = *vci;
		p2.push(polygon);
  }
	return p2;
}
Offset_polygon_with_holes_2 offset(Polygon_with_holes_2 pwh, double radius){
  const double err_bound = 0.00001;
  Offset_polygon_with_holes_2  offset;
  offset = approximated_offset_2 (pwh, radius, err_bound);
	return offset;
}

Data_Type<Polygon_with_holes_2> define_Polygon_with_holes_2(Rice::Module rb_mCGAL ) {
	
			Data_Type<Polygon_with_holes_2> rb_cPolygon_with_holes_2 =
			define_class_under<Polygon_with_holes_2>(rb_mCGAL, "Polygon_with_holes_2")
			.define_method("outer_boundary", &outer_boundary)
			.define_method("holes", &holes)
			.define_method("offset", &offset)
			.define_method("to_a", &to_a)
		;

	return rb_cPolygon_with_holes_2;
}


