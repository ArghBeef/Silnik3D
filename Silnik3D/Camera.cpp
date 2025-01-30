#include "Camera.h"


Camera::Camera(glm::vec3 position) {
	Position = position;
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Front = glm::vec3(0.0f, 0.0f, -3.0f);
	Click = true;
}

void Camera::handleInputs(GLFWwindow* window) {

	//do klawiatury
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Front, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Front, Up));
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// Ukrywa kursor myszy
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Zapobiega skakaniu kamery
			if (Click)
			{
				glfwSetCursorPos(window, (800 / 2), (800 / 2));
				Click = false;
			}

			// Przechowuje wspolrzedne kursora
			double mouseX;
			double mouseY;
			// Pobiera wspolrzedne kursora
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizuje i przesuwa wspolrzedne kursora tak, aby zaczynaly sie na srodku ekranu,
			// a nastepnie "transformuje" je na stopnie
			float rotX = sensitivity * (float)(mouseY - (800 / 2)) / 800;
			float rotY = sensitivity * (float)(mouseX - (800 / 2)) / 800;

			// Oblicza nadchodzaca zmiane orientacji w pionie
			Front = glm::rotate(Front, glm::radians(-rotX), glm::normalize(glm::cross(Front, Up)));

			// Obraca orientacje w lewo i w prawo
			Front = glm::rotate(Front, glm::radians(-rotY), Up);

			// Ustawia kursor myszy na srodku ekranu, aby nie wloczyl sie po ekranie
			glfwSetCursorPos(window, (800 / 2), (800 / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Odslania kursor, poniewaz kamera juz sie nie obraca
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Zapewnia, ze nastepnym razem kamera nie przeskoczy
			Click = true;
		}
	}
}


glm::mat4 Camera::GetUpdateView() {
	//Zeby dostac matrix do zmieny w programie
	return glm::lookAt(Position, Position + Front, Up);
}
