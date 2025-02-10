#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform	mat4	model;
uniform	mat4	view;
uniform	mat4	projection;
out		vec3	FragPos;
out		vec3	Normal;

void	main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
}

#shader fragment
#version 460 core

out		vec4	FragColor;
uniform	vec3	objectColor;
uniform	vec3	lightColor;
uniform	vec3	lightPos;
in		vec3	Normal;
in		vec3	FragPos;

void    main()
{
	vec3	ambient = vec3(0.1, 0.1, 0.1);
	vec3	norm = normalize(Normal);
	vec3	lightDir = normalize(lightPos - FragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = diff * lightColor;
	vec3	result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}
