require_relative '../cgal'
triangle = CGAL::Triangle_3.new([[0,0,0],[1,0,0],[2,0,0]])
raise if !triangle.degenerate?
triangle = CGAL::Triangle_3.new([[0,0,0],[1,0,0],[1,-1,0]])
raise if triangle.degenerate?