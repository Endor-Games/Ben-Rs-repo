#include "pch.h"
#include "Shader.h"

namespace Engine::Graphics {
	static std::string ReadFileAsString(const std::string& filepath)
	{
		std::string result;
		std::ifstream input(filepath, std::ios::in | std::ios::binary);

		if (!input)
			LOG_ERROR("Could not open file '{0}'", filepath);

		input.seekg(0, std::ios::end);
		result.resize(static_cast<size_t>(input.tellg()));
		input.seekg(0, std::ios::beg);
		input.read(&result[0], result.size());
		input.close();

		return result;
	}

	Shader* Shader::FromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		Shader* pShader = new Shader();
		pShader->LoadFromFile(vertexShaderPath, fragmentShaderPath);
		return pShader;
	}

	void Shader::LoadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		// Load vertex/fragment shaders from file
		std::string vertexSource = ReadFileAsString(vertexShaderPath);
		std::string fragmentSource = ReadFileAsString(fragmentShaderPath);

		// Create a new shader program instance
		const GLuint program = glCreateProgram();

		// Compile vertex shader
		const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);

		// Compile fragment shader
		const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		glAttachShader(program, fragmentShader);

		// Link the shader
		glLinkProgram(program);

		// Check the shader is linked
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LOG_ERROR("{0}", infoLog.data());
		}

		// Cleanup shaders
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_id = program;
	}

	GLuint Shader::CompileShader(const GLenum type, const std::string& source)
	{
		const GLuint shader = glCreateShader(type);

		const GLchar* pSourceCStr = source.c_str();
		glShaderSource(shader, 1, &pSourceCStr, nullptr);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			LOG_ERROR("{0}", infoLog.data());
		}

		return shader;
	}
}
