require 'mkmf-rice'

puts `clear`

pwd = Dir.pwd
Dir.chdir(File.join(File.dirname(__FILE__),"cpp"))

start = Time.now

# Extra configuration parameters for CGAL and others
$LIBS <<  "  -lCGAL -lgmp -lmpfr -lqt-mt  -lGL -lGLU -lglut -lCGAL_Qt3 "
$CFLAGS << " -frounding-math "

# More parameters needed for CGAL and friends
#TODO replace absolute paths below by "have_library('qt3')" or something like that
#WARNING: this needs to be changed in a different system
dir_config('myQt3Libs', '/usr/include/qt3', '/usr/share/qt3/lib') 
#I think this did not work, so in addition, I did this:
#	1) Add a line "/home/rodrigo/CGAL-4.0.2/lib" to the file /etc/ld.so.conf
#	2) Run sudo ldupdate to reflect the changes
dir_config('CGAL_Qt3', 'CGAL/IO', '/home/rodrigo/CGAL-4.0.2/lib') # Replace 3rd argument with right path

create_makefile 'cgal'

puts 'making'
puts `make`

Dir.chdir(pwd)
puts `mv cpp/cgal.so .`

puts "extconf.rb done! (#{Time.now-start} secs)"

