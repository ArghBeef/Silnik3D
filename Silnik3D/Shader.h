#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include <glm.hpp>

/**
* Pobrac zawartosc pliku do programu (w naszym wypadku tekst z shaderami)
* @param filename nazwa pliku
*/
std::string get_file_contents(const char* filename);

/**
 * @class Shader
 * @brief Klasa do Shader
 *
 * Klasa do zarzadzania shaderami, ich zaladowanie i wykorzystanie
 *
 */
class Shader
{
public:
	GLuint ID; ///<ID objektu shadera

	Shader() = default;
	/**
   * Constructor klasy BitmapHandler
   * @param plik do vertex shader
   * @param plik do fragment shader
   */
	Shader(const char* vertexFile, const char* fragmentFile);

	/**
	* Funkcja do aktywowania shaderu
	*/
	void Use();
	/**
	* Funkcja do usuniecia shaderu
	*/
	void Delete();
	/**
	* Funkcja do ustawiania zmiennej uniform zmienna typu matrix
	* @param name nazwa uniform zmiennej
	* @param mat macierz
	*/
	void setMat(const std::string& name, const glm::mat4& mat);
	/**
	* Funkcja do ustawiania zmiennej uniform zmienna typu vec3
	* @param name nazwa uniform zmiennej
	* @param x X 
	* @param y Y
	* @param z Z
	*/
	void setVec(const std::string& name, float x, float y, float z);
	/**
	* Funkcja do ustawiania zmiennej uniform zmienna typu vec3
	* @param name nazwa uniform zmiennej
	* @param vector vector
	*/
	void setVec(const std::string& name, glm::vec3 vector);
};
#endif