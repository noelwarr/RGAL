#include "rb_Segmented_polygon_with_holes_2.h"

Array holes(Segmented_polygon_with_holes_2 opwh){
	Array array;
	Segmented_polygon_with_holes_2::Hole_const_iterator hci;
	for (hci = opwh.holes_begin(); hci != opwh.holes_end(); ++hci){
		array.push(*hci);
	}
	return array;
}
Segmented_polygon_with_holes_2::Polygon_2 outer_boundary(Segmented_polygon_with_holes_2 opwh){
	return opwh.outer_boundary();
}
Array to_a(Segmented_polygon_with_holes_2 opwh){
	Array array;
	array.push(opwh.outer_boundary());
	Segmented_polygon_with_holes_2::Hole_const_iterator hci;
	for (hci = opwh.holes_begin(); hci != opwh.holes_end(); ++hci){
		array.push(*hci);
	}
	return array;
}

Data_Type<Segmented_polygon_with_holes_2> define_Segmented_polygon_with_holes_2(Rice::Module rb_mCGAL ) {
	Data_Type<Segmented_polygon_with_holes_2> rb_cSegmented_polygon_with_holes_2 =
			define_class_under<Segmented_polygon_with_holes_2>(rb_mCGAL, "Segmented_polygon_with_holes_2")
			.define_method("outer_boundary", &outer_boundary)
			.define_method("holes", &holes)
			.define_method("to_a", &to_a)
		;


	return rb_cSegmented_polygon_with_holes_2;
}


