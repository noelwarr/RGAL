#include "rb_Aff_transformation_3.h"


Aff_transformation_3 build_scaling(float s) // s: scaling factor
{ 
  
  return CGAL::Aff_transformation_3<Kernel>  (CGAL::SCALING, s, 1.0); //to change the 3rd arg., use  build_scaling_full
  
}

Aff_transformation_3 build_scaling_full(float s, float h) //Workaround to have h to be an optional argument, specifying Args was crashing irb
{ 
  
  return CGAL::Aff_transformation_3<Kernel>  (CGAL::SCALING, s, h);
  
}

Aff_transformation_3 build_translation(float x, float y, float z) // (x,y,z): translation vector
{ 
  
  return CGAL::Aff_transformation_3<Kernel>  (CGAL::TRANSLATION, Nef_polyhedron_3::Vector_3(x, y, z));
  
}


Point_3 transform_Point_3(Aff_transformation_3 T, Point_3 p) {
	return T.transform(p);
}


Aff_transformation_3  compose (Aff_transformation_3 t, Aff_transformation_3 s) {
    return t * s;
}

Aff_transformation_3  inverse (Aff_transformation_3 t) {
    return t.inverse();
}


Data_Type<Aff_transformation_3> define_Aff_transformation_3(Rice::Module rb_mCGAL ) {

  /*
   * TODO: Add other methods:
   * 	t.is_even ()
   * 	t.is_odd ()
   *    t.m ( int i, int j) const
   */
  
	Data_Type<Aff_transformation_3> rb_cAff_transformation_3 =
			define_class_under<Aff_transformation_3>(rb_mCGAL, "Aff_transformation_3")
			.define_singleton_method("build_scaling", &build_scaling)
			.define_singleton_method("build_scaling_full", &build_scaling_full)
			.define_singleton_method("build_translation", &build_translation)
			.define_method("*", &compose) 
			.define_method("inverse", &inverse) 
			.define_method("transform_Point_3", &transform_Point_3)
		;

	return rb_cAff_transformation_3;
}


