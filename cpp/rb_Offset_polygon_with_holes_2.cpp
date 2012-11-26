#include "rb_Offset_polygon_with_holes_2.h"

Array holes(Offset_polygon_with_holes_2 opwh){
	Array array;
	Offset_polygon_with_holes_2::Hole_const_iterator hci;
	for (hci = opwh.holes_begin(); hci != opwh.holes_end(); ++hci){
		array.push(*hci);
	}
	return array;
}
Offset_polygon_with_holes_2::Polygon_2 outer_boundary(Offset_polygon_with_holes_2 opwh){
	return opwh.outer_boundary();
}
Array to_a(Offset_polygon_with_holes_2 opwh){
	Array array;
	array.push(opwh.outer_boundary());
	Offset_polygon_with_holes_2::Hole_const_iterator hci;
	for (hci = opwh.holes_begin(); hci != opwh.holes_end(); ++hci){
		array.push(*hci);
	}
	return array;
}

Data_Type<Offset_polygon_with_holes_2> define_Offset_polygon_with_holes_2(Rice::Module rb_mCGAL ) {
	Data_Type<Offset_polygon_with_holes_2> rb_cOffset_polygon_with_holes_2 =
			define_class_under<Offset_polygon_with_holes_2>(rb_mCGAL, "Offset_polygon_with_holes_2")
			.define_method("outer_boundary", &outer_boundary)
			.define_method("holes", &holes)
			.define_method("to_a", &to_a)
		;


	return rb_cOffset_polygon_with_holes_2;
}


