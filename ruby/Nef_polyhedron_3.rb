module CGAL
	class Nef_polyhedron_3
		def self.build_cube(x,y,z)
			self.build( [[0,0,0],[x,0,0],[x,y,0],[0,y,0],[0,y,z],[0,0,z],[x,0,z],[x,y,z]],
									[[0,1,6,5],[1,2,7,6],[2,3,4,7],[3,0,5,4],[3,2,1,0],[4,5,6,7]])
		end
	end
end