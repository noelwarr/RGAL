#include "rb_Nef_polyhedron_3.h"
#include "rb_Vertex.h"
#include "rb_Halffacet.h"
#include "rb_SHalfedge.h"
#include "rb_SVertex.h"
#include "rb_Point_2.h"
#include "rb_Point_3.h"
#include "rb_X_monotone_curve_2.h"
#include "rb_Offset_polygon_with_holes_2.h"
#include "rb_Offset_polygon_2.h"
#include "rb_Polygon_set_2.h"
#include "rb_Polygon_with_holes_2.h"
#include "rb_Polygon_2.h"
#include "rb_Iso_cuboid_3.h"
#include "rb_Lazy_exact_nt.h"
#include "rb_Aff_transformation_3.h"

#include "defs.h"

using namespace std;
using namespace Rice;

Nef_polyhedron_3 minkowski_sum_3 (Nef_polyhedron_3 N1, Nef_polyhedron_3 N2){
	Nef_polyhedron_3 N = CGAL::minkowski_sum_3(N1, N2);
	return N;
}


extern "C"
void Init_cgal(void)
{
  RUBY_TRY
  {
		Rice::Module rb_mCGAL = define_module("CGAL")
			.define_module_function("minkowski_sum_3", &minkowski_sum_3);
		
		Data_Type<Nef_polyhedron_3> rb_cNef_polyhedron_3 =
			define_Nef_polyhedron_3(rb_mCGAL);

		Data_Type<Vertex> rb_cVertex =
			define_Vertex(rb_mCGAL);		

		Data_Type<Halffacet> rb_cHalffacet =
			define_Halffacet(rb_mCGAL);
		
		Data_Type<SHalfedge> rb_cSHalfedge =
			define_SHalfedge(rb_mCGAL);		

		Data_Type<SVertex> rb_cSVertex =
			define_SVertex(rb_mCGAL);		

		Data_Type<Point_3> rb_cPoint_3 =
			define_Point_3(rb_mCGAL);

		Data_Type<Point_2> rb_cPoint_2 =
			define_Point_2(rb_mCGAL);
		
		Data_Type<X_monotone_curve_2> rb_cX_monotone_curve_2 =
			define_X_monotone_curve_2(rb_mCGAL);

		Data_Type<Offset_polygon_with_holes_2> rb_cOffset_polygon_with_holes_2 =
			define_Offset_polygon_with_holes_2(rb_mCGAL);

		Data_Type<Offset_polygon_2> rb_cOffset_polygon_2 =
			define_Offset_polygon_2(rb_mCGAL);

		Data_Type<Polygon_set_2> rb_cPolygon_set_2 =
			define_Polygon_set_2(rb_mCGAL);

		Data_Type<Polygon_with_holes_2> rb_cPolygon_with_holes_2 =
			define_Polygon_with_holes_2(rb_mCGAL);

		Data_Type<Polygon_2> rb_cPolygon_2 =
			define_Polygon_2(rb_mCGAL);

		Data_Type<Iso_cuboid_3> rb_cIso_cuboid_3 =
			define_Iso_cuboid_3(rb_mCGAL);

		Data_Type<Lazy_exact_nt> rb_cLazy_exact_nt =
			define_Lazy_exact_nt(rb_mCGAL);
			
		Data_Type<Aff_transformation_3> rb_Aff_transformation_3 =
			define_Aff_transformation_3(rb_mCGAL);
		
  }
  RUBY_CATCH
}

