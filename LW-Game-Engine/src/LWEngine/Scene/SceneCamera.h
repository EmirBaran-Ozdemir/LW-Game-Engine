#pragma once

#include "LWEngine/Renderer/Camera.h"

namespace LWEngine {

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType {
			Perspective = 0,
			Orthographic = 1
		};
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographicCamera(float size, float nearClip, float farClip);
		void SetPerspectiveCamera(float FOV, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		//. Perspective
		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float verticalFOV) { m_PerspectiveFOV = verticalFOV; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farCliip) { m_PerspectiveFar = farCliip;  RecalculateProjection(); }
		
		//. Orthographic
		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; RecalculateProjection(); }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }
		void SetOrthographicFarClip(float farCliip) { m_OrthographicFar = farCliip;  RecalculateProjection(); }



		ProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(int typeId) { m_ProjectionType = (ProjectionType)typeId; RecalculateProjection(); }
	//private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Perspective;
		
		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 1.0f;
	};
}