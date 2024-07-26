#include <scop.hpp>

void	setVertexArray(void)
{
	unsigned int		buffer_id;
	const unsigned int	size = 12;
	const unsigned int	vertexSize = 3;
	float				data[size] = {
		 .5, -.1, -.2,
		 .1,  .5,  .1,
		-.5,  .0, -.3,
		  0, -.5,  .0,
	};

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), 0);

}

unsigned int	setVertexIndexArray(void)
{
	unsigned int		ibo;
	const unsigned int	indexSize = 6;
	unsigned int 		indices[indexSize] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	return indexSize;
}