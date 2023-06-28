#include "lwpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderCommand.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace LWEngine {

	struct Renderer2DStorage
	{
		Ref<LWEngine::Shader> quadShader;
		Ref<LWEngine::VertexArray> quadVA;
		Ref<LWEngine::Texture2D> quadTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
	
		s_Data->quadVA = LWEngine::VertexArray::Create();
		float squareVertices[3 * 4] = {
			-0.2f,	-0.2f,	0.0f,
			 0.2f,	-0.2f,	0.0f,
			 0.2f,	 0.2f,	0.0f,
			-0.2f,	 0.2f,	0.0f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> squareVB;
		squareVB.reset(LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		LWEngine::BufferLayout squareLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
		};
		squareVB->SetLayout(squareLayout);
		s_Data->quadVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		Ref<LWEngine::IndexBuffer> squareIB;
		squareIB.reset((LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		s_Data->quadVA->SetIndexBuffer(squareIB);
		s_Data->quadShader = Shader::Create("assets/shaders/SquareShader.glsl");
	}
	
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->quadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->quadShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->quadShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));

	}
	
	void Renderer2D::EndScene()
	{
	
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->quadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->quadShader)->UploadUniformFloat4("u_Color", color);


		s_Data->quadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVA);
	}
}