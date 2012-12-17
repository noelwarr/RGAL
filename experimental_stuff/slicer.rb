#Slicer takes a polyhedron and slices it accross the xy plane
#at a given interval. It uses a technique called vertex shifting
#to avoid planes intercepting vertices and edges.
#It has only been tested on triangulated manifold volumes.

class Slicer

  #Specify the starting and finishing values for the z axis
  #Optionally specify how often to perform the slice
  def initialize(z_from, z_to, z_step = 0.5)
    @z_from, @z_to, @z_step = z_from.to_f, z_to.to_f, z_step.to_f
    @shift_value = 0.00001
    @dp = (13)
    @max_loops = 10000 #safety precaution to stop infinite loops 
    @slice_table = Hash.new
    slice_count = ((@z_to - @z_from) / @z_step + 1.0).floor
    slice_count.times{|i|
      z = (@z_from + (i * @z_step)).round(@dp)
      @slice_table[z] = []
    }
  end

  #Arguments can be passed in one of the following ways
  #  slice points, facets
  #    where points are in the form [[x,y,z]...]
  #    and facets refference the points [[1,2,3]...]
  #  slice {points: [[x,y,z]...], facets: [[p1,p2,p3]...]}
  #    this is a convenience method to ease the process
  #
  #Returns a hash of a structure like
  #  {z:[[[x,y,z]...]...]}
  #   z:                    (Hash)
  #     => List of polygons (Array)
  #       => List of points (Array)
  #         => Coordinates  (Array)

  def slice(*args)
    if args[0].is_a? Hash
      structure = args[0].clone
    else
      structure = {points: args[0].clone, facets: args[1].clone}
    end
    @slice_table.each{|slice|slice.clear}
    shift_points(structure)
    link_structure(structure)
    structure[:facets].each{|facet| intersect_facet(facet) }
    @slice_table.each{|z, intersection_list| #link intersections
      facets_list = intersection_list.collect{|intersection| intersection[:facet]}
      intersection_list.each{|intersection|
        next_facet = intersection[:edge][:twin][:facet]
        index = facets_list.index(next_facet)
        intersection[:next] = intersection_list[index]
      }
    }
    @slice_table.each{|z, intersection_list| #organise into polygons
      checklist = []
      polygons = []
      intersection_list.each{|intersection|
        if !checklist.include?(intersection)
          polygon = []
          _intersection = intersection
          i = 0
          begin
            checklist.push _intersection
            polygon.push _intersection[:point]
            _intersection = _intersection[:next]
            i < @max_loops ? i += 1 : raise
          end until intersection == _intersection
          polygons.push polygon
        end
      }
      @slice_table[z] = polygons
    }
  end

  private

  def intersect_edge(edge)
    p1, p2 = edge[:source], edge[:target]
    z = p2[2] - p1[2]
    #only taking into account edges going up ensures edges aren't
    #intersected twice. This works thanks to the fact edges (or
    #halfedges to be more exact) always go around facets in the 
    #same direction.
    if z > 0 
      intersections = []
      slice_modulo = (p1[2] - @z_from) % @z_step 
      slice_start = @z_step - slice_modulo
      x, y = (p2[0]-p1[0]), (p2[1]-p1[1])
      mx = z / x.to_f
      my = z / y.to_f
      i = 0
      until ( slice = slice_start + (i * @z_step) ).abs > z.abs
        i += 1
        _x = ((slice / mx) + p1[0]).round(@dp)
        _y = ((slice / my) + p1[1]).round(@dp)
        _z = ((slice)      + p1[2]).round(@dp)
        intersections.push [_x,_y,_z] if (_z).between?(@z_from,@z_to)
      end
      intersections
    else
      nil
    end
  end

  def intersect_facet(facet)
    facet[:edges].each{|edge|
      intersections = intersect_edge(edge)
      if intersections != nil
        intersections.each{|point|
          z = point[2]
          #add intersection to the slice table
          puts z
          @slice_table[z].push Hash[point: point, edge: edge, facet: facet]
        }
      end
    }
  end

  #Add smart pointers to create a pseudo polyhedral object that
  #can be navigated around
  def link_structure(structure)
    structure[:edges] = Array.new
    structure[:facets].collect!{|array_of_indices|
      facet = Hash.new
      points  = array_of_indices.collect{|index| structure[:points][index] }
      edges = [points, points.rotate].transpose.collect{|p1,p2|
        {source: p1, target: p2, facet: facet}
      }
      structure[:edges] += edges
      facet[:points] = points
      facet[:edges] = edges
      facet
    }
    source2target_list = structure[:edges].collect{|edge| [edge[:source], edge[:target]]}
    structure[:edges].each{|edge|
      target2source = [edge[:target], edge[:source]]
      index = source2target_list.index(target2source)
      edge[:twin] = structure[:edges][index]
    }
    structure
  end

  #Avoid vertex and edge intersections
  def shift_points(structure)
    structure[:points].collect!{|point|
      z = point[2]
      if (((z - @z_from) % @z_step).round(@dp) == 0.0)
        point[2] = z - @shift_value 
      end
      point
    }
  end

end

slicer = Slicer.new(0,1,0.5)
result = slicer.slice({:points=>[[337.235720855427, 101.688004593451, 19.0], [303.135720855427, 310.588004593451, 19.0], [303.135720855427, 101.688004593451, 19.0], [337.235720855427, 310.588004593451, 19.0], [500.0, 500.0, 0.0], [0.0, 0.0, 0.0], [0.0, 500.0, 0.0], [500.0, 0.0, 0.0], [500.0, 0.0, 19.0], [500.0, 500.0, 19.0], [0.0, 500.0, 19.0], [0.0, 0.0, 19.0], [68.2148678450297, 64.1898730708488, 19.0], [435.31486784503, 64.1898730708488, 19.0], [435.31486784503, 409.289873070849, 19.0], [68.2148678450297, 409.289873070849, 19.0], [219.435620058057, 145.604320118039, 19.0], [129.735620058057, 328.104320118039, 19.0], [129.735620058057, 145.604320118039, 19.0], [219.435620058057, 328.104320118039, 19.0], [68.2148678450297, 64.1898730708488, 4.00000000000001], [129.735620058057, 145.604320118039, 4.00000000000001], [68.2148678450297, 409.289873070849, 4.00000000000001], [435.31486784503, 64.1898730708488, 4.00000000000001], [303.135720855427, 101.688004593451, 4.00000000000001], [219.435620058057, 145.604320118039, 4.00000000000001], [219.435620058057, 328.104320118039, 4.00000000000001], [337.235720855427, 101.688004593451, 4.00000000000001], [337.235720855427, 310.588004593451, 4.00000000000001], [129.735620058057, 328.104320118039, 4.00000000000001], [435.31486784503, 409.289873070849, 4.00000000000001], [303.135720855427, 310.588004593451, 4.00000000000001]], :facets=>[[0, 1, 2], [1, 0, 3], [4, 5, 6], [5, 4, 7], [4, 8, 7], [8, 4, 9], [10, 4, 6], [4, 10, 9], [11, 12, 10], [12, 11, 8], [12, 8, 13], [13, 8, 14], [10, 15, 9], [15, 10, 12], [9, 15, 14], [9, 14, 8], [8, 5, 7], [5, 8, 11], [10, 5, 11], [5, 10, 6], [16, 17, 18], [17, 16, 19], [20, 21, 22], [21, 20, 23], [21, 23, 24], [21, 24, 25], [25, 24, 26], [24, 23, 27], [27, 23, 28], [22, 29, 30], [29, 22, 21], [30, 29, 26], [30, 26, 31], [31, 26, 24], [30, 31, 28], [30, 28, 23], [14, 23, 13], [23, 14, 30], [14, 22, 30], [22, 14, 15], [22, 12, 20], [12, 22, 15], [12, 23, 20], [23, 12, 13], [17, 26, 29], [26, 17, 19], [26, 16, 25], [16, 26, 19], [16, 21, 25], [21, 16, 18], [17, 21, 18], [21, 17, 29], [1, 28, 31], [28, 1, 3], [28, 0, 27], [0, 28, 3], [0, 24, 27], [24, 0, 2], [1, 24, 2], [24, 1, 31]]})
puts result[0.5]