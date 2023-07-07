#pragma once

#include "LWEngine/Renderer/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

namespace LWEngine {
	
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D> GetTexture() { return m_Texture; }
		const glm::vec2* GetTextCoords() { return m_TexCoords; }
		
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture,const glm::vec2 coords, const glm::vec2 spriteSize, float offset = 0);
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TexCoords[4];
	};
}