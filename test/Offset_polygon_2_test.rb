require_relative "../cgal.rb"
coordinates = [[0,0],[1,1],[2,3],[1,2],[0,0]]
nef1 = CGAL::Nef_polyhedron_3.new coordinates.collect{|p| CGAL::Point_3.new p[0], p[1], 0}
coordinates.pop
pg = CGAL::Polygon_2.new coordinates.collect{|p| CGAL::Point_2.new p[0], p[1]}
ps = CGAL::Polygon_set_2.join [pg]
pwh = ps.to_a[0]
opwh = pwh.offset(0.1)
points = opwh.outer_boundary.to_points.collect{|p| CGAL::Point_3.build p.x, p.y, 0 }
nef2 = CGAL::Nef_polyhedron_3.build_polyline points