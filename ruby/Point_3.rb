module CGAL
	class Point_3
		##
		# :call-seq:
		# 	Point_3.new(x,y,z) => Point_3
		#   Point_3.new([x,y,z]) => Point_3
		def self.new(*args)
			if args.length == 3
				p = args
			elsif args[0].is_a?(Array)
				p = args[0]
			end
			Point_3.build(p[0],p[1],p[2])
		end
		def ==(point)
			self.to_a == point.to_a
		end
		def to_s
			"(#{self.to_a.join(", ")})"
		end
	end
end
