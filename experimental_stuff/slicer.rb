off = File.open("socket.off").read.split("\n")
off.delete_if{|line| line[0,1] == "#"}
vertex_count, facet_count, edges_count =  off[1].split(" ").collect{|s|s.to_i}
points = off[2,vertex_count].collect{|line|
  line.split(" ").collect{|s|s.to_f}
}
facets = off[(2+vertex_count),facet_count].collect{|line|
  split = line.split(" ")
  index_count = split[0].to_i
  split[1,index_count].collect{|s|s.to_i}
}
class Slicer < Hash
  def initialize(z_from, z_to, z_step = 0.5)
    @z_from, @z_to, @z_step = z_from.to_f, z_to.to_f, z_step.to_f
    @shift_value = 0.00001
    slice_count = ((@z_to - @z_from) / @z_step).ceil
    slice_count.times{|i|
      z = @z_from + (i * @z_step)
      self[z] = []
    }
  end
  def slice(hash)
    @structure = hash
    shift_points!
    link_facets!
    @structure[:facets].each{|facet| intersect_facet(facet[:points])}
    self.values.each_with_index{|lines,i|
      puts lines if i == 25
      lines.each{|line|
        find_next_line(line,lines)
      }      
    }
  end
  private
  def find_next_line(line, lines)
    p1, p2 = line
    lines.each_with_index{|_line, index|
      return index if _line[0] == p2
    }
    raise
  end
  def intersect_edge(edge)
    p1, p2 = edge
    z = p2[2] - p1[2]
    direction = (z<0 ? -1 : 1)
    intersections = []
    if z != 0
      slice_modulo = (p1[2] - @z_from) % @z_step 
      if slice_modulo == 0
        slice_start = 0
      elsif z > 0
        slice_start = @z_step - slice_modulo
      else
        slice_start = -slice_modulo
      end
      x, y = (p2[0]-p1[0]), (p2[1]-p1[1])
      mx = z / x
      my = z / y
      i = 0
      #puts "#{p1[2]} #{p2[2]} #{slice_start}"
      until ( slice = slice_start + (i * @z_step) ).abs > z.abs
        i += direction
        _x = ((slice / mx) + p1[0]).round(13)
        _y = ((slice / my) + p1[1]).round(13)
        _z = ((slice)      + p1[2]).round(13)
        intersections.push [_x,_y,_z] if (_z).between?(@z_from,@z_to)
      end
    end
    return intersections
  end
  def intersect_facet(facet)
    edges = [facet, facet.rotate].transpose
    edge_intersections = edges.collect{|edge| intersect_edge(edge)}
    #edge_intersections.each{|intersection| puts intersection.map{|p| p.join(",")}.join " - "}
    #puts edge_intersections.collect{|intersection| intersection.length }.join(" ")
    lengths = edge_intersections.collect{|a|a.length}
    index = lengths.index(lengths.max)
    lines = [ edge_intersections[index],
            ( edge_intersections[index-2] + edge_intersections[index-1]).reverse ].transpose
    lines.each{|p1, p2|
      if p1[2] != p2[2]
        self.clear
        raise
      end
      z = p1[2]
      self[z].push [p1, p2]
    }
  end
  def link_facets!
    @structure[:facets].collect!{|facet|
      { points: facet.collect{|index|@structure[:points][index]} }
    }
  end
  def shift_points!
    @structure[:points].each{|point|
      z = point[2]
      if (((z - @z_from) % @z_step).round(13) == 0.0)
        point[2] = z - @shift_value 
      end
    }
  end
end

#Slicer.new(0.2,0.8,0.2).slice({points: [[0,0,0.5],[1,0,0],[0,1,0],[0,0,1]], facets: [[0,1,3],[1,2,3],[2,0,3],[2,1,0]]})
Slicer.new(-100,100,1).slice({points: points, facets: facets})