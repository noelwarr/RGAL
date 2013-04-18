require_relative "../cgal.rb"

def move
	points = [[0,0,0],[0,0,1]].collect{|p|CGAL::Point_3.new(p)}
	n1 = CGAL::Nef_polyhedron_3.new(points, :polyline)
	xform = CGAL::Aff_transformation_3.build_translation(1,1,0)
	n2 = n1.transform!(xform)
	
end

move