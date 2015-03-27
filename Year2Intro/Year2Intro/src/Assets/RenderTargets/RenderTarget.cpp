#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "RenderTarget.h"
#include <iostream>

RenderTarget::RenderTarget(int a_height,int a_width)
{
	// Create fbo, texture and depth buffer here
	m_height = a_height;
	m_width = a_width;

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, m_width, m_height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		m_fboTexture, 0);

	glGenRenderbuffers(1, &m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
		m_width, m_height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, m_fboDepth);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer Error!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//Another Constructor End value is useless, Making it possible to dif between the two
RenderTarget::RenderTarget(int a_height, int a_width, int shadowmap )
{
	// Create fbo, texture and depth buffer here
	m_height = a_height;
	m_width = a_width;
	// setup shadow map buffer
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_fboDepth);
	glBindTexture(GL_TEXTURE_2D, m_fboDepth);
	// texture uses a 16-bit depth component format

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, a_width, a_height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE);

	// attached as a depth attachment to capture depth not colour
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		m_fboDepth, 0);
	// no colour targets are used
	glDrawBuffer(GL_NONE);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer Error!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
RenderTarget::~RenderTarget()
{
	glDeleteBuffers(1,&m_fbo);
	glDeleteBuffers(1,&m_fboDepth);
	glDeleteBuffers(1,&m_fboTexture);
	
}

void RenderTarget::BindTarget()
{
	// Binds your render target
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, m_width, m_height);
}

void RenderTarget::BindBackBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::BindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fboDepth);
}

//Creates the mesh for the target to be drawn to.

