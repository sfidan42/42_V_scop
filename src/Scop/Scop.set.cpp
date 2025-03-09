#include <Scop.hpp>

void	Scop::setMVP(void)
{
	shader.setMat4fv("model", glm2::value_ptr(model));
	shader.setMat4fv("view", glm2::value_ptr(view));
	shader.setMat4fv("projection", glm2::value_ptr(projection));
}

void	Scop::setLightPos(glm::vec3 lightPos)
{
	shader.set3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
}

void	Scop::setMaterial(tMaterial mat)
{
	shader.set3f("ambientColor", mat.ka.r, mat.ka.g, mat.ka.b);
	shader.set3f("diffuseColor", mat.kd.r, mat.kd.g, mat.kd.b);
	shader.set3f("specularColor", mat.ks.r, mat.ks.g, mat.ks.b);
}

void	Scop::setSpeedCoeff(float val)
{
	speedCoeff = val;
}
