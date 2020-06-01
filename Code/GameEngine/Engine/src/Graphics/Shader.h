#pragma once

#include <fstream>
#include <glad/glad.h>

namespace Engine::Graphics {
	class Shader
	{
	public:
		~Shader() { glDeleteProgram(m_id); };

		// Get the renderer ID of the shader instance
		GLuint GetRendererID() const { return m_id; }

		// Load a new shader from both vertex & fragment files
		static Shader* FromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	private:
		Shader() = default;

		// Load a shader from a specified file
		void LoadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		// Compile a shader from raw shader string
		GLuint CompileShader(GLenum type, const std::string& source);

		// Shader instance id
		GLuint m_id;
	};
}
