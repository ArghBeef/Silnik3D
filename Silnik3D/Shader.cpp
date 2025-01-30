#include"Shader.h"

// Читає текстовий файл і повертає рядок з усім вмістом файлу
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Завантажує файли шейдерів і зберігає їх у рядки
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Пупи для логу
	GLint success;
	GLchar infoLog[512];

	// Перетворює текстові рядки з кодом шейдерів у масиви символів
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Створює об'єкт вершинного шейдера і отримує його посилання
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Прикріплює вихідний код вершинного шейдера до об'єкта шейдера
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Компілює вершинний шейдер у машинний код
	glCompileShader(vertexShader);

	//Провірка чи все ок
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Помилка компіляції вершинного шейдера:\n" << infoLog << std::endl;
	}

	// Створює об'єкт фрагментного шейдера і отримує його посилання
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Прикріплює вихідний код фрагментного шейдера до об'єкта шейдера
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Компілює фрагментний шейдер у машинний код
	glCompileShader(fragmentShader);

	//Провірка чи все ок
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Помилка компіляції фрагментного шейдера:\n" << infoLog << std::endl;
	}

	// Створює об'єкт програми шейдерів і отримує його посилання
	ID = glCreateProgram();
	// Прикріплює вершинний і фрагментний шейдери до програми шейдерів
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Завершує/зв'язує всі шейдери разом у програму шейдерів
	glLinkProgram(ID);
	//Провірка чи все ок
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Помилка зв'язування програми шейдерів:\n" << infoLog << std::endl;
	}

	// Видаляє непотрібні об'єкти вершинного та фрагментного шейдерів
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Активує програму шейдерів
void Shader::Use()
{
	glUseProgram(ID);
}

// Видаляє програму шейдерів
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Пупи які міняють uniform зміну, треба три для матриць, і два для векторів (другу подаєм просто вектор)
void Shader::setMat(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec(const std::string& name, glm::vec3 vector) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}
