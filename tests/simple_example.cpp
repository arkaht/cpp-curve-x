//  Includes all necessary code including the Curve class
#include <curve-x/curve.h>
//  Includes the CurveSerializer class, only if you want to import or export
//  the curves data from or to files
#include <curve-x/curve-serializer.h>

int main()
{
	//  Initialize a curve object
	curve_x::Curve curve;

	//  Add two keys with different control points
	curve.add_key( curve_x::CurveKey( { 0.0f, 0.0f } ) );
	curve.add_key( curve_x::CurveKey( { 1.0f, 1.0f } ) );

	//  Evaluate the curve at x=0.3f
	float time = 0.3f;
	float value = curve.evaluate_by_time( time );
	printf( "Evaluation for x=%.2f: y=%.2f\n\n", time, value );
	//  Output:
	//  Evaluation for x=0.30: y=0.22

	//  Serialize the curve into a string
	curve_x::CurveSerializer serializer;
	std::string data = serializer.serialize( curve );
	printf( "Curve serialized data:\n%s\n", data.c_str() );
	//  Output:
	//  version:1
	//	0:x=0.000000;y=0.000000,x=-1.000000;y=0.000000,x=1.000000;y=0.000000,0
	//	1:x=1.000000;y=1.000000,x=-1.000000;y=0.000000,x=1.000000;y=0.000000,0
}