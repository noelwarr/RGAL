require_relative "../cgal.rb"

Array poly1 = Array.new()
poly1.push(CGAL::Point_2.build(1,1))
poly1.push(CGAL::Point_2.build(-1,1))
poly1.push(CGAL::Point_2.build(-1,-1))
poly1.push(CGAL::Point_2.build(1,-1))

Array hole2 = Array.new()
hole2.push(CGAL::Point_2.build(0.8,0.5))
hole2.push(CGAL::Point_2.build(0.3,0.5))
hole2.push(CGAL::Point_2.build(0.3,-0.5))
hole2.push(CGAL::Point_2.build(0.8,-0.5))

Array hole2 = Array.new()
hole2.push(CGAL::Point_2.build(0,0.5))
hole2.push(CGAL::Point_2.build(0.5,0))
hole2.push(CGAL::Point_2.build(0,-0.5))
hole2.push(CGAL::Point_2.build(-0.5,0))

Array polyList = Array.new()
polyList.push(poly1)
polyList.push(hole2)

offsets = CGAL::inward_offset_polygon(polyList,0.1,1)	

pointList = poly1.to_a.collect{|p2| CGAL::Point_3.build p2.x, p2.y, 0}
pointList.push (pointList[0])
originalPolygon = CGAL::Nef_polyhedron_3.build_polyline pointList

pointList = hole2.to_a.collect{|p2| CGAL::Point_3.build p2.x, p2.y, 0}
pointList.push (pointList[0])
originalPolygonHole = CGAL::Nef_polyhedron_3.build_polyline pointList

fullOriginalPolygon = originalPolygon + originalPolygonHole
fork {fullOriginalPolygon}

offsets.flatten!
offsets.collect!{|polygon2|
                 list_of_points = polygon2.to_a
                list_of_points.push list_of_points[0]
                CGAL::Nef_polyhedron_3.build_polyline list_of_points	.collect{|p2|	 
                                                                            CGAL::Point_3.build p2.x, p2.y, 0
                                                                           }
                }
(offsets.inject{|prev, curr| prev + curr}+fullOriginalPolygon)

