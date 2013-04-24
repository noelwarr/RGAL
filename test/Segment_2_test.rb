require_relative '../cgal.rb'
p = CGAL::Point_2.new [0,0]
q = CGAL::Point_2.new [1,1]
c = CGAL::Circle_2.build_halfcircle(p,q)
CGAL::Segment_2.build_curve(c,p,q,:counterclockwise)