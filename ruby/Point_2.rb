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
		def to_3(z = 0)
			Point_3.new self.to_a.push(z)
		end
		
    # Returns the Euclidean distance from the point to p
    def distance_to(p)
      x_diff = self.x-p.x
      y_diff = self.y-p.y
      return Math.sqrt(x_diff*x_diff + y_diff*y_diff)
    end
    
    # Returns a new vector that is the opposite
    def opposite(p)
      return CGAL::Point_2.build(self.y, self.x)
    end

	end
	

	
end