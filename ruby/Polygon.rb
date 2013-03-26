module CGAL

	#Wrapper class aimed ant making the use of CGAL polygons a bit more simple
	class Polygon

	#attribute accessor to the polygon_with_holes_2 object that this class
	#wraps around
	attr_accessor :root

		#list points of outer boundary and holes
		def outer_boundary; root.outer_boundary.to_a;							end
		def holes 				; root.holes.collect{|poly|poly.to_a};	end

		#build from a polygon_with_holes_2, a polygon_2 or an array of points
		#points can come in Point_2 or [float,float].  Just one array of points
		#builds a simple polygon.  Nested arrays will build a countour with holes
		def initialize(args)
			if args.is_a?(Array)
				if args[0][0].is_a?(Numeric) || args[0].is_a?(Point_2)
					input = [args.clone]
				else
					input = args
				end
				polygons = input.collect{|polygon|
					points = polygon.collect{|point| 
						point.is_a?(Array) ? Point_2.new(point) : point
					}
					Polygon_2.build points
				}
				@root = Polygon_with_holes_2.build polygons
			elsif args.is_a?(Polygon_with_holes_2)
				@root = args
			elsif args.is_a?(Polygon_2)
				@root = Polygon_2.build [args]
			else
				raise "Wrong argument. Expected array of points or Polygon_with holes"
			end
		end

		#offset
		def offset(radius, precision = 0)
			opwh = root.offset radius
			polygons = opwh.to_a.collect{|op| op.to_points}
			Polygon.new(polygons)
		end

		#returns a nef facet representing the polygon
		def to_nef(z = 0)
			polygons = root.to_a.collect{|poly|
				poly.to_a.collect{|p| 
					Point_3.new p.to_a.push(z)
				}
			}
			nef = Nef_polyhedron_3.new polygons.shift
			polygons.each{|polygon|
				nef -= Nef_polyhedron_3.new polygon
			}
			nef
		end

		#Add two polygons
		def +(polygon)
			ps = Polygon_set_2.join_polygons_with_holes [root, polygon.root]
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		#Subtract a polygon from this one
		def -(polygon)
			ps = Polygon_set_2.difference_polygons_with_holes root, polygon.root
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		#visualise the nef representing this polygon
		def show(z = 0)
			to_nef(z).show
		end

		#join a whole series of polygons with holes
		def self.join(polygons)
			pwhs = polygons.collect{|polygon| polygon.root }
			ps = Polygon_set_2.join_polygons_with_holes pwhs
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		#convert an array of polygons to nefs
		def self.to_nef(polygons, z = 0)
			nefs = polygons.collect{|polygon|polygon.to_nef(z)}
			nefs.inject(:+)
		end

		#visualise an array of polygons
		def self.show(polygons, z = 0)
			to_nef(polygons, z).show
		end

	end

end