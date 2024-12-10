#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera {
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int width, height;
		float speed = 0.4f;
		float sensitivity = 1.0f;

		Camera(int width, int height, glm::vec3 position);

		bool firstClick = true;

		void Input(GLFWwindow* window, float deltaTime);
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char *uniform);

};

#endif // !CAMERA_H