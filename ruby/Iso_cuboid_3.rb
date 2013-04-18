class CGAL::Iso_cuboid_3
	def self.new(points)
		self.build points
	end

	def to_a
		(0..7).collect {|i| self[i] }
	end

	def to_nef
		points = self.to_a
		facets = [[3,2,1,0], 																#bottom
							[0,1,6,5],[1,2,7,6],[2,3,4,7],[3,0,5,4],	#sides
							[4,5,6,7]]																#top
		CGAL::Nef_polyhedron_3.build_polyhedron(points, facets)
	end

end