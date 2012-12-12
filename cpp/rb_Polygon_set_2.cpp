#include "rb_Polygon_set_2.h"

Polygon_set_2 join(Array polygons){
	vector<Polygon_2> polygon_vector;
	for (unsigned int i = 0; i < polygons.size(); i++) {
		Polygon_2 polygon = from_ruby<Polygon_2>(polygons[i]);
		if (polygon.is_simple()) {
			polygon_vector.push_back(polygon);
		}
	}
	Polygon_set_2 S;
	S.join(polygon_vector.begin(), polygon_vector.end());
	return S;
}

// Returns a new polygon set that is equal to joining polySet1 and polySet2
Polygon_set_2 join_polygon_sets(Polygon_set_2 polySet1, Polygon_set_2 polySet2){
	Polygon_set_2 S(polySet1);
	S.join(polySet2);
	return S;
}


// Returns a new polygon set that is equal to polySet1.difference(polySet2)
Polygon_set_2 difference_polygon_sets(Polygon_set_2 polySet1, Polygon_set_2 polySet2){

	Polygon_set_2 S(polySet1);
	S.difference(polySet2);
	return S;
}

// Returns a new polygon set that is equal to poly1.difference(poly2)
Polygon_set_2 difference_polygons(Polygon_2 poly1, Polygon_2 poly2){

	Polygon_set_2 pset1 (poly1);
	Polygon_set_2 pset2 (poly2);
	pset1.difference(pset2);
	return pset1;
}

// Returns a new polygon set that is equal to poly1.difference(poly2)
Polygon_set_2 difference_polygons_with_holes(Polygon_with_holes_2 poly1, Polygon_with_holes_2 poly2){

	Polygon_set_2 pset1 (poly1);
	Polygon_set_2 pset2 (poly2);
	pset1.difference(pset2);
	return pset1;
}

Array to_a(Polygon_set_2 S){
	Array ps;	
	list<Polygon_with_holes_2> res;
  list<Polygon_with_holes_2>::const_iterator it;
	S.polygons_with_holes (back_inserter (res));
  for (it = res.begin(); it != res.end(); ++it){
		Polygon_with_holes_2 pwh = *it;
		ps.push(pwh);
  }
	return ps;
}

bool is_empty(Polygon_set_2 S) {
    return S.is_empty();
}

Data_Type<Polygon_set_2> define_Polygon_set_2(Rice::Module rb_mCGAL ) {
	
	Data_Type<Polygon_set_2> rb_cPolygon_set_2 =
		define_class_under<Polygon_set_2>(rb_mCGAL, "Polygon_set_2")
		.define_singleton_method("join", &join)
		.define_singleton_method("join_polygon_sets", &join_polygon_sets)
		.define_singleton_method("difference_polygons", &difference_polygons)
		.define_singleton_method("difference_polygons_with_holes", &difference_polygons_with_holes)
		.define_singleton_method("difference_polygon_sets", &difference_polygon_sets)
		.define_method("to_a", &to_a)
		.define_method("is_empty", &is_empty)

	;

	return rb_cPolygon_set_2;
}


