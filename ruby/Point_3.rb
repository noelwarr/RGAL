module CGAL
	class Point_3
		def new(x,y,z)
			Point.build(x,y,z)
		end
		def ==(point)
			self.to_a == point.to_a
		end
		def to_s
			"(#{self.to_a.join(", ")})"
		end
	end
end
