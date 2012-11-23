#require main c extension
require_relative 'cpp/cgal.so'

#Monkey patch!!!
Dir.glob(File.join(File.dirname(__FILE__),"ruby","*.rb")).each{|path|
	require path
}