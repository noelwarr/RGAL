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
				if args[0].is_a?(Point_2) || args[0][0].is_a?(Point_2)
					args = [args] if args[0].is_a?(Point_2)
				else
					args = [args] if args[0][0].is_a?(Numeric)
					args = args.collect{|point_list| 
						point_list.collect{|c|
							Point_2.new c
						}
					}
				end
				polys = args.collect{|point_list|
					poly = Polygon_2.build point_list
					if !poly.simple? || poly.collinear?
						raise "Polygon points make a non valid polygon : #{point_list.inspect}" 
					end
					poly
				}
				@root = Polygon_with_holes_2.build polys
			elsif args.is_a?(Polygon_with_holes_2)
				args.to_a.each{|poly| raise "Polygon_2 is not simple" if !poly.simple? }
				@root = args
			elsif args.is_a?(Polygon_2)
				raise "Polygon_2 is not simple" if !args.simple?
				@root = Polygon_with_holes_2.build [args]
			else
				raise "Wrong argument. Expected array of points or Polygon_2 or Polygon_with_holes_2"
			end
		end

		def empty?
			self.to_a.empty?
		end

		def intersect?(polygon)
			ps = Polygon_set_2.join_polygons_with_holes([self.root])
			ps.intersect_polygon_with_holes?(polygon.root)
		end


		#offset
		def offset(radius, args = 0)
			opwh = root.offset radius 
			polygons = opwh.to_a.collect{|op| op.to_points }
			Polygon.new(polygons)
		end

		#inward
		def inward_offset(radius)
			inward_offsets(radius, 1)[0]
		end

		def inward_offsets(radius, args = 0)
			offsets = CGAL::inward_offset_polygon(self.to_a, radius.abs, args)
			offsets.collect{|polys|
				pwh = CGAL::Polygon_with_holes_2.build(polys)
				Polygon.new(pwh)
			}
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
				nef -= Nef_polyhedron_3.new polygon.reverse
			}
			nef
		end

		#Add two polygons
		def +(polygon)
			ps = Polygon_set_2.join_polygons_with_holes [self.root, polygon.root]
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		#Subtract a polygon from this one
		def -(polygon)
			ps = Polygon_set_2.difference_polygons_with_holes root, polygon.root
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		def to_a()
			[outer_boundary] + holes
		end

		#visualise the nef representing this polygon
		def show(z = 0)
			to_nef(z).show
		end

		def to_s
			"#<CGAL::Polygon:0x%08x>" % (object_id * 2)
		end

		#join a whole series of polygons with holes
		def self.join(polygons)
			pwhs = polygons.collect{|polygon| polygon.root }
			ps = Polygon_set_2.join_polygons_with_holes pwhs
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		def self.intersect(polygons1, polygons2)
			pwhs1 = polygons1.collect{|polygon| polygon.root }
			ps1 = Polygon_set_2.join_polygons_with_holes pwhs1
			pwhs2 = polygons2.collect{|polygon| polygon.root }
			ps2 = Polygon_set_2.join_polygons_with_holes pwhs2
			ps = Polygon_set_2.intersect_polygon_sets ps1, ps2
			ps.to_a.collect{|pwh| Polygon.new(pwh)}
		end

		def self.difference(polygons1, polygons2)
			pwhs1 = polygons1.collect{|polygon| polygon.root }
			ps1 = Polygon_set_2.join_polygons_with_holes pwhs1
			pwhs2 = polygons2.collect{|polygon| polygon.root }
			ps2 = Polygon_set_2.join_polygons_with_holes pwhs2
			ps = Polygon_set_2.difference_polygon_sets ps1, ps2
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