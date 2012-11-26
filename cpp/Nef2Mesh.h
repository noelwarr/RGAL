// Inspired from Nef_polyhedron_3::Build_polyhedron
template<typename Kernel, typename Nef_3, typename Mark> class Nef2Mesh
{

    // Ugh, how much of this stuff do we need
    typedef typename Nef_3::SNC_structure                        SNC_structure;
    typedef typename SNC_structure::SNC_decorator                SNC_decorator;
    typedef typename CGAL::SNC_const_decorator<SNC_structure>    SNC_const_decorator;

    typedef typename SNC_structure::Sphere_point                 Sphere_point;
    typedef typename SNC_structure::Sphere_segment               Sphere_segment;
    typedef typename SNC_structure::Sphere_circle                Sphere_circle;
    typedef typename SNC_structure::Vertex_base                  Vertex;
    typedef typename SNC_structure::Halfedge_base                Halfedge;
    typedef typename SNC_structure::Halffacet_base               Halffacet;
    typedef typename SNC_structure::Volume_base                  Volume;
    typedef typename SNC_structure::Vertex_const_handle          Vertex_const_handle;
    typedef typename SNC_structure::Halfedge_const_handle        Halfedge_const_handle;
    typedef typename SNC_structure::Halffacet_const_handle       Halffacet_const_handle;
    typedef typename SNC_structure::Volume_const_handle          Volume_const_handle;
    typedef typename SNC_structure::SHalfedge_around_svertex_circulator 
        SHalfedge_around_svertex_circulator;
    typedef typename SNC_structure::SHalfedge_around_svertex_const_circulator 
        SHalfedge_around_svertex_const_circulator;
    typedef typename SNC_structure::SHalfedge_around_facet_circulator 
        SHalfedge_around_facet_circulator;
    typedef typename SNC_structure::SHalfedge_around_facet_const_circulator 
        SHalfedge_around_facet_const_circulator;
    typedef typename SNC_structure::SHalfedge_around_sface_const_circulator 
        SHalfedge_around_sface_const_circulator;
    typedef typename SNC_structure::Halffacet_cycle_const_iterator     
        Halffacet_cycle_const_iterator;
    typedef typename SNC_structure::Halffacet_cycle_iterator     
        Halffacet_cycle_iterator;
    typedef typename SNC_structure::Infi_box                     Infi_box;
    typedef typename SNC_structure::Size_type Size_type;
    typedef Size_type                         size_type;
    typedef typename SNC_decorator::Vertex_iterator  Vertex_iterator;
    typedef typename SNC_decorator::Halfedge_iterator
        Halfedge_iterator;
    typedef typename SNC_decorator::Halffacet_iterator
        Halffacet_iterator;
    typedef typename SNC_structure::Shell_entry_iterator
        Shell_entry_iterator;
    typedef typename SNC_decorator::Volume_iterator  Volume_iterator;
    typedef typename SNC_structure::Vertex_const_iterator
        Vertex_const_iterator;
    typedef typename SNC_structure::Halfedge_const_iterator 
        Halfedge_const_iterator;
    typedef typename SNC_structure::Halffacet_const_iterator     
        Halffacet_const_iterator;
    typedef typename SNC_structure::Volume_const_iterator     
        Volume_const_iterator;
    typedef typename SNC_structure::Shell_entry_const_iterator
        Shell_entry_const_iterator;
    typedef typename SNC_decorator::SFace_cycle_const_iterator     
        SFace_cycle_const_iterator;
    typedef typename SNC_decorator::Association  Association;

    typedef typename SNC_structure::Sphere_map       Sphere_map;
    typedef CGAL::SM_decorator<Sphere_map>           SM_decorator;
    typedef CGAL::SM_const_decorator<Sphere_map>     SM_const_decorator;
    typedef CGAL::SM_point_locator<SNC_structure>    SM_point_locator;

    typedef typename SM_decorator::SVertex_const_handle
        SVertex_const_handle;
    typedef typename SM_decorator::SHalfedge_const_handle
        SHalfedge_const_handle;
    typedef typename SM_decorator::SHalfloop_const_handle
        SHalfloop_const_handle;
    typedef typename SM_decorator::SFace_const_handle
        SFace_const_handle;

    typedef typename Kernel::Point_3                    Point_3;
    typedef typename Kernel::Plane_3                    Plane_3;
    typedef typename Kernel::Vector_3                   Vector_3;
    typedef typename Kernel::Segment_3                  Segment_3;


    SNC_const_decorator& scd;
    CGAL::Object_index<Vertex_const_iterator> VI;

public:
    //Ctor
    Nef2Mesh(SNC_const_decorator& s) : 
      scd(s), VI(s.vertices_begin(),s.vertices_end(),'V') {}

      // Perform operation
      void operator()(BGT_Mesh &out_mesh) {
          out_mesh.Clear();

          // Apparently, number of irrelevant volumes to skip. Depends on kernel.
          int skip_volumes = Infi_box::extended_kernel() ? 2 : 1; 
          CGAL_assertion_msg  (skip_volumes == 1, "Doubt that we can handle extended kernel");

          // Would be nice if BGT_Mesh had Reserve() functionality for vert, facet 
          // data structures.
          BGT_Mesh::BatchMode bm(&out_mesh);

          // Populate vertices
          Vertex_const_iterator v;
          CGAL_forall_vertices(v,scd) {
              if(Infi_box::is_standard(v->point())) {
                  // Add to mesh
                  const Point_3 &point = v->point();
                  BGT_V4 vert = BGT_V4_Construct((float)::CGAL::to_double(point.x()), 
                      (float)::CGAL::to_double(point.y()), 
                      (float)::CGAL::to_double(point.z()));
                  // Add to object index
                  VI[v] = out_mesh.AddVertex(vert);
              }
          }     

#ifdef _MATERIAL_MARKING_
          // Create blind data for userdata
          int newIndex = out_mesh.CreateBlindData("texture", 32);
          // Later code will assume index zero for this
          CGAL_assertion_msg(newIndex == 0, "Must provide mesh with no blind data");
          // To prevent thrashing, initialize the blind data size to something reasonable
          // 2 * numvertices seems like a reasonable upper bound (can't find literature on this!)
          out_mesh.GetBlindData()[0]->SetElement(out_mesh.GetNumVertices() * 2, 0);
#endif

          Visitor V(out_mesh,scd,VI);
          Volume_const_handle c;
          CGAL_forall_volumes(c,scd)
              // if(skip_volumes-- <= 0)
              for(Shell_entry_const_iterator shei = c->shells_begin();
                  shei != c->shells_end(); ++shei)
              {
                  scd.visit_shell_objects(SFace_const_handle(shei),V);
              }
      }

      class Visitor 
      {
          typedef typename CGAL::Triangulation_euclidean_traits_xy_3<Kernel>       XY;
          typedef typename CGAL::Triangulation_euclidean_traits_yz_3<Kernel>       YZ;
          typedef typename CGAL::Triangulation_euclidean_traits_xz_3<Kernel>       XZ;

          const CGAL::Object_index<Vertex_const_iterator>& VI;
          SNC_const_decorator& D;
          BGT_Mesh &m_mesh;

      public:
          Visitor(BGT_Mesh &out_mesh,
              SNC_const_decorator& sd,
              CGAL::Object_index<Vertex_const_iterator>& vi) : VI(vi), m_mesh(out_mesh), D(sd){}

          void visit(Halffacet_const_handle opposite_facet) {

              CGAL_NEF_TRACEN("Build_polyhedron: visit facet " << opposite_facet->plane());
              CGAL_assertion(Infi_box::is_standard(opposite_facet->plane()));

              SHalfedge_const_handle se;
              Halffacet_cycle_const_iterator fc;

              Halffacet_const_handle f = opposite_facet->twin();

              SHalfedge_around_facet_const_circulator 
                  sfc1(f->facet_cycles_begin()), sfc2(sfc1);

              const Mark &mark = sfc1->mark();

              if(++f->facet_cycles_begin() != f->facet_cycles_end() ||
                  ++(++(++sfc1)) != sfc2) {
                      Vector_3 orth = f->plane().orthogonal_vector();
                      int c = CGAL::abs(orth[0]) > CGAL::abs(orth[1]) ? 0 : 1;
                      c = CGAL::abs(orth[2]) > CGAL::abs(orth[c]) ? 2 : c;

                      if(c == 0) {
                          Triangulation_handler2<YZ> th(f, mark);
                          th.handle_triangles(m_mesh, VI);
                      } else if(c == 1) {
                          Triangulation_handler2<XZ> th(f, mark);
                          th.handle_triangles(m_mesh, VI);
                      } else if(c == 2) {
                          Triangulation_handler2<XY> th(f, mark);
                          th.handle_triangles(m_mesh, VI);
                      } else
                          CGAL_assertion_msg(false, "wrong value");

              } else {

                  // We expect 3 verts
                  int vertIndices[3];
                  int currIndex = 0;

                  fc = f->facet_cycles_begin();
                  se = SHalfedge_const_handle(fc);
                  CGAL_assertion(se!=0);
                  SHalfedge_around_facet_const_circulator hc_start(se);
                  SHalfedge_around_facet_const_circulator hc_end(hc_start);
                  CGAL_For_all(hc_start,hc_end) {
                      CGAL_NEF_TRACEN("   add vertex " << hc_start->source()->center_vertex()->point());
                      CGAL_assertion_msg(currIndex < 3, "more than 3 verts in facet!");
                      vertIndices[currIndex++] = VI[hc_start->source()->center_vertex()];
                  }
                  CGAL_assertion_msg(currIndex == 3, "Facet not a triangle");
                  int newPoly = m_mesh.AddPolygon(&vertIndices[0], 3);
                  
#ifdef _MATERIAL_MARKING_
                  BGT_BlindData *bd = m_mesh.GetBlindData()[0];
                  CGAL_assertion_msg(bd != NULL, "Blind data hasn't been created for input mesh!");
                  bd->SetElement(newPoly, (BGT_BlindData::DataValueType)mark.m_userdata); 
#endif

              }
          }

          void visit(SFace_const_handle) {}
          void visit(Halfedge_const_handle) {}
          void visit(Vertex_const_handle) {}
          void visit(SHalfedge_const_handle) {}
          void visit(SHalfloop_const_handle) {}
      };


      template<typename Kernel>
      class Triangulation_handler2 {

          typedef typename CGAL::Triangulation_vertex_base_2<Kernel>               Vb;
          typedef typename CGAL::Constrained_triangulation_face_base_2<Kernel>     Fb;
          typedef typename CGAL::Triangulation_data_structure_2<Vb,Fb>             TDS;
          typedef typename CGAL::Constrained_triangulation_2<Kernel,TDS>           CT;

          typedef typename CT::Face_handle           Face_handle;
          typedef typename CT::Vertex_handle         CTVertex_handle;
          typedef typename CT::Finite_faces_iterator Finite_face_iterator;
          typedef typename CT::Edge                  Edge;

          CT ct;
          CGAL::Unique_hash_map<Face_handle, bool> visited;
          CGAL::Unique_hash_map<CTVertex_handle, Vertex_const_handle> ctv2v;
          Finite_face_iterator fi;
          const Mark &m_mark;
          Plane_3 supporting_plane;

      public:
          Triangulation_handler2(Halffacet_const_handle f, const Mark &mark) : 
            visited(false), supporting_plane(f->plane()), m_mark(mark) {
                Halffacet_cycle_const_iterator fci;
                for(fci=f->facet_cycles_begin(); fci!=f->facet_cycles_end(); ++fci) {
                    if(fci.is_shalfedge()) {
                        SHalfedge_around_facet_const_circulator sfc(fci), send(sfc);
                        CGAL_For_all(sfc,send) {
                            CGAL_NEF_TRACEN("  insert point" << sfc->source()->source()->point());
                            CTVertex_handle ctv = ct.insert(sfc->source()->source()->point());
                            ctv2v[ctv] = sfc->source()->source();
                        }
                    }
                }

                for(fci=f->facet_cycles_begin(); fci!=f->facet_cycles_end(); ++fci) {
                    if(fci.is_shalfedge()) {
                        SHalfedge_around_facet_const_circulator sfc(fci), send(sfc);
                        CGAL_For_all(sfc,send) {
                            CGAL_NEF_TRACEN("  insert constraint" << sfc->source()->source()->point()
                                << "->" << sfc->source()->twin()->source()->point());
                            ct.insert_constraint(sfc->source()->source()->point(),
                                sfc->source()->twin()->source()->point());
                        }
                    }
                }
                CGAL_assertion(ct.is_valid());

                CGAL_NEF_TRACEN("number of finite triangles " << ct.number_of_faces());

                typename CT::Face_handle infinite = ct.infinite_face();
                typename CT::Vertex_handle ctv = infinite->vertex(1);
                if(ct.is_infinite(ctv)) ctv = infinite->vertex(2);
                CGAL_assertion(!ct.is_infinite(ctv));

                typename CT::Face_handle opposite;
                typename CT::Face_circulator vc(ctv,infinite);
                do { opposite = vc++;
                } while(!ct.is_constrained(typename CT::Edge(vc,vc->index(opposite))));
                typename CT::Face_handle first = vc;

                CGAL_assertion(!ct.is_infinite(first));
                traverse_triangulation(first, first->index(opposite));

                fi = ct.finite_faces_begin();
            }

            void traverse_triangulation(Face_handle f, int parent) {
                visited[f] = true;
                if(!ct.is_constrained(Edge(f,ct.cw(parent))) && !visited[f->neighbor(ct.cw(parent))]) {
                    Face_handle child(f->neighbor(ct.cw(parent)));
                    traverse_triangulation(child, child->index(f));
                } 
                if(!ct.is_constrained(Edge(f,ct.ccw(parent))) && !visited[f->neighbor(ct.ccw(parent))]) {
                    Face_handle child(f->neighbor(ct.ccw(parent)));
                    traverse_triangulation(child, child->index(f));
                } 
            } 

            template<typename Triangle_3>
            bool get_next_triangle(Triangle_3& tr) {
                while(fi != ct.finite_faces_end() && visited[fi] == false) ++fi;
                if(fi == ct.finite_faces_end()) return false;
                tr = Triangle_3(fi->vertex(0)->point(), fi->vertex(1)->point(), fi->vertex(2)->point());
                ++fi;
                return true;
            }

            bool same_orientation(Plane_3 p1) const {
                if(p1.a() != 0)
                    return CGAL::sign(p1.a()) == CGAL::sign(supporting_plane.a());
                if(p1.b() != 0)
                    return CGAL::sign(p1.b()) == CGAL::sign(supporting_plane.b());
                return CGAL::sign(p1.c()) == CGAL::sign(supporting_plane.c());
            }

            template<typename Index>
            void handle_triangles(BGT_Mesh &out_mesh, Index& VI) {
                while(fi != ct.finite_faces_end() && visited[fi] == false) ++fi;
                while(fi != ct.finite_faces_end()) {
                    Plane_3 plane(fi->vertex(0)->point(),
                        fi->vertex(1)->point(),
                        fi->vertex(2)->point());

                    // Add a triangle
                    int vertIndices[3];
                    vertIndices[0] = VI[ctv2v[fi->vertex(0)]];
                    if(same_orientation(plane)) {
                        vertIndices[1] = VI[ctv2v[fi->vertex(1)]];
                        vertIndices[2] = VI[ctv2v[fi->vertex(2)]];
                    } else {
                        vertIndices[1] = VI[ctv2v[fi->vertex(2)]];
                        vertIndices[2] = VI[ctv2v[fi->vertex(1)]];
                    }
                    int newPoly = out_mesh.AddPolygon(&vertIndices[0], 3);

#ifdef _MATERIAL_MARKING_
                    BGT_BlindData *bd = out_mesh.GetBlindData()[0];
                    CGAL_assertion_msg(bd != NULL, "Blind data hasn't been created for input mesh!");
                    bd->SetElement(newPoly, (BGT_BlindData::DataValueType)m_mark.m_userdata);
#endif
                    do {
                        ++fi;
                    } while(fi != ct.finite_faces_end() && visited[fi] == false);
                }
            }
      };

};
