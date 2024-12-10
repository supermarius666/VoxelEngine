#include"camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection *view));
}

void Camera::Input(GLFWwindow* window, float deltaTime) {
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}

	//mouse input
	double mouseX, mouseY;
	static float yaw = -90.0f;  // Angolo di rotazione attorno all'asse Y (inizialmente puntato verso -Z)
	static float pitch = 0.0f;  // Angolo di rotazione attorno all'asse X
	const float pitchLimit = 89.0f; // Limite massimo di pitch per evitare capovolgimenti

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (firstClick) {
			glfwSetCursorPos(window, width / 2, height / 2);
			firstClick = false;
		}

		// Ottieni la posizione corrente del mouse
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Calcola le differenze di movimento del mouse
		float offsetX = sensitivity * (float)(mouseX - width / 2);
		float offsetY = sensitivity * (float)(mouseY - height / 2);

		// Aggiorna yaw e pitch basandoti sui movimenti del mouse
		yaw += offsetX;
		pitch -= offsetY; // Inverti l'asse Y perché il movimento del mouse è invertito per la pitch

		// Limita il pitch per evitare capovolgimenti (gimbal lock)
		if (pitch > pitchLimit) pitch = pitchLimit;
		if (pitch < -pitchLimit) pitch = -pitchLimit;

		// Calcola il nuovo vettore di orientamento usando yaw e pitch
		Orientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		Orientation.y = sin(glm::radians(pitch));
		Orientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		Orientation = glm::normalize(Orientation);

		// Reimposta il mouse al centro della finestra
		glfwSetCursorPos(window, width / 2, height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

}