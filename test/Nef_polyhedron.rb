require_relative "../cgal.rb"
#pol
tetrahedron = CGAL::Nef_polyhedron_3.build([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],[[0,1,3],[1,2,3],[2,0,3],[2,1,0]])