#include "nau/scene/sceneobjectfactory.h"

#include "nau/scene/sceneobject.h"
#include "nau/scene/octreenode.h"
#include "nau/scene/geometryobject.h"
#include "nau.h"

using namespace nau::scene;

SceneObject* 
SceneObjectFactory::create (std::string type)
{
	SceneObject *s;
	if (0 == type.compare ("SimpleObject")) {
		s = new SceneObject;
	} 

	else if (0 == type.compare ("OctreeNode")) {
		s =  new OctreeNode;
	}

	else if (0 == type.compare ("Geometry")) {
		s =  new GeometricObject;
	}
	else {
		assert("SceneObjectFactory: type is not valid");
		return 0;
	}

	RENDERMANAGER->addSceneObject(s);
	return s;
}
