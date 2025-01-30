#include "Texture.h"

Texture::Texture(std::string path) {
    
    glGenTextures(1, &texture); //Генерує текстуру
    glActiveTexture(GL_TEXTURE0); // Робить активною
    glBindTexture(GL_TEXTURE_2D, texture); // Звязує з активною

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Параметр що вона повторюється якщо виходить за края
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Параметри що коли відстань збільшується то сама текстура менше
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Зміні для того аби імпортувати (через бібліотеку СТБИ)
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true); // Переворачує
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //Картинка до текстури підєднується
        glGenerateMipmap(GL_TEXTURE_2D); //Генерує міпмапи (менші картинки які міняються з відстаню)
    }
    else {
        perror("Error loading texture");
    }

    //Розвязує з активної
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data); //Звільнює
}
//Звязує
void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}
//Пончик
void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
//Видаляє
void Texture::Delete() {
    glDeleteTextures(1, &texture);
}
//Звраца текстуру
GLuint Texture::GetTexture() {
    return texture;
}