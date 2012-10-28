require 'json'
load ('../core.rb')
js = File.open('../dev/l.json').read
jo = JSON.parse js
wp = Workpiece.new(jo)
