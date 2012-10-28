#ifndef DEFS_H
#define DEFS_H

#include "rice/Data_Type.hpp"
#include "rice/Enum.hpp"
#include "rice/Constructor.hpp"
#include "rice/Class.hpp"
#include "rice/to_from_ruby.hpp"

#include <sstream>
#include <iostream>
#include <math.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#include <CGAL/minkowski_sum_3.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Polygon_set_2.h>
#include <CGAL/approximated_offset_2.h>
#include <CGAL/offset_polygon_2.h>
#include <CGAL/bounding_box.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel	Kernel;
typedef CGAL::Lazy_exact_nt<CGAL::Gmpq>	 									Lazy_exact_nt;
typedef Kernel::Point_2																		Point_2;
typedef Kernel::Point_3																		Point_3;
typedef Kernel::Iso_cuboid_3															Iso_cuboid_3;
typedef CGAL::Polyhedron_3<Kernel>     										Polyhedron_3;
typedef Polyhedron_3::HalfedgeDS													HalfedgeDS;
typedef CGAL::Nef_polyhedron_3<Kernel>  									Nef_polyhedron_3;
typedef Nef_polyhedron_3::Vertex													Vertex;
typedef Nef_polyhedron_3::Halffacet												Halffacet;
typedef Nef_polyhedron_3::SHalfedge_const_handle					SHalfedge;
typedef Nef_polyhedron_3::Object_handle										Object_handle;
typedef Nef_polyhedron_3::SVertex_const_handle						SVertex;

typedef CGAL::Polygon_2<Kernel>  		   										Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>  							Polygon_with_holes_2;
typedef CGAL::Polygon_set_2<Kernel>  											Polygon_set_2;
typedef CGAL::Gps_circle_segment_traits_2<Kernel>  	Gps_traits_2;
typedef Gps_traits_2::Polygon_2                    	Offset_polygon_2;
typedef Gps_traits_2::Polygon_with_holes_2         	Offset_polygon_with_holes_2;
typedef Offset_polygon_2::X_monotone_curve_2				X_monotone_curve_2;
typedef CGAL::Aff_transformation_3<Kernel>	Aff_transformation_3;

#endif
