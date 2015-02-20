#include "nau/scene/iscene.h"

#include "nau.h"
#include "nau/math/simpletransform.h"

using namespace nau::math;
using namespace nau::scene;

bool 
IScene::Init() {

	// VEC4
	Attribs.add(Attribute(SCALE, "SCALE", Enums::DataType::VEC4, false, new vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	Attribs.add(Attribute(TRANSLATE, "TRANSLATE", Enums::DataType::VEC4, false, new vec4(0.0f, 0.0f, 0.0f, 0.0f)));
	Attribs.add(Attribute(ROTATE, "ROTATE", Enums::DataType::VEC4, false, new vec4(0.0f, 1.0f, 0.0f, 0.0f)));

	// VEC3
	Attribs.add(Attribute(BB_MAX, "BB_MAX", Enums::DataType::VEC3, true, new vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	Attribs.add(Attribute(BB_MIN, "BB_MIN", Enums::DataType::VEC3, true, new vec4(1.0f, 1.0f, 1.0f, 1.0f)));

	// ENUM
	Attribs.add(Attribute(TRANSFORM_ORDER, "TRANSFORM_ORDER", Enums::ENUM, false, new int(T_R_S)));
	Attribs.listAdd("TRANSFORM_ORDER", "T_R_S", T_R_S);
	Attribs.listAdd("TRANSFORM_ORDER", "T_S_R", T_S_R);
	Attribs.listAdd("TRANSFORM_ORDER", "R_T_S", R_T_S);
	Attribs.listAdd("TRANSFORM_ORDER", "R_S_T", R_S_T);
	Attribs.listAdd("TRANSFORM_ORDER", "S_R_T", S_R_T);
	Attribs.listAdd("TRANSFORM_ORDER", "S_T_R", S_T_R);

	NAU->registerAttributes("SCENE", &Attribs);

	return true;
}

AttribSet IScene::Attribs;
bool IScene::Inited = Init();


void 
IScene::updateTransform() {

	ITransform *tis = TransformFactory::create("SimpleTransform");

	switch (m_EnumProps[TRANSFORM_ORDER]) {

	case T_R_S:
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		break;
	case T_S_R:
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		break;
	case R_T_S:
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		break;
	case R_S_T:
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		break;
	case S_R_T:
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		break;
	case S_T_R:
		tis->scale(m_Float4Props[SCALE].x, m_Float4Props[SCALE].y, m_Float4Props[SCALE].z);
		tis->translate(m_Float4Props[TRANSLATE].x, m_Float4Props[TRANSLATE].y, m_Float4Props[TRANSLATE].z);
		tis->rotate(m_Float4Props[ROTATE].w, m_Float4Props[ROTATE].x, m_Float4Props[ROTATE].y, m_Float4Props[ROTATE].z);
		break;
	}
	setTransform(tis);

}


void
IScene::setPropf4(Float4Property prop, vec4& aVec) {

	switch (prop) {
	case SCALE:
	case ROTATE:
	case TRANSLATE:
		m_Float4Props[prop] = aVec;
		updateTransform();
		break;
	default:
		AttributeValues::setPropf4(prop, aVec);
	}

}


void 
IScene::setPrope(EnumProperty prop, int v) {

	switch (prop) {
	case TRANSFORM_ORDER:
		m_EnumProps[prop] = v;
		updateTransform();
		break;
	default:
		AttributeValues::setPrope(prop, v);
	}
}


void *
IScene::getProp(unsigned int prop, Enums::DataType type) {

	if (type == Enums::VEC3) {

		switch (prop) {
		case BB_MIN: m_Float3Props[BB_MIN] = getBoundingVolume().getMin();
			return &m_Float3Props[BB_MIN];
		case BB_MAX: m_Float3Props[BB_MAX] = getBoundingVolume().getMax();
			return &m_Float3Props[BB_MAX];
		default: return AttributeValues::getProp(prop, type);
		}
	}
	else
		return AttributeValues::getProp(prop, type);
}


vec3 &
IScene::getPropf3(Float3Property prop) {

	switch (prop) {
	case BB_MIN: m_Float3Props[BB_MIN] = getBoundingVolume().getMin();
		return m_Float3Props[BB_MIN];
	case BB_MAX: m_Float3Props[BB_MAX] = getBoundingVolume().getMax();
		return m_Float3Props[BB_MAX];
	default: return AttributeValues::getPropf3(prop);
	}
}