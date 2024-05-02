#pragma once

#include <string>

#include "utils.h"

namespace curve_x
{
	/*
	 * Space defining how a point should be interpreted, allowing
	 * conversions between spaces.
	 */
	enum class PointSpace
	{
		/*
		 * Relative to another point, used for tangent points
		 */
		Local,

		/*
		 * Global point, used for control points
		 */
		Global,
	};

	/*
	 * A point consisting of two axes X and Y.
	 *
	 * If raylib is defined before this header file, conversions
	 * constructor and operator for Vector2 will be available.
	 */
	struct Point
	{
	public:
		float x, y;

	public:
		Point()
			: x( 0.0f ), y( 0.0f ) {}
		Point( float x, float y )
			: x( x ), y( y ) {}

#ifdef RAYLIB_H
		Point( const Vector2& vec )
			: x( vec.x ), y( vec.y ) {}
		operator Vector2() const { return Vector2 { x, y }; }
#endif

		Point operator+( const Point& point ) const
		{
			return {
				x + point.x,
				y + point.y
			};
		}
		Point operator-( const Point& point ) const
		{
			return {
				x - point.x,
				y - point.y
			};
		}
		Point operator*( float value ) const
		{
			return {
				x * value,
				y * value
			};
		}
		Point operator/( float value ) const
		{
			return {
				x / value,
				y / value
			};
		}

		Point operator-() const
		{
			return {
				-x,
				-y
			};
		}

		bool operator==( const Point& point ) const
		{
			return x == point.x 
				&& y == point.y;
		}

		/*
		 * Convert the point to a one-line string format.
		 */
		std::string str() const
		{
			return "x=" + std::to_string( x ) + ";" 
				 + "y=" + std::to_string( y );
		}

		/*
		 * Returns a copy of the point whose axes are remapped from 
		 * range 'in' to range 'out'.
		 */
		Point remap( 
			float in_min_x, float in_max_x, 
			float out_min_x, float out_max_x,
			float in_min_y, float in_max_y,
			float out_min_y, float out_max_y
		) const
		{
			return Point {
				Utils::remap( x, 
					in_min_x, in_max_x, 
					out_min_x, out_max_x ),
				Utils::remap( y, 
					in_min_y, in_max_y, 
					out_min_y, out_max_y ),
			};
		}

		/*
		 * Compute the squared magnitude of the point.
		 */
		float length_sqr() const 
		{
			return x * x + y * y;
		}

		/*
		 * Compute the magnitude of the point.
		 */
		float length() const
		{
			return sqrtf( length_sqr() );
		}

		/*
		 * Returns a normalized copy of the point. 
		 * Normalization results in the point magnitude being 1.0f.
		 */
		Point normalized() const
		{
			float m = length();
			return Point {
				x / m,
				y / m,
			};
		}
	};
}