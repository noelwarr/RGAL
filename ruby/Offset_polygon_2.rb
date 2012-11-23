module CGAL
	class Offset_polygon_2
		def to_points
			curves = self.curves
			result = [curves[0].source]
			curves.each{|curve|
				if curve.circular?
					result += circular_curve_to_points(curve)
				else
					result.push curve.target
				end
			}
			return result
		end
    
    private

		def angle(point1, point2)				
			x, y = point1.to_a.zip(point2.to_a).collect{|c1, c2| c2 - c1}
			q = 0.0							if (x >= 0) && (y >= 0)
			q = Math::PI*(0.5)	if (x <= 0) && (y >  0)
			q = Math::PI*(1.0)	if (x <  0) && (y <= 0)
			q = Math::PI*(1.5)	if (x >= 0) && (y <  0)
			return q if (x == 0 || y == 0)
			return Math::atan(y.to_f/x.to_f).abs + q
		end
		
		def circular_curve_to_points(curve)
			result = Array.new
			precision = Math::PI/24
			a1 = angle(curve.center, curve.source)
			a2 = angle(curve.center, curve.target)
			a2 = (a2 > a1) ? a2 : (a2 + Math::PI * 2)
			angle = (a2 - a1)
			number_of_steps = (angle / precision).to_i.abs
			step_angle = (angle / number_of_steps)
			(1..number_of_steps-1).each{|step|
				a = a1 + ( step_angle * step )
				x = (Math::cos(a) * curve.radius) + curve.center.x
				y = Math::sin(a) * curve.radius + curve.center.y
				result.push CGAL::Point_2.build(x,y)
			}
			result += [curve.target]
			return result
		end
	end
end
