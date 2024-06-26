#pragma once

#include <vector>

#include "point.h"
#include "key.h"

namespace curve_x
{
	/*
	 * The extrems coordinates of a curve, these bounds can be
	 * represented in a rectangle.
	 */
	struct CurveExtrems
	{
		float min_x, max_x;
		float min_y, max_y;
	};

	/*
	 * Default precision value for iteration steps.
	 * Used for length and nearest point distance calculations.
	 */
	constexpr float ITERATIONS_STEPS = 1.0f / 100.0f;

	/*
	 * A Bézier cubic 2D-spline consisting of a vector of curve 
	 * keys. 
	 
	 * A curve should either represent a geometrical shape or 
	 * timed-values as the evaluation can be done either by the 
	 * percentage on the curve (from 0.0f to 1.0f), by distance 
	 * (in relation to the curve length) or by time (the X-axis).
	 * 
	 * Keys are referenced by using a 'key index', which is 
	 * basically the index used to store the key inside the keys 
	 * vector.
	 * 
	 * A 'point index' refers to an index inside a theoritical 
	 * vector where all control points and tangent points of all 
	 * keys are merged in this order: control point 0, right 
	 * tangent 0, left tangent 0, control point 1, right tangent 1,
	 * left tangent 1, etc. 
	 * 
	 * For this reason, a 'point index' can either refer to a 
	 * control point or to a tangent point.
	 * 
	 * Nevertheless, there are helper functions to convert 'key 
	 * indices' to 'point indices' and vice-versa.
	 */
	class Curve
	{
	public:
		Curve();
		Curve( const std::vector<CurveKey>& keys );

		/*
		 * Evaluate a curve point at given percent, in range from 
		 * 0.0f to 1.0f.
		 */
		Point evaluate_by_percent( float t ) const;
		/*
		 * Evaluate a curve point at given distance.
		 * 
		 * Internally using 'evaluate_by_percent' by dividing the
		 * distance by the curve length.
		 */
		Point evaluate_by_distance( float dist ) const;
		/*
		 * Evaluate the Y-axis value corresponding to the given 
		 * time on the X-axis.
		 * 
		 * NOTE: This evaluation method does NOT take in account 
		 * the tangents X-axis right now. 
		 * See: https://github.com/arkaht/cpp-curve-x/issues/1
		 */
		float evaluate_by_time( float time ) const;

		/*
		 * Add a key at the end of the vector.
		 */
		void add_key( const CurveKey& key );
		/*
		 * Insert a key before given index. 
		 * The index must refer either to a valid key or to the 
		 * keys count.
		 */
		void insert_key( int key_id, const CurveKey& key );
		/*
		 * Remove a key at given index. 
		 * The index must refer to a valid key.
		 */
		void remove_key( int key_id );

		/*
		 * Get a reference to the key at given index.
		 * The index must refer to a valid key.
		 */
		CurveKey& get_key( int key_id );
		/*
		 * Get a const-reference to the key at given index.
		 * The index must refer to a valid key.
		 */
		const CurveKey& get_key( int key_id ) const;

		/*
		 * Set the location at the given point index.
		 * The index must refer to a valid point.
		 */
		void set_point( int point_id, const Point& point );
		/*
		 * Set the location at the given point index, assuming it 
		 * is a tangent point, and apply the tangent mode to its 
		 * peer.
		 * 
		 * Since tangents are stored relatively to their control 
		 * point, this function handles point-space conversion.
		 * 
		 * The index must refer to a valid point.
		 */
		void set_tangent_point( 
			int point_id, 
			const Point& point,
			PointSpace point_space = PointSpace::Local
		);

		/*
		 * Get the location from the specified point index.
		 * The index must refer to a valid point.
		 */
		Point get_point( 
			int point_id, 
			PointSpace point_space = PointSpace::Local
		) const;
		/*
		 * Compute the nearest point on the curve from an arbitrary 
		 * global-space point.
		 */
		Point get_nearest_point_to(
			const Point& point,
			const float steps = ITERATIONS_STEPS
		) const;
		/*
		 * Compute the nearest curve distance from an arbitrary 
		 * global-space point.
		 */
		float get_nearest_distance_to(
			const Point& point,
			const float steps = ITERATIONS_STEPS
		) const;

		/*
		 * Convert any point index to its key index.
		 */
		int point_to_key_id( int point_id ) const;
		/*
		 * Convert a key index to its control point index.
		 */
		int key_to_point_id( int key_id ) const;
		
		/*
		 * Change the tangent mode for the given key index.
		 * 
		 * By default, it applies the new mode constraint to both 
		 * tangents.
		 * 
		 * The index must refer to a valid key.
		 */
		void set_tangent_mode( 
			int key_id, 
			TangentMode mode, 
			bool should_apply_constraint = true
		);
		/*
		 * Returns the tangent mode of given key index.
		 * The index must refer to a valid key.
		 */
		TangentMode get_tangent_mode( int key_id ) const;

		/*
		 * Returns whenever the curve contains a valid amount of 
		 * points for further usage.
		 * 
		 * It's important to first check the curve validity before 
		 * using other methods since they do not check about it. 
		 * It prevent crashes to happen.
		 */
		bool is_valid() const;
		/*
		 * Returns whenever the given key index refers to a
		 * valid key.
		 */
		bool is_valid_key_id( int key_id ) const;
		/*
		 * Returns whenever the given point index refers to a
		 * valid point.
		 */
		bool is_valid_point_id( int point_id ) const;
		/*
		 * Returns whenever the given point index refers to
		 * a control point or to a tangent point.
		 */
		bool is_control_point_id( int point_id ) const;

		/*
		 * Fill given variables to the coordinates extrems of all
		 * points.
		 */
		void get_extrems( 
			float* min_x, float* max_x, 
			float* min_y, float* max_y 
		) const;
		/*
		 * Returns the coordinates extrems of all points.
		 */
		CurveExtrems get_extrems() const;

		/*
		 * Fill given variables with the first & last key indexes 
		 * to use for evaluation from given time.
		 */
		void find_evaluation_keys_id_by_time( 
			int* first_key_id,
			int* last_key_id,
			float time 
		) const;
		/*
		 * Fill given variables with the first & last key indexes 
		 * to use for evaluation from given percent. 
		 * 
		 * Variable 't' may be modified after the function call.
		 */
		void find_evaluation_keys_id_by_percent(
			int* first_key_id,
			int* last_key_id,
			float& t
		) const;
		/*
		 * Fill given variables with the first & last key indexes 
		 * to use for evaluation from given distance.
		 */
		void find_evaluation_keys_id_by_distance(
			int* first_key_id,
			int* last_key_id,
			float d
		) const;

		/*
		 * Returns the size of the keys vector.
		 */
		int get_keys_count() const;
		/*
		 * Returns the number of curves formed by the keys.
		 * Basically, the number of keys minus one.
		 */
		int get_curves_count() const;
		/*
		 * Returns the number of points.
		 */
		int get_points_count() const;

		/*
		 * Compute the curve's length, representing the maximum 
		 * evaluable distance.
		 */
		void compute_length( const float steps = ITERATIONS_STEPS );

		/*
		 * Get the length of the curve. 
		 * If marked as dirty, the length is updated beforehand.
		 */
		float get_length();
		/*
		 * Get the previously computed length of the curve. 
		 * 
		 * Due to constness, it will NOT update the length if 
		 * marked as dirty. You may want to manually compute the 
		 * length AFTER modifying the curve and BEFORE passing it 
		 * as a const-reference.
		 */
		float get_length() const;

	public:
		/*
		 * Boolean stating whenever the length need to be updated.
		 */
		bool is_length_dirty = true;

	private:
		/*
		 * Length of the curve, representing its maximum distance.
		 * It is automatically computed after changes to the curve.
		 */
		float _length = 0.0f;

		/*
		 * Vector containing the keys.
		 * The required index is refered as a 'key index'.
		 */
		std::vector<CurveKey> _keys;
	};
}