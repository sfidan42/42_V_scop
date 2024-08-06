#ifndef __INDEX_BUFFER__
# define __INDEX_BUFFER__

class IndexBuffer
{
private:
	unsigned int	m_RendererID;
	unsigned int	m_Count;
public:
	IndexBuffer(const unsigned int *data, unsigned int count);
	~IndexBuffer(void);
	void bind(void) const;
	void unbind(void) const;
	inline unsigned int getCount(void) const { return m_Count; }
};

#endif