#ifndef OBJECTANIMATION_H
#define OBJECTANIMATION_H

#include "nau/event/ilistener.h"
#include "nau/event/iEventData.h"
#include "nau/math/vec3.h"
#include "nau/scene/sceneobject.h"

using namespace nau::scene;

namespace nau
{
	namespace event_
	{
		class ObjectAnimation: public IListener
		{
		public:
			std::string name;
			SceneObject *object;

			ObjectAnimation(std::string name, SceneObject *object);
			ObjectAnimation(const ObjectAnimation &c);
			ObjectAnimation(void);
			~ObjectAnimation(void);

			std::string &getName(void);
			void removeAnimationListener(void);
			void addAnimationListener(void);
			SceneObject *getObject(void);		
			void eventReceived(const std::string &sender, const std::string &eventType, nau::event_::IEventData *evt);
			//void init(std::string name, ISceneObject *o);
		};
	};
};

#endif
