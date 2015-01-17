#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <nau/attribute.h>
#include <nau/attributeValues.h>
#include <nau/event/ilistener.h>
#include <nau/geometry/iboundingvolume.h>
#include <nau/math/itransform.h>
#include <nau/render/irenderable.h>
#include <nau/scene/sceneobjectfactory.h>

#include <string>

namespace nau
{
	namespace scene
	{
		class SceneObject : public AttributeValues, public nau::event_::IListener
		{
		public:
			friend class nau::scene::SceneObjectFactory;

			FLOAT4_PROP(SCALE, 0);
			FLOAT4_PROP(ROTATE, 1);
			FLOAT4_PROP(TRANSLATE, 2);

			static AttribSet Attribs;

			virtual void setPropf4(Float4Property prop, vec4& aVec);

			static void ResetCounter();
			static unsigned int Counter;

			virtual std::string getType (void);

			virtual int getId ();
			virtual void setId (int id);

			virtual std::string& getName ();
			virtual void setName (const std::string &name);

			virtual void unitize(float min, float max);

			virtual bool isStatic();
			virtual void setStaticCondition(bool aCondition);

			virtual const nau::geometry::IBoundingVolume* getBoundingVolume();
			virtual void setBoundingVolume (nau::geometry::IBoundingVolume *b);

			virtual const nau::math::ITransform& getTransform();
			virtual void transform(nau::math::ITransform *t);
			virtual void setTransform (nau::math::ITransform *t);
			virtual void burnTransform (void);
			virtual nau::math::ITransform *_getTransformPtr (void);
			virtual void updateGlobalTransform(nau::math::ITransform *m_Transform);
			
			virtual nau::render::IRenderable& getRenderable (void);
			virtual nau::render::IRenderable* _getRenderablePtr (void);
			virtual void setRenderable (nau::render::IRenderable *renderable);

			virtual void writeSpecificData (std::fstream &f);
			virtual void readSpecificData (std::fstream &f);

			void prepareTriangleIDs(bool ids);

			virtual ~SceneObject(void);


		protected:

			static bool Init();
			static bool Inited;

			SceneObject (void);
			int m_Id;
			std::string m_Name;
			bool m_StaticCondition;
			nau::render::IRenderable *m_Renderable;
			nau::geometry::IBoundingVolume *m_BoundingVolume;
			nau::math::ITransform *m_Transform, *m_GlobalTransform, *m_ResultTransform;

			void calculateBoundingVolume (void);
		};
	};
};

#endif // SCENEOBJECT_H
