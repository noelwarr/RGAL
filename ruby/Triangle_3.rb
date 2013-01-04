module CGAL
	##
	# Triangle
	class Triangle_3
		##
		# :call-seq:
		# 	Triangle_3.new(p1, p2, p3) => Triangle_3
		# 	Triangle_3.new([[x,y,z],[x,y,z],[x,y,z]]) => Triangle_3
		def self.new(*args)
			if args[0].is_a?(CGAL::Point_3)
				Triangle_3.build(args[0], args[1], args[2])
			else
				points = args[0].collect{|coords|Point_3.new(coords)}
				Triangle_3.build(points[0], points[1], points[2])
			end
		end

		##
		# :method: degenerate?

	end
end