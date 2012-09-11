#include "rb_Polygon_2.h"

Polygon_2 build(Array points){
	Polygon_2 polygon;
	for (unsigned int i = 0; i < points.size(); i++) {
		Array coordinate = Array(points[i]);
		Point_2 point(
				from_ruby<double>(coordinate[0]),
				from_ruby<double>(coordinate[1]));
		polygon.push_back(point);
	}
	return polygon;
}

Array to_a(Polygon_2 polygon){
	Array points;
	Polygon_2::Vertex_iterator vit;
  for (vit = polygon.vertices_begin(); vit != polygon.vertices_end(); ++vit){
		Point_2 point = *vit;
		points.push(point);
	}
	return points;
}

Data_Type<Polygon_2> define_Polygon_2(Rice::Module rb_mCGAL ) {

	Data_Type<Polygon_2> rb_cPolygon_2 =
		define_class_under<Polygon_2>(rb_mCGAL, "Polygon_2")
		.define_singleton_method("build", &build)
		.define_method("simple?", &Polygon_2::is_simple)
		.define_method("clockwise?", &Polygon_2::is_clockwise_oriented)
		.define_method("counterclockwise?", &Polygon_2::is_counterclockwise_oriented)
		.define_method("collinear?", &Polygon_2::is_collinear_oriented)
		.define_method("to_a", &to_a)
	;

	return rb_cPolygon_2;
}


