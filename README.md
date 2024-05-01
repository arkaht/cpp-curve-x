# Curve-X
**Curve-X is a small and easy-to-use C++ Bézier library to create 2D-splines with its own optional GUI editor.**

*If you are a game developer working on its own C++ engine and you want to have fine control over your values (let's say: gamepad sensitivity, dynamic FOV depending on the player's speed, gravity force, particle effects, animations, etc.) for the sake of game feel, this project may interests you.*

Curve-X allows to create 2D-splines, either they are intended to be geometrical shapes or for timed-based values. It is simple of usage yet allows a lot of manipulation. The code is also well-documented: each class, functions and enums are properly described.

This project is split into two Github repositories: the library (this one) and the [GUI editor application](https://github.com/arkaht/cpp-curve-editor-x). You are not forced to use the editor, it is entirely optional but it is here to facilitate your experience with Curve-X.

By default, the project is built for C++17, yet it is compatible with the versions specified in [Dependencies](#dependencies).

Originally, it was both a learning project to know more about curves and also a side-project because I wanted time-based curves for my game engine so I could better control the feeling of my games. It is also my first time using CMake and Git Submodules (used in the editor repository).

This project is still under development, feel free to raise issues as you encounter them.

## Dependencies 
+ C++11, 14, 17 or 20 compiler
+ CMake 3.11 is optional
+ *Nothing else...*

## Features
+ **Carefully well-documented code for classes, functions and enums**
+ Written in **simple and straightforward C++17** using **snake_case** notation
+ Project IDE-independent thanks to **CMake**
+ **Custom [GUI editor](https://github.com/arkaht/cpp-curve-editor-x) to easily create and edit curve files**
+ Support for both geometrical shapes and timed-based curves
+ Multiple evaluation methods: progress (from 0.0 to 1.0), time (using X-axis) and distance.
+ **Embedded curves serialization and un-serialization methods**
+ Custom and human-readable text format for curves serialization
+ **Free and open-source**

## Code Example
From [`tests/simple_example.cpp`](https://github.com/arkaht/cpp-curve-x/tree/master/tests/simple_example.cpp):
```cpp
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
```

For more examples, look at the [`tests/`](https://github.com/arkaht/cpp-curve-x/tree/master/tests) folder.

## Getting Started
This project is built using **CMake 3.11**. However, it is not required to use it on your project with proper setup.

### Add the library to your project
#### With CMake
1. Clone the library or download the ZIP and extract it
2. Move the library inside a folder for the libraries of your project, for example: 
```
<your_project>/
| libs/
| | curve-x/
| | | CMakeLists.txt
| | | ...
| CMakeLists.txt
| ...
```
3. In your `CMakeLists.txt`:
+ Use `add_subdirectory` with the library's path to include it:
```cmake
add_subdirectory( "libs/curve-x" )
```
+ Link the library to your project with `target_link_libraries`:
```cmake
target_link_libraries(<your_project_target> PRIVATE curve_x <your_project_libs>)
```

#### Without CMake
*To be written...*

### Build the project
*To be written...*

## References
This library has been possible thanks to all these online resources:
+ [The Continuity of Splines](https://www.youtube.com/watch?v=jvPPXbo87ds) by **Freya Holmér**
+ [Cubic Hermite spline](https://en.wikipedia.org/wiki/Cubic_Hermite_spline) from **Wikipedia**
+ [Bézier spline](https://en.wikipedia.org/wiki/B%C3%A9zier_curve) from **Wikipedia**
+ [Curves and Splines](https://catlikecoding.com/unity/tutorials/curves-and-splines/) from **Catlike Coding**
+ [A Primer on Bézier Curve](https://pomax.github.io/BezierInfo-2/) by **Pomax**
+ **Unreal Engine**'s `FRichCurve` code for evaluation by time