#pragma once

#include "point.h"

namespace curve_x
{
	/*
	 * Tangent mode which defines the constraint by which tangents
	 * behave in relation to each other.
	 */
	enum class TangentMode
	{
		/*
		 * Mirroring tangent directions and lengths.
		 */
		Mirrored	= 0,

		/*
		 * Tangent directions are aligned with individual lengths.
		 */
		Aligned		= 1,

		/*
		 * Both tangents have their own direction and length.
		 */
		Broken		= 2,

		MAX,
	};

	/*
	 * A key inside a curve consisting of a control point, two
	 * tangents and the related tangent mode.
	 * 
	 * Tangent points are stored in local-space, forming a weighted 
	 * direction from the control point.
	 */
	class CurveKey
	{
	public:
		CurveKey( 
			const Point& control, 
			const Point& left_tangent = { -1.0f, 0.0f },
			const Point& right_tangent = { 1.0f, 0.0f },
			TangentMode tangent_mode = TangentMode::Mirrored
		);

		/*
		 * Set the location of the left tangent (in local space) 
		 * and applies the tangent mode constraint on the right 
		 * tangent.
		 */
		void set_left_tangent( const Point& point );
		/*
		 * Set the location of the right tangent (in local space) 
		 * and applies the tangent mode constraint on the left 
		 * tangent.
		 */
		void set_right_tangent( const Point& point );

	public:
		Point control;
		Point left_tangent;
		Point right_tangent;

		TangentMode tangent_mode;

		//  TODO: Implement the distance on the curve for each key 
		//float distance = -1.0f;

	private:
		/*
		 * Set the location of the target tangent (in local space) 
		 * and applies the tangent mode constraint on the peer 
		 * tangent.
		 */
		void _set_tangent( 
			const Point& point, 
			Point* target_tangent,
			Point* peer_tangent
		);
	};
}