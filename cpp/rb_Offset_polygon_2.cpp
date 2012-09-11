#include "rb_Offset_polygon_2.h"

Array curves(Offset_polygon_2 op){
	Array array;
	Offset_polygon_2::Curve_const_iterator cci;
	for (cci = op.curves_begin(); cci != op.curves_end(); ++cci) {
		array.push(*cci);
	}
	return array;
}

Data_Type<Offset_polygon_2> define_Offset_polygon_2(Rice::Module rb_mCGAL ) {
	
	Data_Type<Offset_polygon_2> rb_cOffset_polygon_2 =
		define_class_under<Offset_polygon_2>(rb_mCGAL, "Offset_polygon_2")
		.define_method("curves", curves)
	;

	return rb_cOffset_polygon_2;
}


