#include "rb_Lazy_exact_nt.h"
#include <boost/lexical_cast.hpp>

String to_s(Lazy_exact_nt nt){
	string val = boost::lexical_cast<string>(CGAL::to_double(nt));
	return String("<Lazy_exact_nt:" + val + ">");
}

float to_f(Lazy_exact_nt nt){
	return CGAL::to_double(nt);
}


Data_Type<Lazy_exact_nt> define_Lazy_exact_nt(Rice::Module rb_mCGAL ) {

	Data_Type<Lazy_exact_nt> rb_cLazy_exact_nt =
			define_class_under<Lazy_exact_nt>(rb_mCGAL, "Lazy_exact_nt")
			.define_method("to_s", &to_s)
			.define_method("to_f", &to_f)
		;

	return rb_cLazy_exact_nt;
}
