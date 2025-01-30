#ifndef PRIMITIVES_h
#define PRIMITIVES_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/**
* @brief Klasa do prymitywow
* 
* Klasa do stworzenia, rysowania i transformacji prymitywow
*/

class Primitives {
public:
    /**
    * Konstruktor do stworzenia obiektu prymitywu przez tablice wierszcholkow
    * @param tab tablica wierszcholkow
    * @param rozmiar tablicy
    */
	Primitives(float tab[], size_t sizetab);

    /**
    * Konstruktor do stworzenia obiektu z wykorzystaniem juz skompilowanego VBO
    * @param VBO
    * @param rozmiar
    */
    Primitives(GLuint Vertexes, size_t sizetab);

    /**
    * Wiazanie prymitywu (jako aktywny)
    */
    void Bind();
    /**
    * Odwiazanie prymitywu
    */
    void Draw();
    /**
    * Usuniecie prymitywu
    */
    void Delete();

    /**
    * Translacja prymitywu
    * @param x wspolrzedne X
    * @param y wspolrzedne Y
    * @param z wspolrzedne Z
    * @param model uniform do model
    */
    static glm::mat4 Translate(float x, float y, float z, glm::mat4 model);
    /**
    * Obrot prymitywu
    * @param angle kat obrotu
    * @param x wspolrzedne X
    * @param y wspolrzedne Y
    * @param z wspolrzedne Z
    * @param model uniform do model
    */
    static glm::mat4 Rotate(float angle, float x, float y, float z, glm::mat4 model);
    /**
    * Skalowanie prymitywu
    * @param x wspolrzedne X
    * @param y wspolrzedne Y
    * @param z wspolrzedne Z
    * @param model uniform do model
    */
    static glm::mat4 Scale(float x, float y, float z, glm::mat4 model);

    GLuint VBO, VAO; ///<VBO i VAO

    size_t GetSize(); ///<Pobrac rozmiar

private:
    size_t size; ///<Rozmiar
};


#endif 
