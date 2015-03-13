#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void BindTexture();
	void SetUpFrameBuffers();
	void GenFrameBuffers();
	void GenBuffers(); 
protected:
	unsigned int m_fbo;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_fboDepth;
	unsigned int m_fboTexture;
	

};

