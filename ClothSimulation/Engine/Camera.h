#pragma once

// Local Include
#include "Utility.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void UpdateCamera();

	glm::mat4 GetView() const;
	void CalcViewMatrix();
	glm::mat4 GetProj() const;
	void CalcProjectionMatrix();

public:

	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraFacing;
	glm::vec3 m_cameraNormal;

	float m_viewPortWidth;
	float m_viewPortHeight;

	float m_nearPlane;
	float m_farPlane;
	float m_fov;

	ECAMERATYPE m_cameraType;

private:

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};