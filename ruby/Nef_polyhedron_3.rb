module CGAL
	class Nef_polyhedron_3
		def self.new(*args)
			if args.first == nil
				self.build
			elsif args.first.is_a?(Hash)
				self.build_polyhedron(args.first[:points], args.first[:facets])
			elsif args.first.is_a?(Array)
				self.build_polyline(args.first)
			end
		end

		def self.build_cube(x,y,z)
			self.build_polyhedron( [[0,0,0],[x,0,0],[x,y,0],[0,y,0],[0,y,z],[0,0,z],[x,0,z],[x,y,z]],
									[[0,1,6,5],[1,2,7,6],[2,3,4,7],[3,0,5,4],[3,2,1,0],[4,5,6,7]])
		end

		def transform(transformation)
			nef = self.clone
			nef.transform!(transformation)
			nef
		end

		def structure
			volumes = Array.new
			self.split.each{|nef|
				volumes.push parse_off(nef.to_off)
			}
			volumes
		end

		def dump
			self.class.dump(self)
		end

		private
		def parse_off(off)
			off = off.split "\n"
			metadata = off[1].split(" ")
			return nil if metadata.length < 3
			point_count = metadata[0].to_i
			facet_count = metadata[1].to_i
			points = []
			facets = []
			off[3,point_count].each{|line|
				c = line.split(" ")
				points.push([	c[0].to_f,
											c[1].to_f,
											c[2].to_f])
			}
			off[3+point_count,facet_count].each{|line|
				(indices = line.split(" ")).delete_at(0)
				indices.collect!{|index| index.to_i}
				facets.push(indices)
			}
			Hash[:points => points, :facets => facets]
		end
	end
end
