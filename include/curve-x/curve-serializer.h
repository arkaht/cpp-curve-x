#pragma once

#include <string>

#include "curve.h"

namespace curve_x
{
	/*
	 * Current format version for the serializer. 
	 * When unserializing, this is used to compare the version of 
	 * the data, allowing conversions from older to newer versions.
	 * 
	 * For now, since its the very first version, this is intended 
	 * for forward compatibility.
	 */
	const int         FORMAT_VERSION = 1;
	/*
	 * Conventional file extension to use for curve files.
	 */
	const std::string FORMAT_EXTENSION = "cvx";

	/*
	 * Helper class aiming to serialize and unserialize curves data,
	 * in order to export and import them to and from files.
	 * 
	 * It uses its own simple and human-readable text format.
	 */
	class CurveSerializer
	{
	public:
		CurveSerializer();

		/*
		 * Serializes the given curve into a string.
		 */
		std::string serialize( const Curve& curve );

		/*
		 * Un-serialize the given string data into a curve object.
		 * 
		 * The given string is assumed to be in the correct format.
		 * Exceptions can be thrown otherwise.
		 */
		Curve unserialize( const std::string& data );

	private:
		/*
		 * Converts a string into the integer it represents.
		 */
		int _to_int( const std::string& str );
		/*
		 * Converts a string into the float it represents.
		 */
		float _to_float( const std::string& str );
		/*
		 * Converts two strings into the point they represents.
		 */
		Point _to_point( 
			const std::string& str_x, 
			const std::string& str_y 
		);
	};
}