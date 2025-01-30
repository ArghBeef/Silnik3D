#ifndef ENGINE_H
#define ENGINE_H

#include<iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"
#include "Primitives.h"
#include "Camera.h"


/**
* @brief Klasa Silnika
* 
* Glowna klasa Engine z metodami Init, Update
*/
class Engine {
public:
	GLFWwindow* window; ///< Okno silnika
	Shader shader; ///< Glowny shader
	Camera camera; ///< Kamera


	Engine() = default;
	/**
	* Metoda to inicjalizacji silnika
	*/
	void Init();
	/**
	* Metoda do aktualizacji z petla
	*/
	void Update();
	/**
	* Zamkniecie wszystkiego
	*/
	void closeWindow();


private:
	/**
	* Obsluga klawiatury i myszy
	*/
	void handleInputs();
	/**
	* Czyszczenie okna
	*/
	void clearWindow(float r, float g, float b);

	glm::mat4 model; ///< uniform model
	glm::mat4 view; ///< uniform view
	glm::mat4 projection; ///< uniform projection

	float framerate = 60.0f; ///< FPS
	float deltaTime; ///< czas

};


#endif