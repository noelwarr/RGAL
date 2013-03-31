#include "rb_Polygon_with_holes_2.h"

Polygon_with_holes_2 build_polygon_with_holes_2(Array array) {
	Polygon_2 outer_boundary = from_ruby<Polygon_2>(array[0]);
	vector<Polygon_2> holes;
	for (unsigned int i = 1; i != array.size(); ++i){
		Polygon_2 hole = from_ruby<Polygon_2>(array[i]);
		holes.push_back(hole);
	}
	return Polygon_with_holes_2(outer_boundary, holes.begin(), holes.end());
}


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
  const double err_bound = 0.01;
  Offset_polygon_with_holes_2  offset;
  offset = approximated_offset_2 (pwh, radius, err_bound);
	return offset;
}

/*
 * Returns the area of a polygon with holes (taking holes into account)
 */
double area(Polygon_with_holes_2 pwh) {

	Polygon_2 boundary = pwh.outer_boundary();

	// Area of outer boundary
	double totalArea = CGAL::to_double(boundary.area());

	// Add area of holes (that should be negative)
	Polygon_with_holes_2::Hole_const_iterator vci;
	for (vci = pwh.holes_begin(); vci != pwh.holes_end(); ++vci) {
		totalArea += CGAL::to_double(vci->area());
	}
	return totalArea;
}


Data_Type<Polygon_with_holes_2> define_Polygon_with_holes_2(Rice::Module rb_mCGAL ) {
	
			Data_Type<Polygon_with_holes_2> rb_cPolygon_with_holes_2 =
			define_class_under<Polygon_with_holes_2>(rb_mCGAL, "Polygon_with_holes_2")
			.define_singleton_method("build", &build_polygon_with_holes_2)
			.define_method("outer_boundary", &outer_boundary)
			.define_method("holes", &holes)
			.define_method("offset", &offset)
			.define_method("to_a", &to_a)
			.define_method("area", &area)
		;

	return rb_cPolygon_with_holes_2;
}


