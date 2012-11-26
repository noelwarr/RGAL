
module CGAL
	##
	# Affine_transformations
	class Aff_transformation_3
		##
		# :call-seq:
		# 	Aff_transfromation_3.new() => identity_transformation
		# 	Aff_transfromation_3.new(:identity_transformation) => identity_transformation
		# 	Aff_transfromation_3.new(:scaling, factor) => scaling_transformation
		#   Aff_transfromation_3.new(:scaling, factor_numerator, factor_denominator) => scaling_transformation
		# 	Aff_transfromation_3.new(:translation, array_representing_vector) => translation_transformation
		# 	Aff_transfromation_3.new(array_9) => linear_matrix_transformation
		# 	Aff_transfromation_3.new(array_10) => linear_matrix_transformation
		# 	Aff_transfromation_3.new(array_12) => affine_matrix_transformation
		# 	Aff_transfromation_3.new(array_13) => affine_matrix_transformation
		# 	Aff_transfromation_3.new(array_13) => affine_matrix_transformation
		# 	Aff_transfromation_3.new(array_13) => affine_matrix_transformation
		# 	Aff_transfromation_3.new(:rotation, :x, angle) => rotation_transformation
		# 	Aff_transfromation_3.new(:rotation, :y, angle) => rotation_transformation
		# 	Aff_transfromation_3.new(:rotation, :z, angle) => rotation_transformation

		def self.new(*args)
			if args[0].is_a?(Array) && [9,10,12,13].include?(args[0].length)
				transformation_type = :matrix
			else
				transformation_type = args[0] || :identity_transformation
			end
			if transformation_type == :identity_transformation
				#IDENTITY
				self.build_identity();
			elsif transformation_type == :scaling
				#TRANSFORMATION can take one (factor) or two (a/b) arguments
				self.build_scaling(args[1], (args[2] || 1.0))
			elsif transformation_type == :translation
				#TRANSLATION this should take a vector_3 as an argument.  At the moment just array
				self.build_translation(args[1][0],args[1][0],args[1][0])
			elsif transformation_type == :matrix
				#MATRIX
				matrix = args[0]
				matrix.push(1) if (matrix.length == 9 || matrix.length == 12)
				build_matrix(matrix)
			elsif transformation_type == :rotation
				#ROTATION
				build_rotation_axis(args[1].to_s, args[2])
			else
				#This should have better feedback
				raise ArgumentError
			end
		end

		##
		# :call-seq: transformation.transform(Point_3) => Point_3
		def transform(arg)
			transform_Point_3(arg)
		end

		##
		# :method: *

		##
		# :method: inverse

		##
		# :method: is_even

		##
		# :method: is_odd

		##
		# :method: m
		
		##
		# :method: hm

	end
end

