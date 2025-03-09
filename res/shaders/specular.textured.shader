#shader glm::vec3
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform	mat4	model;
uniform	mat4	view;
uniform	mat4	projection;
out		vec3	FragPos;
out		vec3	Normal;
out		vec2	TexCoord;

void	main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoord = aTexCoord;
}

#shader fragment
#version 460 core

in		vec3		Normal;
in		vec3		FragPos;
in		vec2		TexCoord;
uniform	vec3		ambientColor;
uniform	vec3		diffuseColor;
uniform	vec3		specularColor;
uniform	vec3		lightPos;
uniform	vec3		viewPos;
out		vec4		FragColor;
uniform	sampler2D	theTexture;

void main()
{
    // Sample the texture
    vec3 texColor = texture(theTexture, TexCoord).rgb;

    // Ambient lighting
    vec3 ambient = ambientColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * specularColor;

    // Combine all lighting components
    vec3 result = (ambient + diffuse + specular) * texColor;
    FragColor = vec4(result, 1.0);
}