module CGAL
	class Polygon_2
		FILTER_LIMIT = 0.0001
		def self.new(points, filter = {filter: true})
			points.collect!{|point|
				point.is_a?(Array) ? Point_2.new(point[0], point[1]) : point
			}
			points.each_cons(2){|p1, p2|
				diff = (p1.x - p2.x).abs + (p1.y - p2.y).abs
				points.delete(p1) if diff < FILTER_LIMIT
			}
			self.build(points)
		end
	end
end
