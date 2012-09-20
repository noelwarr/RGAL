require 'json'
require_relative ("../core.rb")
js = File.open('test/wp.json').read
jo = JSON.parse js
wp = Workpiece.new(jo)
