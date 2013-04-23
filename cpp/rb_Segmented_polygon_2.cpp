#include "rb_Segmented_polygon_2.h"

Array curves(Segmented_polygon_2 op){
	Array array;
Segmented_polygon_2::Curve_const_iterator cci;
	for (cci = op.curves_begin(); cci != op.curves_end(); ++cci) {
		array.push(*cci);
	}
	return array;
}

Data_Type<Segmented_polygon_2> define_Segmented_polygon_2(Rice::Module rb_mCGAL ) {
	
	Data_Type<Segmented_polygon_2> rb_Segmented_polygon_2 =
		define_class_under<Segmented_polygon_2>(rb_mCGAL, "Segmented_polygon_2")
		.define_method("curves", curves)
	;

	return rb_Segmented_polygon_2;
}


