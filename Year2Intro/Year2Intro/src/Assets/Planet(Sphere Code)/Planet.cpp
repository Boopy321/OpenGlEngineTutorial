#include "Planet.h"

#include "Gizmos.h"

void Planet::Update()
{
	m_fRotAngle += 0.01f;
	//Gets the current Rotation matrix from the 
	glm::mat4 rotMatrix = GetRotationMatrix();

	// Alters the XYZ positions in the matrix. in which direction that it should be going


	//Adjusts ROW 0 which is X value
	m_localTransform[0] = rotMatrix[0];
	//Adjust ROW 1 which is Y Value
	m_localTransform[1] = rotMatrix[1];
	//Adjusts ROW 2 which is Z Value
	m_localTransform[2] = rotMatrix[2];

}

void Planet::Render()
{
	
	glm::mat4 rot = GetRotationMatrix();
	//Draws the Sphere based of the world position 
	Gizmos::addSphere(GetWorldTransform()[3].xyz(),m_size, 10, 10, glm::vec4(1, .75f, 0, 1), &rot);
}
//RECURSIVE FUNCTION
glm::mat4 Planet::GetWorldTransform()
{
	//Gets the world Transform location
	glm::mat4 trans;
	//If it has a parent it calls the this again.
	if (m_pParent)
	{
		// Adds the Local Transform to the world transform
		trans = m_pParent->GetWorldTransform() * m_localTransform;
	}
	else
	{
		//Has no parents is the world Transform
		trans = m_localTransform;
	}

	return trans;
}

