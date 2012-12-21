module CGAL
	class Point_2
		def self.new(*args)
			if args.length == 2
				p = args
			elsif args[0].is_a?(Array)
				p = args[0]
			end
			self.build(p[0],p[1])
		end
		def ==(point)
			self.to_a == point.to_a
		end
		def to_s
			"(#{self.to_a.join(", ")})"
		end
	end
end