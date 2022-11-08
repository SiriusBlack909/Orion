#pragma once
#include"../LightSource.h"

namespace Orion
{
	class SpotLight : public LightSource
	{
	public:
		SpotLight() 
		{
			FramebufferSpecification fb;
			fb.OnlyDepthPass = true;
			fb.CubemapBuffer = true;
			fb.Width =  512;
			fb.Height = 512;

			m_ShadowMap = Framebuffer::Create(fb);
		};
		SpotLight(Shared<Model>& model, uint32_t shadowWidth = 512, uint32_t shadowHeight = 512) : LightSource(model)
		{
			FramebufferSpecification fb;
			fb.OnlyDepthPass = true;
			fb.CubemapBuffer = true;
			fb.Width = shadowWidth;
			fb.Height = shadowHeight;

			m_ShadowMap = Framebuffer::Create(fb);
		}
		

		virtual void SetupLight(Shared<Shader>& currentShader, std::vector<Shared<LightSource>>& otherLights, std::function<void()> renderFunc) override;
		virtual void LoadToLightShader() override;
		virtual void RenderLightModel(Shared<Shader>& shader) override;


		inline float& GetInnerCutOff() { return m_InnerCutOff; }
		inline float& GetOuterCutOff() { return m_OuterCutOff; }

	private: 
		float m_InnerCutOff = 0.5f, m_OuterCutOff = 5.f;
	};
}
