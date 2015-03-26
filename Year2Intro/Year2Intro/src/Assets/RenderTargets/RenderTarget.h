#pragma once
class RenderTarget
{
public:
	RenderTarget(int a_height, int a_width);
	RenderTarget(int a_height, int a_width, int shadowmap);
	~RenderTarget();
	void BindTarget();
	void GenFrameBuffers();
	static void BindBackBuffer();
	void BindTexture();

protected:
	unsigned int m_fbo;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_fboDepth;
	unsigned int m_fboTexture;
	int m_height;
	int m_width;
	
};

