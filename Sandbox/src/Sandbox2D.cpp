#include "Sandbox2D.h"
#include <Platform/OpenGL/OpenGLShader.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)1280 / 720)
{

}

void Sandbox2D::OnAttach()
{


}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(LWEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
	LWEngine::RenderCommand::Clear();


	LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	LWEngine::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, m_SquareColor);
	LWEngine::Renderer2D::EndScene();

	//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->Bind();
	//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender(LWEngine::Timestep ts)
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}