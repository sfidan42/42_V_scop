#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 transform;

void	main()
{
	gl_Position = transform * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}


#shader fragment
#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void	main()
{
	FragColor = mix(texture(texture1, TexCoord),
					texture(texture2, TexCoord), mixValue);
}
