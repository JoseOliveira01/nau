#ifndef PROFILERPASS_H
#define PROFILERPASS_H

#include "nau/geometry/font.h"
#include "nau/render/pass.h"
#include "nau/render/iRenderable.h"
#include "nau/scene/camera.h"

namespace nau
{
	namespace render
	{
		class PassProfiler :
			public Pass
		{
		protected:
			nau::geometry::Font m_pFont;
			nau::scene::Camera *m_pCam;
			nau::scene::SceneObject *m_pSO;

			static bool Init();
			static bool Inited;

		public:
			PassProfiler (const std::string &name);
			virtual ~PassProfiler(void);

			static Pass *Create(const std::string &name);

			void prepare (void);
			void restore (void);
			void doPass (void);
			virtual void setCamera (const std::string &cameraName);
			

		};
	};
};
#endif 