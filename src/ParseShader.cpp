#include <main.h>

/*
* Given a file path, this function will read the file and parse it to a string.
* The string will be split into two parts: vertex shader and fragment shader.
*/
ShaderProgramSource	ParseShader(const std::string &filepath)
{
	std::ifstream		file(filepath);
	std::string			line;
	std::stringstream	ss[2];
	enum class			ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType			type;
	
	type = ShaderType::NONE;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}
	return {ss[0].str(), ss[1].str()};
}
