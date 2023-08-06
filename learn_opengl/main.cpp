#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include"Shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

}
void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { //����Ƿ�����esc��
		glfwSetWindowShouldClose(window, true);
	}
}
int main() {



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	//�������ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 800, "Learn opengl", NULL, NULL);
	glfwMakeContextCurrent(window);


	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	

	//GLAD����opengl�ĺ���ָ�� �� GLAD ���ݺ����������ض��ڲ���ϵͳ�� OpenGL ����ָ��ĵ�ַ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initial GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	//ע��GLFW�ص����� �����ڴ�������֮���������Ⱦѭ��֮ǰע��ص�������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2  // first triangle

	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	//const char* vertexShaderSource = "#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"layout (location = 1) in vec3 aColor;\n"
	//	"out vec3 ourColor;"
	//	"void main()\n"
	//	"{\n"
	//	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	//	"   ourColor=aColor;\n"
	//	"}\0";
	//const char* fragmentShaderSource = "#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"in  vec3 ourColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"   FragColor = vec4(ourColor,1.0);\n"
	//	"}\0";
	
	Shader shader("./vertexShader.vs","./fragmentShader.vs");



	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {  //glfwWindowShouldClose �������glfw�Ƿ��ѱ�ָʾ�ر�

		//input
		ProcessInput(window);

		//render	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		shader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//check and call events
		glfwSwapBuffers(window); //˫�����������л�
		glfwPollEvents(); //����Ƿ񴥷��κ��¼�����������������ƶ��¼��������´���״̬����������Ӧ�ĺ��������ǿ���ͨ���ص�����ע�ᣩ
	}
	glfwTerminate(); //����ѷ����glfw��Դ

	return 0;

}