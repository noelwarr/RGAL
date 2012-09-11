require 'mkmf-rice'
libraries = "-lCGAL -lgmp -lmpfr"
puts `clear`
Dir.chdir(File.join(File.dirname(__FILE__.),"cpp"))
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
start = Time.now
puts `make`
puts 'Done! (#{Time.now-start} secs)'

