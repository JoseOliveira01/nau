#include "nau/render/imageTexture.h"

#if NAU_OPENGL_VERSION >= 420


#ifdef NAU_OPENGL
#include "nau/render/opengl/glimagetexture.h"
#endif

#include "nau.h"

using namespace nau::render;
using namespace nau;


bool
ImageTexture::Init() {

	// UINT
	Attribs.add(Attribute(TEX_ID, "TEX_ID", Enums::DataType::UINT, false, new int(0)));
	Attribs.add(Attribute(LEVEL, "LEVEL", Enums::DataType::UINT, false, new int(0)));
	// ENUM
	Attribs.add(Attribute(ACCESS, "ACCESS", Enums::DataType::ENUM, false));
	// BOOL
	Attribs.add(Attribute(CLEAR, "CLEAR", Enums::DataType::BOOL, false, new bool(false)));
	// INT
	Attribs.add(Attribute(UNIT, "UNIT", Enums::DataType::INT, true, new int(-1)));

	NAU->registerAttributes("IMAGE_TEXTURE", &Attribs);

	return true;
}


AttribSet ImageTexture::Attribs;
bool ImageTexture::Inited = Init();




ImageTexture*
ImageTexture::Create(std::string label, unsigned int unit, unsigned int texID, unsigned int level, unsigned int access) {

#ifdef NAU_OPENGL
	return new GLImageTexture (label, unit, texID, level, access);
#elif NAU_DIRECTX
	//Meter fun��o para DirectX
#endif
}


ImageTexture*
ImageTexture::Create(std::string label, unsigned int unit, unsigned int texID) {

#ifdef NAU_OPENGL
	return new GLImageTexture (label, unit, texID);
#elif NAU_DIRECTX
	//Meter fun��o para DirectX
#endif
}


ImageTexture::ImageTexture() {

	registerAndInitArrays(Attribs);
}


std::string&
ImageTexture::getLabel (void) {

	return m_Label;
}


void
ImageTexture::setLabel (std::string label) {

	m_Label = label;
}


#endif