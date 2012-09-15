pwd = Dir.pwd
Dir.chdir(File.join(File.dirname(__FILE__),"cpp"))
require 'mkmf-rice'
puts `clear`
start = Time.now
libraries = "-lCGAL -lgmp -lmpfr"
create_makefile 'cgal'
puts 'modifying makefile for CGAL'
filecontent = File.open('Makefile').to_a
File.open('Makefile', "w+"){|file|
	filecontent.each{|line|
		if line[0,4] == "LIBS"
			line = line.insert(7, libraries + " ")
    elsif line[0,8] == "CXXFLAGS"
      line = line.insert(21, "-frounding-math ")
		end
		file.puts line
	}  
}
puts 'making'
puts `make`
Dir.chdir(pwd)
puts `mv cpp/cgal.so .`
puts "Done! (#{Time.now-start} secs)"

