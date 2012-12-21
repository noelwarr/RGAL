#include "rb_Polygon_2.h"

const double MIN_DIFF = 0.0001; // Difference in coordinates to consider two consecutive points too close

/*
 * Internal use only (use build/build_after_filtering instead)
 * Builds a new Polygon_2 with the points specified in points
 * If filter=true, it filters consecutive points that are too close to each other
 */
Polygon_2 build(Array points/*, bool filter=false*/){
	Polygon_2 polygon;
	/*double prevX = 0, prevY = 0;*/
	for (unsigned int i = 0; i < points.size(); i++) {
		//Point_2 point = from_ruby<double>points[i];
		/*double x = from_ruby<double>(coordinate[0]);
		double y = from_ruby<double>(coordinate[1]);
		double diffX = x-prevX;
		double diffY = y-prevY;
		// If filtering: skip point if difference is too small (can produce a degenate segment)
		if (!filter || (diffX*diffX > MIN_DIFF*MIN_DIFF || diffY*diffY > MIN_DIFF*MIN_DIFF)) { */
		  //Point_2 point(x,y);
		  polygon.push_back(from_ruby<Point_2>(points[i]));
		//}
		/*prevX = x;
		prevY = y;*/
	}
	return polygon;
}

/*
 * Same as build() but filtering consecutive points that are too close between each other
 */
/*
Polygon_2 build_after_filtering(Array points){
	
	return build_polygon(points, true);
}*/


/*
 * Builds a new Polygon_2 with akk the points specified in points
 *
 */
 /*
Polygon_2 build(Array points){
	return  build_polygon(points, false);
}
*/
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
		//.define_singleton_method("build_after_filtering", &build_after_filtering)
		.define_method("simple?", &Polygon_2::is_simple)
		.define_method("clockwise?", &Polygon_2::is_clockwise_oriented)
		.define_method("counterclockwise?", &Polygon_2::is_counterclockwise_oriented)
		.define_method("collinear?", &Polygon_2::is_collinear_oriented)
		.define_method("area", &Polygon_2::area)
		.define_method("to_a", &to_a)
	;

	return rb_cPolygon_2;
}


