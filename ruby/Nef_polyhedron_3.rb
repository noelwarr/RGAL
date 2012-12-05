module CGAL
	class Nef_polyhedron_3
		def new(*args)
			type = args[0].is_a?(Symbol) ? args[0] : :polyhedron
			
		end
	end
end
