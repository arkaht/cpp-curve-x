#include <curve-x/curve.h>
#include <curve-x/curve-serializer.h>

using namespace curve_x;

int main()
{
	printf( "Curve testing executable\n\n" );

	//  Initialize a curve object
	Curve curve;

	//  Add two keys with different control points
	curve.add_key( CurveKey( { 0.0f, 0.0f } ) );
	curve.add_key( CurveKey( { 1.0f, 1.0f } ) );

	//  Insert a key between the two above
	curve.insert_key( 
		1, 
		CurveKey( 
			{ 0.5f, 0.5f },
			{ -0.5f, -0.5f },
			//  Set the right tangent to have an heavy weight on the Y-axis
			{ 1.0f, 5.0f },
			TangentMode::Broken
		) 
	);

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