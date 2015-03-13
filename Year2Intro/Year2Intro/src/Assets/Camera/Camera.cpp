#include "Camera.h"

Camera::Camera() :Camera(mat4(1))
{

}

Camera::Camera(vec3 position) : Camera()
{
	m_worldTransform[3] = vec4(position, 1);
	m_bPerspectiveSet = false;
}

Camera::Camera(mat4 transform) : m_worldTransform(transform)
{
	UpdateProjectionViewTransform();
}

void Camera::SetTransform(mat4 transform)
{
	m_worldTransform = transform;
	UpdateProjectionViewTransform();
}

//Sets the camera postion
void Camera::setPersepective(float FOV, float aspectRatio, float near = 0.1f, float far = 1000.0f)
{
	m_projectionTransform = glm::perspective(FOV, aspectRatio, near, far);
	m_bPerspectiveSet = true;

	UpdateProjectionViewTransform();
}

void Camera::setLookAt(vec3 position, vec3 lookAt, vec3 worldUp)
{
	m_worldTransform = glm::inverse(glm::lookAt(position, lookAt, worldUp));
	UpdateProjectionViewTransform();
}

void Camera::setLookAt(vec3 lookAt, vec3 worldup)
{
	vec4 vLocation = m_worldTransform[3];
	m_worldTransform = glm::inverse(glm::lookAt(vLocation.xyz(), lookAt, worldup));
	UpdateProjectionViewTransform();
}

void Camera::setPosition(vec3 pos)
{
	m_worldTransform[3] = vec4(pos, 1);
	UpdateProjectionViewTransform();
}

void Camera::UpdateProjectionViewTransform()
{
	m_viewTransform = glm::inverse(m_worldTransform);
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}

Camera::~Camera()
{

}
