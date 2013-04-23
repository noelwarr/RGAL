module CGAL
	class Segmented_polygon_2
		def to_points
			curves = self.curves
			result = []#curves[0].source]
			curves.each{|curve|
				if curve.circular?
					result += Segmented_polygon_2.circular_curve_to_points(curve.center, curve.source, curve.target, curve.radius)
				else
					result.push curve.target
				end
			}
			return result
		end
    		
		def self.circular_curve_to_points(curve_center, curve_source, curve_target, curve_radius)
			result = Array.new
			segments = 24
			precision = Math::PI/(segments/2)
			a1 = angle(curve_center, curve_source)
			a2 = angle(curve_center, curve_target)
			a2 = (a2 > a1) ? a2 : (a2 + Math::PI * 2)
			angle = (a2 - a1)
			number_of_steps = (angle / precision).to_i.abs % (segments)
			step_angle = (angle / number_of_steps)
			(1..number_of_steps-1).each{|step|
				a = a1 + ( step_angle * step )
				x = (Math::cos(a) * curve_radius) + curve_center.x
				y = Math::sin(a) * curve_radius + curve_center.y
				result.push CGAL::Point_2.build(x,y)
			}
			result += [curve_target]
			return result
		end
		
  private

    def self.angle(point1, point2)        
      x, y = point1.to_a.zip(point2.to_a).collect{|c1, c2| c2 - c1}
      atan = Math::atan(y.to_f/x.to_f).abs
      pi = Math::PI
      case
        when (x >= 0) && (y >= 0) then atan
        when (x <  0) && (y >= 0) then pi - atan
        when (x <  0) && (y <  0) then pi + atan
        when (x >= 0) && (y <  0) then (2 * pi) - atan
      end
    end
	end
end
