#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "RenderTarget.h"
#include <iostream>

RenderTarget::RenderTarget()
{
}


RenderTarget::~RenderTarget()
{
}

void RenderTarget::SetUpFrameBuffers()
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//Attach Render Targets here!


		//Unbind FBO so we can render to the back buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderTarget::BindTexture()
{
	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);

	// specify texture format for storage
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 512);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// attach it to the framebuffer as the first colour attachment
	// the FBO MUST still be bound
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		m_fboTexture, 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
}

void RenderTarget::GenFrameBuffers()
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glGenTextures(1, &m_fboTexture);

	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 512, 512);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		m_fboTexture, 0);

	glGenRenderbuffers(1, &m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
		512, 512);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, m_fboDepth);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer Error!\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void RenderTarget::GenBuffers()
{
	float vertexData[] = {
		-5, 0, -5, 1, 0, 0,
		5, 0, -5, 1, 1, 0,
		5, 10, -5, 1, 1, 1,
		-5, 10, -5, 1, 0, 1,
	};
	unsigned int indexData[] = {
		0, 1, 2,
		0, 2, 3,
	};
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 6 * 4,
		vertexData, GL_STATIC_DRAW);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* 6,
		indexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, 0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, ((char*)0) + 16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}