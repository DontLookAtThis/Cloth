
// This Include
#include "Camera.h"

CCamera::CCamera()
{
	m_cameraPosition = { 0.0f, 0.0f, 3.0f };
	m_cameraFacing = { 0.0f, 0.0f, -1.0f };
	m_cameraNormal = { 0.0f, 1.0f, 0.0f };
	m_viewPortWidth = (float)util::SCR_WIDTH;
	m_viewPortHeight = (float)util::SCR_HEIGHT;
	m_nearPlane = 0.1f;
	m_farPlane = 3000.0f;
	m_fov = 60.0f;
	m_cameraType = ECAMERATYPE::PERSPECTIVE;
}

CCamera::~CCamera()
{}

void CCamera::UpdateCamera()
{
	CalcViewMatrix();
	CalcProjectionMatrix();
}

glm::mat4 CCamera::GetView() const
{
	return m_viewMatrix;
}

void CCamera::CalcViewMatrix()
{
	m_viewMatrix = glm::lookAt(
		m_cameraPosition * (float)util::PIXELUNIT, 
		m_cameraPosition * (float)util::PIXELUNIT + m_cameraFacing,
		m_cameraNormal);
}

glm::mat4 CCamera::GetProj() const
{
	return m_projectionMatrix;
}
void CCamera::CalcProjectionMatrix()
{
	if (m_cameraType == ORTHOGRAPHIC)
	{
		m_projectionMatrix = glm::ortho(-(m_viewPortWidth / 2.0f), (m_viewPortWidth / 2.0f),
			-(m_viewPortHeight / 2.0f), (m_viewPortHeight / 2.0f), m_nearPlane, m_farPlane);
	}
	else
	{
		m_projectionMatrix = glm::perspective(
			m_fov, m_viewPortWidth / m_viewPortHeight, m_nearPlane, m_farPlane);
	}
}