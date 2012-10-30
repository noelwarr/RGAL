#include "rb_Aff_transformation_3.h"


Aff_transformation_3 build_scaling(float s) // s: scaling factor
{ 
  
  return CGAL::Aff_transformation_3<Kernel>  (CGAL::SCALING, s, 1.0); //to change the 3rd arg., use  build_scaling_full
  
}

 
/*
 * Receives a Ruby array that should contain the 10 or 13 relevant entries of the affine transformation matrix.
 * 
 * See http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Kernel_23_ref/Class_Aff_transformation_3.html for a description.
 */
Aff_transformation_3 build_matrix(Array m) // See CGAL doc 
{ 
    int n = m.size();
    if (n==10 or n==13){
      // Array must have 10 or 13 elements
      
      // Not-so-elegant way to convert Rice Array to an array of Lazy_exact_nt's. 
      Lazy_exact_nt v[n];
      int i=0;
      Array::iterator aI = m.begin();
	Array::iterator aE = m.end();
	while (aI != aE) {
	  double d =  from_ruby<double> (*aI);
	  v[i++]=Lazy_exact_nt(d);
	  ++aI;
	}
      
      if (n==10) 
	return CGAL::Aff_transformation_3<Kernel>  (v[0], v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9]);
      else // 13 elements
	return CGAL::Aff_transformation_3<Kernel>  (v[0], v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12]);
    
    }  else {
      std::cout << "Aff_transformation_3 build_matrix() error: Array argument does not have size 13."<<std::endl;
      return CGAL::Aff_transformation_3<Kernel>  (CGAL::SCALING, 0.0, 1.0); // null matrix (not the neatest thing to return actually)
  
  }
 
}

/*
 *  Prints out the matrix of the transformation.
 * For debugging purposes. TODO: make the method return a ruby matrix
 */
void print_matrix (Aff_transformation_3 t) {
    for (int i=0;i<4;++i) {
      for (int j=0;j<4;++j) {
	cout << t.m(i,j) << " ";
	
      }
      cout << endl;
    }
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

bool  is_even (Aff_transformation_3 t) {
    return t.is_even();
}

bool  is_odd (Aff_transformation_3 t) {
    return t.is_odd();
}

double m (Aff_transformation_3 t, int i, int j) {
    return CGAL::to_double(t.m(i,j));
}

double hm (Aff_transformation_3 t, int i, int j) {
    return CGAL::to_double(t.hm(i,j));
}

Data_Type<Aff_transformation_3> define_Aff_transformation_3(Rice::Module rb_mCGAL ) {
  
	Data_Type<Aff_transformation_3> rb_cAff_transformation_3 =
			define_class_under<Aff_transformation_3>(rb_mCGAL, "Aff_transformation_3")
			.define_singleton_method("build_scaling", &build_scaling)
			.define_singleton_method("build_scaling_full", &build_scaling_full)
			.define_singleton_method("build_translation", &build_translation)
			.define_singleton_method("build_matrix", &build_matrix)
			.define_method("*", &compose) 
			.define_method("inverse", &inverse) 
			.define_method("is_even", &is_even) 
			.define_method("is_odd", &is_odd) 
			.define_method("m", &m) 
			.define_method("hm", &hm)
			.define_method("print_matrix", &print_matrix) // For debugging purposes
			.define_method("transform_Point_3", &transform_Point_3)
		;

	return rb_cAff_transformation_3;
}


