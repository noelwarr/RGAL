require_relative '../cgal.rb'
polygon1 = CGAL::Polygon.new([[[0,0],[5,0],[0,5]],[[3,1],[1,1],[1,3]]])
polygon2 = CGAL::Polygon.new([[2,0],[10,0],[2,7]])
polygon3 = CGAL::Polygon.new([[12,0],[11,1],[11,0]])
(polygon1 + polygon2)[0].offset(0.2)
(polygon1 - polygon3)[0].offset(0.2)
CGAL::Polygon.join([polygon1,polygon2,polygon3])[0].offset(0.3)