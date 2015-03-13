#ifndef _PLANET_H_
#define _PLANET_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Planet
{
public:
	//Constructor
	Planet() 
	{
		m_fRotAngle = 0;
		m_pParent = nullptr;
		m_localTransform = glm::mat4(1);
		m_size = 0.5f;
	}
	~Planet() {};
	//Sets the parent
	void SetParent(Planet* parent) { m_pParent = parent; }

	void Update();
	//Draws the Planet
	void Render();
	//Set the local posistion matrix of the object
	void SetLocalPosition(glm::vec3 position) { m_localTransform[3] = glm::vec4(position, 1); }
	//Gets the planets local position 
	glm::vec3 GetLocalPosition() { return m_localTransform[3].xyz(); }
	//Gets the current rotation, Based of x Value and Then vec3 to finish
	glm::mat4 GetRotationMatrix() { return glm::rotate(m_fRotAngle, glm::vec3(0,1, 0)); }

	glm::mat4 GetWorldTransform();
	//Gives flexability on size
	void setSize(float value){m_size = value;}
	

private:
	//Local value to contain rotation
	float m_fRotAngle;
	//Planets local transform Matrix data
	glm::mat4 m_localTransform;
	//Just a parent value.
	Planet* m_pParent;
	//Size for the moon values
	float m_size;
};

#endif