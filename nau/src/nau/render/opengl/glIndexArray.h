#ifndef GLINDEXARRAY_H
#define GLINDEXARRAY_H

#include "nau/geometry/indexData.h"


using namespace nau::geometry;

namespace nau
{
	namespace render
	{
		class GLIndexArray : public IndexData
		{

			friend class nau::geometry::IndexData;

		protected:
			bool m_IsCompiled;
			//bool compile (VertexData &v);
			void resetCompilationFlag();
			bool isCompiled();
			void bind (void);
			void unbind (void);
			//GLIndexArray(void);
			GLIndexArray(std::string &name);

		public:

			//std::vector<unsigned int>& getIndexData (void);
			void compile();
			void useAdjacency(bool adj);
			bool getAdjacency();

			virtual unsigned int getBufferID();
			virtual void setBuffer(unsigned int id);

			virtual unsigned int getIndexSize(void);

			~GLIndexArray(void);

		};
	};
};

#endif //GLVERTEXARRAY_H
