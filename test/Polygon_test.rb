require_relative '../cgal.rb'
=begin
polygon1 = CGAL::Polygon.new([[[0,0],[5,0],[0,5]],[[3,1],[1,1],[1,3]]])
polygon2 = CGAL::Polygon.new([[2,0],[10,0],[2,7]])
polygon3 = CGAL::Polygon.new([[12,0],[11,1],[11,0]])
(polygon1 + polygon2)[0].offset(0.2)
(polygon1 - polygon3)[0].offset(0.2)
CGAL::Polygon.join([polygon1,polygon2,polygon3])[0].offset(0.3)
pts = polygon1.root.to_a.collect{|p|p.to_a}
CGAL::inward_offset_polygon(polygon1.to_a, 0.1, 0).inspect
polygon1.inward_offsets(0.1).inspect
=end
pts = [[2,0],[10,0],[2,7]].collect{|c|CGAL::Point_2.new c}
CGAL::Polygon.new(pts).simple?
