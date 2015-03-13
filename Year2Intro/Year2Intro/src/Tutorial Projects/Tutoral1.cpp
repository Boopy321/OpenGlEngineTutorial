#include "gl_core_4_4.h"
#include "Tutoral1.h"
#include "GLFW\glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>


using glm::vec3;
using glm::vec4;
using glm::mat4;

Tutoral1::Tutoral1(Renderer* a_render)
{
	//Sets the Position of the planets
	sun.SetLocalPosition(glm::vec3(0, 0, 0));
	//Mercury
	mercury.SetParent(&sun);
	mercury.SetLocalPosition(glm::vec3(1, 0, 1));
	//Venus
	venus.SetParent(&sun);
	venus.SetLocalPosition(glm::vec3(2, 0, -2));
	//Earth
	earth.SetParent(&sun);
	earth.SetLocalPosition(glm::vec3(3, 0, 0));
	//Earth Moon
	e_moon.SetParent(&earth);
	e_moon.SetLocalPosition(glm::vec3(1.f, 0, 0));
	e_moon.setSize(0.1f);

	//Get the renderer
	m_render = a_render;
}

void Tutoral1::GameLoop()
{
	sun.Update();
	mercury.Update();
	venus.Update();
	e_moon.Update();
	earth.Update();
}

Tutoral1::~Tutoral1()
{
}

void Tutoral1::Draw()
{
	Gizmos::clear();

	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	//Creates the grid
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	};

	//Draws the Planets here.
	sun.Render();
	mercury.Render();
	venus.Render();
	earth.Render();
	e_moon.Render();
}
