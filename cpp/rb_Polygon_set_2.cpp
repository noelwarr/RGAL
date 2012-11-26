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

Data_Type<Polygon_set_2> define_Polygon_set_2(Rice::Module rb_mCGAL ) {
	
	Data_Type<Polygon_set_2> rb_cPolygon_set_2 =
		define_class_under<Polygon_set_2>(rb_mCGAL, "Polygon_set_2")
		.define_singleton_method("join", &join)
		.define_method("to_a", &to_a)
	;

	return rb_cPolygon_set_2;
}


