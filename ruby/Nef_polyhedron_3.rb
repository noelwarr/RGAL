require_relative '../cgal.rb'
module CGAL
	class Nef_polyhedron_3
		def self.new(*args)
			if args.first == nil
				self.build
			elsif args.first.is_a?(Hash)
				points = args.first[:points]
				facets = args.first[:facets]
				off = "OFF\n#{points.length} #{facets.length} 0\n"
				points.each{|point|
					off += "#{point.join(" ")}\n"
				}
				facets.each{|facet|
					off += "#{facet.length} #{facet.join(" ")} \n"
				}
				self.build_polyhedron_from_off(off).regularization
				#self.build_polyhedron(args.first[:points], args.first[:facets])
			elsif args.first.is_a?(Array)
				self.build_polyline(args.first)
			end
		end

		def self.build_cube(x,y,z)
			self.build_polyhedron( [[0,0,0],[x,0,0],[x,y,0],[0,y,0],[0,y,z],[0,0,z],[x,0,z],[x,y,z]],
									[[0,1,6,5],[1,2,7,6],[2,3,4,7],[3,0,5,4],[3,2,1,0],[4,5,6,7]])
		end

		def transform(transformation)
			nef = Nef_polyhedron_3.clone(self)
			nef.transform!(transformation)
			nef
		end

		def structure
			volumes = Array.new
			self.split.each{|nef|
				nef = nef.closure.regularization
				if !nef.empty? 
					volumes.push parse_off(nef.closure.regularization.to_off)
				end
			}
			volumes
		end

		def dump
			self.class.dump(self).force_encoding('utf-8')
		end

		def intersect?(nef2)
			!(self * nef2).empty?
		end

		private
		def parse_off(off)
			off = off.split "\n"
			metadata = off[1].split(" ")
			return nil if metadata.length < 3
			point_count = metadata[0].to_i
			facet_count = metadata[1].to_i
			points_map 	= Hash.new
			facets_map 	= Hash.new
			points 			= Array.new
			facets 			= Array.new
			off[3,point_count].each{|line|
				c = line.split(" ")
				points.push([	c[0].to_f,
											c[1].to_f,
											c[2].to_f])
			}
			off[3+point_count,facet_count].each{|line|
				indices = line.split(" ")[1,3]
				indices.collect!{|index| 
					p = points[index.to_i]
					if points_map[p].nil?
						i = points_map.length
						points_map[p] =	i
					else
						points_map[p]
					end
				}
				if indices.uniq.length > 2
					duplicate = false
					indices.permutation.each{|facet|
						duplicate = true if facets_map.has_key? facet
						
					}
					facets_map[indices] = true if duplicate == false
				end
			}
			#remove duplicate points and link facets to them
			Hash[:points => points_map.keys, :facets => facets_map.keys]
		end
	end
end