#include "rb_Nef_polyhedron_3.h"

// Comment to try git, by Rodrigo

template <class HDS>
class Polyhedron_builder : public CGAL::Modifier_base<HDS> {
public:    
	Array points;
	Array faces;
	
	Polyhedron_builder(Array points, Array faces) {
		this->points = points;
		this->faces = faces;
	}

  void operator()( HDS& hds) {
    // Postcondition: `hds' is a valid polyhedral surface.
    CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
    typedef typename HDS::Vertex   Vertex;
    typedef typename Vertex::Point PointHDS;
    B.begin_surface( points.size(), faces.size());
    // Add vertices
		for (unsigned int i = 0; i < points.size(); i++) {
			Array point = Array(points[i]);
			PointHDS pt = PointHDS(
				from_ruby<double>(point[0]),
				from_ruby<double>(point[1]),
				from_ruby<double>(point[2]));
			B.add_vertex(pt);
		}
		// Add faces
		for (unsigned int i = 0; i < faces.size(); i++) {
			Array indices = Array(faces[i]);
			B.begin_facet();
			for (unsigned int j = 0; j < indices.size(); j++) {
				B.add_vertex_to_facet(from_ruby<int>(indices[j]));
			}
			B.end_facet();
		}
    B.end_surface();
  }
};


/*-----------MAIN METHODS------------*/

Nef_polyhedron_3 build(){
	Nef_polyhedron_3 N;
	return N;
}

Nef_polyhedron_3 build_polyhedron(Array points, Array faces){
	Polyhedron_builder<HalfedgeDS> pb(points, faces);
	Polyhedron_3 P;
	P.delegate(pb);
	Nef_polyhedron_3 N(P);
	return N;
}

Nef_polyhedron_3 build_polyhedron_from_obj(String objPolyhedron){
	stringstream ss;
	ss << objPolyhedron.c_str();
	Polyhedron_3 P;
	cout << "objPolyhedron.c_str(): " << objPolyhedron.c_str() << endl;
	cout << "ss: " << ss << endl;
	ss >> P;
	cout << " P is valid: "<< P.is_valid() << " P is closed: " << P.is_closed() << endl;
	Nef_polyhedron_3 N(P);

	return N;
}

Nef_polyhedron_3 build_polygon(Array points){
	vector<Point_3> pts;
	for (unsigned int i = 0; i < points.size(); i++) {
		Array coordinate = Array(points[i]);
		Point_3 point(
				from_ruby<double>(coordinate[0]),
				from_ruby<double>(coordinate[1]),
				from_ruby<double>(coordinate[2]));
		pts.push_back(point);
	}
	Nef_polyhedron_3 N( pts.begin(), 
											pts.end());
	return N;
}

Nef_polyhedron_3 clone_nef(Nef_polyhedron_3 N){
	Nef_polyhedron_3 O(N);
	return O;
}


/* Test method
 The goal is to show the qt widget with the polyhedron. 
 TODO: Move it out of this class once stable.
 */
void show(Nef_polyhedron_3 N){

  char *args[]={"Nef_Polyhedron_3 Viewer"};
  int argc=1;
  
  QApplication a(argc, args); 
  CGAL::Qt_widget_Nef_3<Nef_polyhedron_3>* w =
    new CGAL::Qt_widget_Nef_3<Nef_polyhedron_3>(N);
  a.setMainWidget(w);
  w->show();
  
  a.exec();
}


Nef_polyhedron_3 build_polyline(Array points){
	typedef Point_3* 																		point_iterator;
	typedef std::pair<point_iterator,point_iterator> 		point_range;
	typedef std::list<point_range> 											polyline_list;
	Point_3 polyline[points.size()];
	for (unsigned int i = 0; i < points.size(); ++i){
		polyline[i] = from_ruby<Point_3>(points[i]);
	}
	polyline_list polylines;
	polylines.push_back(point_range(polyline,polyline+points.size()));
	Nef_polyhedron_3 N( polylines.begin(), 
											polylines.end(), 
											Nef_polyhedron_3::Polylines_tag());
	return N;
}

Array split(Nef_polyhedron_3 N){
	vector<Nef_polyhedron_3> nefs;
	Nef_polyhedron_3::Volume_const_iterator vi = ++N.volumes_begin();
	Nef_polyhedron_3::Shell_entry_const_iterator si;
  CGAL_forall_volumes(vi,N) {
		if(vi->mark()) {
			Nef_polyhedron_3::Shell_entry_const_iterator si;
			CGAL_forall_shells_of(si, vi) {
				Nef_polyhedron_3::SFace_const_handle sfch(si);
				Nef_polyhedron_3 O(N,sfch);
				nefs.push_back(O);
			}  
		}
	}
	Array out(nefs.begin(), nefs.end());
	return out;
}



String to_off(Nef_polyhedron_3 N){
	stringstream ss;
	if (N.is_valid() && N.is_simple()) {
		Polyhedron_3 P;
		N.convert_to_polyhedron(P);
		ss << P;
	}
	return String(ss.str());
}

Array vertices(Nef_polyhedron_3 N){
	vector<Vertex> vertices;
	Nef_polyhedron_3::Vertex_const_iterator vci;
	CGAL_forall_vertices(vci,N){
		vertices.push_back(vci);
  }
	Array out(vertices.begin(), vertices.end());
	return out;
}

Array halfedges(Nef_polyhedron_3 N){
	vector<Halfedge> halfedges;
	Nef_polyhedron_3::Halfedge_const_iterator heci;
	CGAL_forall_halfedges(heci,N){
		halfedges.push_back(heci);
  }
	Array out(halfedges.begin(), halfedges.end());
	return out;
}

Array halffacets(Nef_polyhedron_3 N){
	vector<Halffacet> halffacets;
	Nef_polyhedron_3::Halffacet_const_iterator hfci;
	CGAL_forall_halffacets(hfci,N){
		halffacets.push_back(hfci);
  }
	Array out(halffacets.begin(), halffacets.end());
	return out;
}

Iso_cuboid_3 bounding_box(Nef_polyhedron_3 N){
	vector<Point_3> points;
	Nef_polyhedron_3::Vertex_const_iterator vci;
	CGAL_forall_vertices(vci,N){
		points.push_back(vci->point());
  }	
	return CGAL::bounding_box(points.begin(),points.end());
}

String dump(Nef_polyhedron_3 N){
	stringstream ss;
	ss << N;
	return String(ss.str());
}

Nef_polyhedron_3 load(String s){
	stringstream ss;
	ss << s.c_str();
	Nef_polyhedron_3 N;
	ss >> N;
	return N;
}

bool is_valid(Nef_polyhedron_3 N){ return N.is_valid();}
bool is_bounded(Nef_polyhedron_3 N){ return N.is_bounded();}


Data_Type<Nef_polyhedron_3> define_Nef_polyhedron_3(Rice::Module rb_mCGAL ) {

	Data_Type<Nef_polyhedron_3> rb_cNef_polyhedron_3 =
		define_class_under<Nef_polyhedron_3>(rb_mCGAL, "Nef_polyhedron_3")
		.define_singleton_method("build", &build)
		.define_singleton_method("build_polyhedron", &build_polyhedron)
		.define_singleton_method("build_polyhedron_from_obj", &build_polyhedron_from_obj)
		.define_singleton_method("build_polyline", &build_polyline)
		.define_singleton_method("build_polygon", &build_polygon)
		.define_singleton_method("dump", &dump)
		.define_singleton_method("load", &load)
		.define_method("clone", &clone_nef)
		.define_method("simple?", &Nef_polyhedron_3::is_simple)
		.define_method("empty?", &Nef_polyhedron_3::is_empty)
		.define_method("space?", &Nef_polyhedron_3::is_space)
		.define_method("valid?", &is_valid)
		.define_method("bounded?", &is_bounded)
		.define_method("+", &Nef_polyhedron_3::operator+)
		.define_method("-", &Nef_polyhedron_3::operator-)
		.define_method("*", &Nef_polyhedron_3::operator*)
		.define_method("vertices", &vertices)
		.define_method("halfedges", &halfedges)
		.define_method("halffacets", &halffacets)
		.define_method("to_off", &to_off)
		.define_method("split", &split)
		.define_method("bounding_box", &bounding_box)
		.define_method("show", &show)
		.define_method("transform!", &Nef_polyhedron_3::transform)
	;

	return rb_cNef_polyhedron_3;
}


