#ifndef ENUMS_H
#define ENUMS_H

#include "nau/math/data.h"

#include <string>
#include <vector>

#ifdef _WINDLL
#ifdef nau_EXPORTS
#define nau_API __declspec(dllexport)   
#else  
#define nau_API __declspec(dllimport)   
#endif 
#else
#define nau_API
#endif

namespace nau {
	
	class Enums
	{

	public:

		enum DataType {
						INT, IVEC2, IVEC3, IVEC4,
						UINT, UIVEC2, UIVEC3, UIVEC4,
						BOOL, BVEC2, BVEC3, BVEC4,
						FLOAT, VEC2, VEC3, VEC4,
						DOUBLE, DVEC2, DVEC3, DVEC4,
						MAT2, MAT3, MAT4, 
						MAT2x3, MAT2x4, 
						MAT3x2, MAT3x4,
						MAT4x2, MAT4x3,
						DMAT2, DMAT3, DMAT4,
						DMAT2x3, DMAT2x4,
						DMAT3x2, DMAT3x4,
						DMAT4x2, DMAT4x3,

						SAMPLER,
						ENUM,

						BYTE, UBYTE, SHORT, USHORT, STRING, INTARRAY,
						COUNT_DATATYPE
		};

		// note: must capitalize all static functions
		static nau_API int getCardinality(DataType p);
		static nau_API Enums::DataType getType(std::string s);
		static nau_API bool isValidType(std::string s);
		static nau_API int getSize(DataType p);
		static nau_API nau::math::Data *getDefaultValue(DataType p);
		//static void* getDefaultValue(DataType p);
		/// returns true if p1 is compatible with p2 
		static nau_API bool isCompatible(DataType p1, DataType p2);
		static nau_API bool isBasicType(DataType t);

		static nau_API const std::vector<std::string> DataTypeToString;
		static nau_API const std::vector<std::string> &GetDataTypeToString();
		static nau_API const std::string valueToString(DataType p, void *v);
		//static std::string &valueToStringAligned(DataType p, void *v);
		static nau_API DataType getBasicType(DataType dt);
		static nau_API std::string pointerToString(DataType p, void *v);
		static nau_API std::string pointerToString(DataType p, void *v, int arraySize);
		static nau_API std::string pointerToStringAligned(DataType p, void *v);

	private:
		static std::string m_Result;

	};
};

#endif // TYPES_H