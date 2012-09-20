require_relative 'cgal.so'

module CGAL
	class Offset_polygon_2
		def to_points
			curves = self.curves
			result = [curves[0].source]
			curves.each{|curve|
				if curve.circular?
					precision = Math::PI / 12
					radius = curve.radius
					center = curve.center.to_a
					points = [curve.source, curve.target]
					rel_coordinates = points.collect{|point|
						p = point.to_a
						c = center
						[p[0]-c[0], p[1]-c[1]]
					}
					angles = rel_coordinates.collect{|p|
						if p[0] != 0 && p[1] != 0
							a = Math::atan(p[0]/p[1])
						elsif p[0] == 0 # 90 or 270
							a =( (p[1] > 0) ? (Math::PI/2) : (Math::PI*(3.to_f/2.to_f)) )
						elsif p[1] == 0 # 0 or 180
							a =( (p[0] > 0) ? 0 : Math::PI )
						end
					}
					direction = (curve.orientation == "clockwise" ? -1 : 1)
					angle = (angles[0] - angles[1]).divmod(Math::PI)[1] * direction
					num_of_points = angle.abs.divmod(precision)[0]
					step = angle.to_f / num_of_points.to_f
					for i in 1..num_of_points
						new_angle = angles[0] + (i * step)
						x = (Math::cos(new_angle) * radius) + center[0]
						y = (Math::sin(new_angle) * radius) + center[1]
						result.push CGAL::Point_2.build(x,y)
					end
				else
					result.push curve.target
				end
			}
			return result
		end
	end
	class Nef_polyhedron_3
		def to_json

		end
	end
end
