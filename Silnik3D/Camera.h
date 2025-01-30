#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>

/**
* @class Camera
* @brief Klasa Kamery
* 
* Jest klasa kamery - jej inicjalizacja, zarzadzania, obsluga kamery przy pomocy klawiatury i myszy
*/
class Camera {
public:

	glm::vec3 Position; ///< Pozycja kamery
	glm::vec3 Up; ///<Koordynata wskazujac na Y (w gore)
	glm::vec3 Front; ///<Koordynata wskazujac na Z (do przodu)


	Camera() = default;
	/**
	* Constructor klasy Camera
	* @param position poczatkowa pozycja kamery
	*/
	Camera(glm::vec3 position);
	/**
	* Funkcja sterowania kamera
	* @param window okno programu
	*/
	void handleInputs(GLFWwindow* window);
	/**
	* Zwraca mat4 zmian kamery
	* @return matrix zmian
	*/
	glm::mat4 GetUpdateView();

private:
	bool Click; ///<Czy jest nacisnieta mysza

	float speed = 0.05f; ///<Szybkosc ruchu kamery
	float sensitivity = 50.65f; ///<Szybkosc obrotu kamery

};

#endif
