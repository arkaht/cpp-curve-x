#include <curve-x/curve.h>
#include <curve-x/curve-serializer.h>

#include <assert.h>

using namespace curve_x;

int main()
{
	printf( "Curve testing executable\n\n" );

	//  Initialize a curve object
	Curve curve;

	//  We have yet not added any keys, so the curve is empty
	assert( curve.get_keys_count() == 0 );

	//  Add two keys with different control points
	curve.add_key( CurveKey( { 0.0f, 0.0f } ) );
	curve.add_key( CurveKey( { 1.0f, 1.0f } ) );

	//  Insert a key between the two above
	curve.insert_key( 
		1, 
		CurveKey( 
			{ 0.5f, 0.5f },
			{ -0.5f, -0.5f },
			//  Set the right tangent to have an heavy weight on the
			//  Y-axis
			{ 1.0f, 5.0f },
			TangentMode::Broken
		) 
	);

	//  Add another key
	curve.add_key( CurveKey( { 2.0f, 3.0f } ) );

	//  We indeed have added 4 keys
	assert( curve.get_keys_count() == 4 );

	//  Remove the last key
	curve.remove_key( 3 );

	//  We are now down to 3 keys
	assert( curve.get_keys_count() == 3 );

	//  Shows the relation of 'point index' to 'key index' by
	//  converting 'point indices' to their related 'key indices'.
	// 
	//  A 'point index' refers to one of the point inside a key 
	//  (either be a control point or a tangent point). A control
	//  point is placed every third 'point index'. Then, in between,
	//  comes its right tangent and left tangent points.
	// 
	//  Therefore, you have two ways of manipulating a curve with 
	//  this library. However, if you would prefer one to another, 
	//  I'd recommend directly using the 'key index' method since 
	//  the 'point index' method use the 'key index' method under 
	//  the hood. 
	//  
	//  Still, some algorithms are more suited with a 'point index' 
	//  method which justifies this design.
	assert( curve.point_to_key_id( 0 ) == 0 );
	assert( curve.point_to_key_id( 1 ) == 0 );
	assert( curve.point_to_key_id( 2 ) == 0 );
	assert( curve.point_to_key_id( 3 ) == 1 );
	assert( curve.point_to_key_id( 4 ) == 1 );
	assert( curve.point_to_key_id( 5 ) == 1 );
	assert( curve.point_to_key_id( 6 ) == 2 );
	assert( curve.point_to_key_id( 7 ) == 2 );
	assert( curve.point_to_key_id( 8 ) == 2 );
	assert( curve.point_to_key_id( 9 ) == 3 );

	//  Does the same thing that above but the other way around: 
	//  converting a 'key index' to its 'point index'.
	// 
	//  Notice that you will only get a 'point index' refering to a
	//  control point (and not to the tangents!).
	assert( curve.key_to_point_id( 0 ) == 0 );
	assert( curve.key_to_point_id( 1 ) == 3 );
	assert( curve.key_to_point_id( 2 ) == 6 );
	assert( curve.key_to_point_id( 3 ) == 9 );

	//  Further proof the link between 'point index' and 'key index'
	//  by demonstrating the two ways of getting the control points 
	//  and the tangent points of a key (in this case, the first key).
	const Point& control_point = curve.get_point( 0 );
	const Point& right_tangent = curve.get_point( 1 );
	const Point& left_tangent = curve.get_point( 2 );
	const CurveKey& key = curve.get_key( 0 );
	assert( control_point == key.control );
	assert( right_tangent == key.right_tangent );
	assert( left_tangent  == key.left_tangent );

	//  It is important to ensure that curves are valid before 
	//  manipulating them (e.g. set/get point, get key, evaluations)
	// 
	//  Curve validity checks that it holds at least 2 keys inside.
	//  Crashes can happen if you try to manipulate an invalid curve.
	assert( curve.is_valid() );

	//  Evaluate the curve by time (i.e. using the X-axis)
	printf( "Evaluation by times:\n" );
	float times[] { 0.0f, 0.5f, 0.6f, 1.0f };
	for ( float time : times )
	{
		float value = curve.evaluate_by_time( time );
		printf( "- x=%.2f: y=%.2f\n", time, value );
	}
	printf( "\n" );

	//  Serialize the curve into a string
	CurveSerializer serializer;
	std::string data = serializer.serialize( curve );
	printf( "Curve serialized data:\n%s\n", data.c_str() );
}