require 'mkmf-rice'

start = Time.now

# Extra configuration parameters for CGAL and others
$LIBS <<  "  -lCGAL -lgmp -lmpfr -lqt-mt  -lGL -lGLU -lglut -lCGAL_Qt3 -lCGAL_Core "
$CFLAGS << " -frounding-math "


#load dir_config to find missing libraries
if File.exists?("dir_config")
	File.open("dir_config", "r") {|io|
		lines = io.readlines
		lines.each{|line|
			params = line.split(" ")
			dir_config(params[0], params[1], params[2]) 
		}
	}
end

#make
Dir.chdir(File.join(File.dirname(__FILE__),"cpp"))
create_makefile 'cgal'
make_result = system("make")
Dir.chdir("..")

if !make_result
	#error message if make fails
	puts "One of the libraies couldn't be found."
	puts "Create a file in this folder called 'dir_config'"
	puts " like so..."
	puts "  name_of_lib path_to_headers path_to_lib"
	puts "just leave a space between each parameter and a new line for each library"
else
	#require cgal and run tests
	puts "Wrapped CGAL for Ruby in #{Time.now-start} secs"
	require_relative("cgal.rb")
	puts "running tests..."
	Dir.glob("test/*.rb").each{|path|
		begin
			load(path)
			puts "#{path}".ljust(30) + " OK"
		rescue
			puts "#{path}".ljust(30) + " failed"
		end
	}
end