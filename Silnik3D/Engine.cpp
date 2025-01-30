#include "Engine.h"


void Engine::Init() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(800, 800, "Silnik3D", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Window error";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);

	shader = Shader("default.vert", "default.frag");
	camera = Camera(glm::vec3(0.0f, 0.0f, -1.0f));
}

void Engine::handleInputs() {

	camera.handleInputs(window);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	for (int i = GLFW_KEY_1; i <= GLFW_KEY_9; ++i) {
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			framerate = (i - GLFW_KEY_0) * 10.0f;
			std::cout << framerate << " FPS\n";
		}
	}
}

void Engine::Update() {

	float lastTime = glfwGetTime();
	deltaTime = 0.0;

	float pyramida[] = {
		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,

		 0.5f, 0.0f,  0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f,  0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f,  -1.0f, 0.5f, -1.0f,
		 0.5f, 0.0f, -0.5f,  1.0f, 0.0f,   1.0f, 0.5f, -1.0f,
		 0.0f, 1.0f,  0.0f,  0.5f, 1.0f,   0.0f, 1.0f, 0.0f,

		 0.5f, 0.0f, -0.5f,  0.0f, 0.0f,   1.0f, 0.5f, -1.0f,
		 0.5f, 0.0f,  0.5f,  1.0f, 0.0f,   1.0f, 0.5f, 1.0f,
		 0.0f, 1.0f,  0.0f,  0.5f, 1.0f,   0.0f, 1.0f, 0.0f,

		 0.5f, 0.0f,  0.5f,  0.0f, 0.0f,   1.0f, 0.5f, 1.0f,
		-0.5f, 0.0f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.5f, 1.0f,
		 0.0f, 1.0f,  0.0f,  0.5f, 1.0f,   0.0f, 1.0f, 0.0f,

		-0.5f, 0.0f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.5f, 1.0f,
		-0.5f, 0.0f, -0.5f,  1.0f, 0.0f,  -1.0f, 0.5f, -1.0f,
		 0.0f, 1.0f,  0.0f,  0.5f, 1.0f,   0.0f, 1.0f, 0.0f
	};
	float cube[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	model = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(125.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	Primitives kub(cube, sizeof(cube));
	Primitives pyramid(pyramida, sizeof(pyramida));
	Texture tex("tf2.jpg");


	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime += (currentTime - lastTime) * framerate;
		lastTime = currentTime;

		if (deltaTime >= 1.0) {
	
			handleInputs();
			clearWindow(0.05f, 0.0f, 0.05f);

			shader.Use();
			shader.setVec("lightposition", 1.0f, 3.0f, 1.8f);
			shader.setVec("lightcolor", 1.0f, 1.0f, 1.0f);
			shader.setVec("cameraposition",camera.Position);

			shader.setMat("projection", projection);

			glm::mat4 view = camera.GetUpdateView();
			shader.setMat("view", view);

			model = glm::mat4(1.0f);
			model = Primitives::Scale(0.6f, 0.6f, 1.0f, model);
			shader.setMat("model", model);
			tex.Bind();
			kub.Bind();
			kub.Draw();


			model = glm::mat4(1.0f);
			model = Primitives::Translate(0.0f, 1.2f, 2.0f, model);
			model = glm::rotate(model, glm::radians(150 * (float)glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.5f));
			shader.setMat("model", model);
			pyramid.Bind();
			pyramid.Draw();


			glfwPollEvents();
			glfwSwapBuffers(window);

			deltaTime--;
		}
	}

	closeWindow();
}

void Engine::clearWindow(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::closeWindow() {
	

	shader.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
}