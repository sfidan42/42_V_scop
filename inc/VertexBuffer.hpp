#ifndef __VERTEX_BUFFER__
# define __VERTEX_BUFFER__

class VertexBuffer
{
private:
	unsigned int	m_RendererID;
public:
	VertexBuffer(const void *data, unsigned int size);
	~VertexBuffer(void);
	void bind(void) const;
	void unbind(void) const;
};

#endif