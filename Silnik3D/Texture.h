#ifndef TEXTURE_H
#define TEXTURE_H


#include "glad/glad.h"
#include <string>
#include <stb/stb_image.h>

/**
* @brief Klasa do Tekstur
* Klasa wykorzystana do ladowania, tworzenia i wykorzystania tekstur
*/

class Texture {
public:
	/**
	* Konstruktor klasy Texture
	* @param path nazwa tekstury na dysku
	*/
	Texture(std::string path);
	
	/**
	* Wiazanie tekstury (jako aktywna)
	*/
	void Bind();
	/**
	* Odwiazanie tekstury
	*/
	static void Unbind();
	/**
	* Usuniecie tekstury
	*/
	void Delete();
	/**
	* Dostac teksture
	* @return zwraca teksture
	*/
	GLuint GetTexture();

private:
	GLuint texture; ///<Tekstura
};

#endif
