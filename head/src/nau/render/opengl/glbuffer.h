#include <nau/config.h>



#ifndef GLBUFFER_H
#define GLBUFFER_H

#include <string>
#include <math.h>

#include <nau/attribute.h>
#include <nau/attributeValues.h>

#include <nau/config.h>
#include <nau/render/ibuffer.h>

using namespace nau;


namespace nau
{
	namespace render
	{
		class GLBuffer : public IBuffer
		{
		public:

			GLBuffer(std::string label);
			~GLBuffer(void) ;

			void bind(unsigned int target);
			void unbind();
			void setProp(int prop, Enums::DataType type, void *value);
			void setData(unsigned int size, void *data);
			void getData(unsigned int offset, unsigned int size, void *data);
#if NAU_OPENGL_VERSION >= 430
			void clear();
#endif
			IBuffer * clone();

		protected:
			static bool Init();
			static bool Inited;

			GLBuffer() {};

			int m_LastBound;

		};
	};
};



#endif // GLBUFFER_H