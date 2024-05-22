//  Includes all necessary code including the Curve class
#include <curve-x/curve.h>
//  Includes the CurveSerializer class, only if you want to import or export
//  the curves data from or to files
#include <curve-x/curve-serializer.h>

//  Includes std::ofstream to output the curve data to files 
#include <fstream>

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
	printf( "Evaluation for x=%f: y=%f\n\n", time, value );
	//  Output:
	//  Evaluation for x=0.300000: y=0.216000

	//  Serialize the curve into a string
	curve_x::CurveSerializer serializer;
	std::string data = serializer.serialize( curve );
	printf( "Curve serialized data:\n%s\n", data.c_str() );
	//  Output:
	//  Curve serialized data:
	//  version:1
	//	0:x=0.000000;y=0.000000,x=-1.000000;y=0.000000,x=1.000000;y=0.000000,0
	//	1:x=1.000000;y=1.000000,x=-1.000000;y=0.000000,x=1.000000;y=0.000000,0

	//  Write the serialized curve into a file
	std::ofstream file( "my_curve.cvx" );
	file << data;
	file.close();
}