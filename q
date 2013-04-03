diff --git a/cpp/rb_Nef_polyhedron_3.cpp b/cpp/rb_Nef_polyhedron_3.cpp
index 6287e2c..44fdb1e 100644
--- a/cpp/rb_Nef_polyhedron_3.cpp
+++ b/cpp/rb_Nef_polyhedron_3.cpp
@@ -143,13 +143,14 @@ Array split(Nef_polyhedron_3 N){
 	vector<Nef_polyhedron_3> nefs;
 	Nef_polyhedron_3::Volume_const_iterator vi = ++N.volumes_begin();
 	Nef_polyhedron_3::Shell_entry_const_iterator si;
-	CGAL_forall_volumes(vi,N) {
+	Nef_polyhedron_3 R;
+	R = N.regularization();
+	CGAL_forall_volumes(vi,R) {
 		if(vi->mark()) {
 			Nef_polyhedron_3::Shell_entry_const_iterator si;
 			CGAL_forall_shells_of(si, vi) {
 				Nef_polyhedron_3::SFace_const_handle sfch(si);
-				cout << sfch->mark();
-				Nef_polyhedron_3 O(N,sfch);
+				Nef_polyhedron_3 O(R,sfch);
 				nefs.push_back(O);
 			}  
 		}
diff --git a/ruby/Nef_polyhedron_3.rb b/ruby/Nef_polyhedron_3.rb
index 78ca174..acf1c72 100644
--- a/ruby/Nef_polyhedron_3.rb
+++ b/ruby/Nef_polyhedron_3.rb
@@ -13,7 +13,7 @@ module CGAL
 				facets.each{|facet|
 					off += "#{facet.length} #{facet.join(" ")} \n"
 				}
-				self.build_polyhedron_from_off(off)
+				self.build_polyhedron_from_off(off).regularization
 				#self.build_polyhedron(args.first[:points], args.first[:facets])
 			elsif args.first.is_a?(Array)
 				self.build_polyline(args.first)
