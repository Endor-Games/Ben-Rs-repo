#include "CustomLayer.h"

void CustomLayer::OnLoad()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = Shader::FromFile(
		"assets/shaders/shader.vert",
		"assets/shaders/shader.frag"
	);

	glCreateVertexArrays(1, &m_quadVA);
	glBindVertexArray(m_quadVA);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	glCreateBuffers(1, &m_quadVB);
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	glCreateBuffers(1, &m_quadIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CustomLayer::OnExit()
{
	glDeleteVertexArrays(1, &m_quadVA);
	glDeleteBuffers(1, &m_quadVB);
	glDeleteBuffers(1, &m_quadIB);
}

void CustomLayer::OnEvent(Event& event)
{
	m_cameraController.OnEvent(event);
}

void CustomLayer::OnUpdate(const Timestep timeStep)
{
	m_cameraController.OnUpdate(timeStep);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_shader->GetRendererID());

	int location = glGetUniformLocation(m_shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_cameraController.GetCamera().GetViewProjectionMatrix()));

	location = glGetUniformLocation(m_shader->GetRendererID(), "u_Color");
	glUniform4fv(location, 1, glm::value_ptr(m_color));

	glBindVertexArray(m_quadVA);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void CustomLayer::OnGuiDraw()
{
	ImGui::Begin("Controls");

	ImGui::ShowDemoWindow();
	
	if (ImGui::ColorEdit4("Color", glm::value_ptr(m_defaultColor)))
		m_color = m_defaultColor;
	
	ImGui::End();
}
