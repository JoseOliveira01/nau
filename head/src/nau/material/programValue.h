#ifndef PROGRAMVALUE_H
#define PROGRAMVALUE_H

#include <string>
#include "nau/enums.h"

namespace nau {

	namespace material {
      
		class ProgramValue {
	 
		public:
 
		private:
			std::string m_TypeString;
			//SEMANTIC_TYPE m_Type;
			int m_ValueOf;
			nau::Enums::DataType m_ValueType;
			std::string m_Context, m_Name;
			std::string m_Param;
			void *m_Values = NULL;
		//	float* m_Value;
		//	int *m_IntValue;
			int m_Cardinality = 0;
			int m_Id = -1;
			int m_Loc = -1;
			bool m_InSpecML; // true for values specified in the material library, false for other uniforms
			float m_fDummy;
		public:

			ProgramValue ();
			ProgramValue (std::string name, std::string type,std::string context,std::string valueof, int id, bool inSpecML = true);
			~ProgramValue();

			void clone(ProgramValue &pv);

			std::string getName();
			std::string getType();
			std::string getContext();
			void setContext(std::string s);

			int getCardinality ();
				
			bool isInSpecML();

			int getId();
			void setId(int id);
			nau::Enums::DataType getValueType ();
//			SEMANTIC_TYPE getSemanticType();
			int getSemanticValueOf();
			//void setSemanticType(SEMANTIC_TYPE s);
			void setSemanticValueOf(int s);
			void setValueType(nau::Enums::DataType s);
				
			void setValueOfUniform(void *values);
			//void setValueOfUniform(int *values);
			//void setValueOfUniform (float *values);
			void* getValues ();

			void setLoc(int l);
			int getLoc();

		};
	};
};
#endif //PROGRAMVALUE_H