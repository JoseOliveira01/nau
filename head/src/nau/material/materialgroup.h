#ifndef MATERIALGROUP_H
#define MATERIALGROUP_H

#include <nau/render/indexdata.h>
#include <nau/render/irenderable.h>

#include <string>

namespace nau
{
	namespace material
	{

		class MaterialGroup 
		{
		public:

			static MaterialGroup *Create(nau::render::IRenderable *parent, std::string materialName);

			const std::string& getMaterialName ();
			void setMaterialName (std::string name);
		   
			unsigned int getNumberOfPrimitives(void);

			nau::render::IndexData& getIndexData (void);
			unsigned int getIndexOffset(void);
			unsigned int getIndexSize(void);

			void setParent (nau::render::IRenderable* parent);
			nau::render::IRenderable& getParent ();

			void updateIndexDataName();

			void setIndexList(std::vector<unsigned int>* indices);

			std::string &getName();

			virtual void compile() = 0;
			virtual bool isCompiled() = 0;
			virtual void resetCompilationFlag() = 0;
			virtual void bind() = 0;
			virtual void unbind() = 0;

			~MaterialGroup();

		protected:
			nau::render::IRenderable* m_Parent;
			std::string m_MaterialName;
			nau::render::IndexData *m_IndexData;
			std::string m_Name;

			MaterialGroup();
			MaterialGroup(nau::render::IRenderable *parent, std::string materialName);
		};

	};
};
#endif // MaterialGroup_H
