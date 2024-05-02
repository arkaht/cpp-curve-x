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

	//  It is important to ensure that curves are valid before 
	//  manipulating them (e.g. set/get point, get key, evaluations)
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