#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform	mat4	model;
uniform	mat4	view;
uniform	mat4	projection;
out		vec3	FragPos;
out		vec3	Normal;
out		vec3	Color;

void	main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = -FragPos;
	Color = aColor;
}

#shader fragment
#version 460 core

in		vec3	Color;
in		vec3	Normal;
in		vec3	FragPos;
uniform	vec3	lightColor;
uniform	vec3	lightPos;
uniform vec3    viewPos;
out		vec4	FragColor;

void    main()
{
	vec3	ambient = vec3(0.1, 0.1, 0.1);
	vec3	norm = normalize(Normal);
	vec3	lightDir = normalize(lightPos - FragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = diff * lightColor;
	float   specularStrength = 0.5;
    vec3    viewDir = normalize(viewPos - FragPos);
    vec3    reflectDir = reflect(-lightDir, norm);
    float   spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3    specular = specularStrength * spec * lightColor;
	vec3    result = (ambient + diffuse + specular) * Color;
    FragColor = vec4(result, 1.0);
}
