require 'json'
load ('../core.rb')

puts 'Testing affine transformations'

AF = CGAL::Aff_transformation_3
t=AF.build_matrix([1,2,3,4,5,6,7,8,9,10,11,12,1])
t.print_matrix

t2=AF.build_matrix([1,2,3,4,5,6,7,8,9,1])
t2.print_matrix

p = CGAL::Point_3.build(1,2,3)
#q = t.transform_Point_3(p) #Scales point p by a factor 2

#puts [q.x,q.y,q.z]

nef = CGAL::Nef_polyhedron_3.build([[0,0,0],[1,0,0],[0,1,0],[Math::PI,Math.sqrt(2),1.23456789123456789]],[[0,1,3],[1,2,3],[2,0,3],[0,2,1]])
puts (nef_string = CGAL::Nef_polyhedron_3::dump(nef)).split("\n")[9,4]
CGAL::Nef_polyhedron_3::load(nef_string)
