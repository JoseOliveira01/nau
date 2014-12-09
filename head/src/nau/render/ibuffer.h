#include <nau/config.h>


#ifndef IBUFFER_H
#define IBUFFER_H

#include <string>
#include <math.h>

#include <nau/attribute.h>
#include <nau/attributeValues.h>



using namespace nau;


namespace nau
{
	namespace render
	{
		class IBuffer : public AttributeValues
		{
		public:

			INT_PROP(ID,0);
//			INT_PROP(BINDING_POINT, 1);

			UINT_PROP(SIZE, 0);

//			ENUM_PROP(TYPE, 0);

//			BOOL_PROP(BOUND, 0);
			ENUM_PROP(CLEAR, 0);
			ENUM_PROP(TYPE, 1);

			typedef enum {
				NEVER,
				BY_FRAME
			} ClearValues; 

			static AttribSet Attribs;


			// Note: no validation is performed!
			virtual void setProp(int prop, Enums::DataType type, void *value)  = 0;

			static IBuffer* Create(std::string label);

			std::string& getLabel (void);

			virtual void setData(unsigned int size, void *data) = 0;
			virtual void getData(unsigned int offset, unsigned int size, void *data) = 0;

			virtual void bind(unsigned int type) = 0;
			virtual void unbind() =0;
#if NAU_OPENGL_VERSION >= 430
			virtual void clear() = 0;
#endif 

			virtual IBuffer * clone() = 0;

			// Only useful for GUIs
			void setStructure(std::string &s);
			std::string &getStructure();
		
			~IBuffer(void) {};
		
		protected:

			IBuffer(): m_Label(""), m_Structure("") { initArrays(Attribs); };

			static bool Init();
			static bool Inited;

			std::string m_Label;
			std::string m_Structure;
		};
	};
};



#endif // IBUFFER_H