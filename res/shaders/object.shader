#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform	mat4	model;
uniform	mat4	view;
uniform	mat4	projection;
out		vec3	Color;

void	main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Color = aColor;
}

#shader fragment
#version 460 core

in		vec3	Color;
out		vec4	FragColor;

void    main()
{
    FragColor = vec4(Color, 1.0);
}
