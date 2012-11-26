#include "rb_Iso_cuboid_3.h"

template <class HDS>
class Cube_builder : public CGAL::Modifier_base<HDS> {
public:    
	Kernel::Iso_cuboid_3 bbx;
	Cube_builder(Iso_cuboid_3 bbx) {
		this->bbx = bbx;
	}
  void operator()( HDS& hds) {
    // Postcondition: `hds' is a valid polyhedral surface.
    CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
    typedef typename HDS::Vertex   Vertex;
    typedef typename Vertex::Point PointHDS;
    B.begin_surface(8, 6);
    // Add vertices
		for (unsigned int i = 0; i < 8; i++) {
			B.add_vertex(bbx[i]);
		}
		// Add faces
		int index[6][4] = { {0,3,2,1},
												{6,5,0,1},
												{5,4,3,0},
												{4,7,2,3},
												{7,6,1,2},
												{7,4,5,6}};
		for (unsigned int i = 0; i < 6; i++) {
			B.begin_facet();
			for (unsigned int j = 0; j < 4; j++) {
				B.add_vertex_to_facet(index[i][j]);
			}
			B.end_facet();
		}
		B.end_surface();
	}
};

Iso_cuboid_3 build_cuboid(Array array){
	vector<Point_3> points;
	for (unsigned int i = 0; i != array.size(); ++i) {
		points.push_back(from_ruby<Point_3>(array[i]));
	}
	return CGAL::bounding_box(points.begin(), points.end());
}

Nef_polyhedron_3 to_nef(Iso_cuboid_3 cuboid){
	Cube_builder<HalfedgeDS> builder(cuboid);
	Polyhedron_3 P;
	P.delegate(builder);
	return Nef_polyhedron_3(P);
}

double xmin(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.xmin());}
double ymin(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.ymin());}
double zmin(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.zmin());}
double xmax(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.xmax());}
double ymax(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.ymax());}
double zmax(Iso_cuboid_3 cuboid){	return CGAL::to_double(cuboid.zmax());}


Data_Type<Iso_cuboid_3> define_Iso_cuboid_3(Rice::Module rb_mCGAL ) {

	Data_Type<Iso_cuboid_3> rb_cIso_cuboid_3 =
			define_class_under<Iso_cuboid_3>(rb_mCGAL, "Iso_cuboid_3")
			.define_singleton_method("build", &build_cuboid)
			.define_method("to_nef", &to_nef)
			.define_method("xmin", &xmin)
			.define_method("ymin", &ymin)
			.define_method("zmin", &zmin)
			.define_method("xmax", &xmax)
			.define_method("ymax", &ymax)
			.define_method("zmax", &zmax)
		;


	return rb_cIso_cuboid_3;
}


