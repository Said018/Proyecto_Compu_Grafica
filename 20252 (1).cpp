/*---------------------------------------------------------*/
/* ----------------   Práctica 4 --------------------------*/
/*-----------------    2025-2   ---------------------------*/
/*------------- Alumno Luna Velazquez Said Josue  ---------------*/
/*------------- No. de cuenta:  318128308   ---------------*/
//#include <glew.h>
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>
#include <stdlib.h>		
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>
#include <mmsystem.h>

//void resize(GLFWwindow* window, int width, int height);
/*void my_input(GLFWwindow* window); */ void my_input(GLFWwindow * window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); 
void animate(void);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor* monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 10.0f, 190.0f));
float MovementSpeed = 0.1f;
GLfloat lastX = SCR_WIDTH / 2.0f,
lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

void getResolution(void);
void myData(void);							// De la practica 4
void LoadTextures(void);					// De la práctica 6
unsigned int generateTextures(char*, bool, bool);	// De la práctica 6

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f,
rotZ = 0.0f;

float	angX = 0.0f,
angY = 0.0f,
angZ = 0.0f;

//Texture
unsigned int	t_smile,
t_toalla,
t_unam,
t_white,
t_ladrillos;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

//// Light
glm::vec3 lightColor = glm::vec3(0.7f);
glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

// posiciones
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 90.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,					//VARIABLES DE DIBUJO
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,				//	CAMBIO EN EL CODIGO
giroCabeza = 0.0f,				//	CAMBIO EN EL CODIGO
giroBrazoDerecho = 0.0f,		//	CAMBIO EN EL CODIGO
girohora = 0.0f,				//	CAMBIO EN EL CODIGO
girominuto = 0.0f;				//	CAMBIO EN EL CODIGO
float	incX = 0.0f,					//	VARIABLE DE CALCULO
incY = 0.0f,
incZ = 0.0f,
rotRodIzqInc = 0.0f,
giroMonitoInc = 0.0f,			//	CAMBIO EN EL CODIGO
giroCabezaInc = 0.0f,			//	CAMBIO EN EL CODIGO
giroBrazoDerechoInc = 0.0f,		//	CAMBIO EN EL CODIGO
girohoraInc = 0.0f,			//	CAMBIO EN EL CODIGO
girominutoInc = 0.0f;			//	CAMBIO EN EL CODIGO

#define MAX_FRAMES 18					//Número de KeyFrames		
int i_max_steps = 60;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;
	float giroCabeza;				//	CAMBIO EN EL CODIGO
	float giroBrazoDerecho;			//	CAMBIO EN EL CODIGO
	float girohora;				//	CAMBIO EN EL CODIGO
	float girominuto;			//	CAMBIO EN EL CODIGO	

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//introducir número en caso de tener Key guardados //	SIRVE PARA YA HACER LAS ANIMACIONES CON SOLO COMPILAR
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].giroCabeza = giroCabeza;								//	CAMBIO EN EL CODIGO
	KeyFrame[FrameIndex].giroBrazoDerecho = giroBrazoDerecho;					//	CAMBIO EN EL CODIGO
	KeyFrame[FrameIndex].girohora = girohora;								//	CAMBIO EN EL CODIGO
	KeyFrame[FrameIndex].girominuto = girominuto;								//	CAMBIO EN EL CODIGO

	std::cout << "posX = " << posX << std::endl;								//CAMBIO EN EL CODIGO
	std::cout << "posZ = " << posZ << std::endl;								//CAMBIO EN EL CODIGO
	std::cout << "Giro = " << giroMonito << std::endl;							//CAMBIO EN EL CODIGO	
	std::cout << "Cabeza = " << giroCabeza << std::endl;						//CAMBIO EN EL CODIGO	

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	giroCabeza = KeyFrame[0].giroCabeza;								//	CAMBIO EN EL CODIGO
	giroBrazoDerecho = KeyFrame[0].giroBrazoDerecho;					//	CAMBIO EN EL CODIGO	
	girominuto = KeyFrame[0].girominuto;								//	CAMBIO EN EL CODIGO
	girohora = KeyFrame[0].girohora;								//	CAMBIO EN EL CODIGO	
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotRodIzqInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	giroCabezaInc = (KeyFrame[playIndex + 1].giroCabeza - KeyFrame[playIndex].giroCabeza) / i_max_steps;						//	CAMBIO EN EL CODIGO
	giroBrazoDerechoInc = (KeyFrame[playIndex + 1].giroBrazoDerecho - KeyFrame[playIndex].giroBrazoDerecho) / i_max_steps;		//	CAMBIO EN EL CODIGO
	girominutoInc = (KeyFrame[playIndex + 1].girominuto - KeyFrame[playIndex].girominuto) / i_max_steps;						//	CAMBIO EN EL CODIGO
	girohoraInc = (KeyFrame[playIndex + 1].girohora - KeyFrame[playIndex].girohora) / i_max_steps;						//	CAMBIO EN EL CODIGO	

}

unsigned int generateTextures(const char* filename, bool alfa, bool isPrimitive){
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	if (isPrimitive)
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	else
		stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.


	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void LoadTextures()
{

	t_smile = generateTextures("Texturas/awesomeface.png", 1, true);
	t_toalla = generateTextures("Texturas/toalla.tga", 0, true);
	t_unam = generateTextures("Texturas/escudo_unam.jpg", 0, true);
	t_ladrillos = generateTextures("Texturas/bricks.jpg", 0, true);
	//This must be the last
	t_white = generateTextures("Texturas/white.jpg", 0, false);
}

void animate(void)								//	ES UN CICLO EN SI MISMO
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotRodIzqInc;
			giroMonito += giroMonitoInc;
			giroCabeza += giroCabezaInc;						//	CAMBIO EN EL CODIGO
			giroBrazoDerecho += giroBrazoDerechoInc;			//	CAMBIO EN EL CODIGO
			girominuto += girominutoInc;						//	CAMBIO EN EL CODIGO
			girohora += girohoraInc;						//	CAMBIO EN EL CODIGO

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacion)
	{
		movAuto_x += 3.0f;
	}
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData(){
	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	float verticesPiso[] = {
		// positions          // texture coords
		 10.5f,  10.5f, 0.0f,   4.0f, 4.0f, // top right
		 10.5f, -10.5f, 0.0f,   4.0f, 0.0f, // bottom right
		-10.5f, -10.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-10.5f,  10.5f, 0.0f,   0.0f, 4.0f  // top left 
	};
	unsigned int indicesPiso[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		//V0 - Frontal
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, 0.5f, 0.5f,		//V5
		-0.5f, -0.5f, 0.5f,		//V0
		-0.5f, 0.5f, 0.5f,		//V4
		0.5f, 0.5f, 0.5f,		//V5

		0.5f, -0.5f, -0.5f,		//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, -0.5f,		//V7

		-0.5f, 0.5f, 0.5f,		//V4 - Izq
		-0.5f, 0.5f, -0.5f,		//V7
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, -0.5f, 0.5f,		//V0

		0.5f, 0.5f, 0.5f,		//V5 - Der
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		0.5f, -0.5f, -0.5f,		//V2

		-0.5f, 0.5f, 0.5f,		//V4 - Sup
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, 0.5f, -0.5f,		//V6

		-0.5f, -0.5f, 0.5f,		//V0 - Inf
		-0.5f, -0.5f, -0.5f,	//V3
		0.5f, -0.5f, -0.5f,		//V2
		-0.5f, -0.5f, 0.5f,		//V0
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, -0.5f, 0.5f,		//V1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

/*void dibujarBloquePiso(int xInicio, int xFin, int zInicio, int zFin, Shader& shader, GLuint VAO) {
	for (int x = xInicio; x < xFin; x++) {
		for (int z = zInicio; z < zFin; z++) {
			glm::mat4 PisoTemp = glm::mat4(1.0f);
			PisoTemp = glm::translate(PisoTemp, glm::vec3(x * 1.0f, -0.1f, z * 1.0f));
			PisoTemp = glm::scale(PisoTemp, glm::vec3(1.0f, 0.1f, 1.0f));

			shader.setMat4("model", PisoTemp);
			shader.setVec3("aColor", glm::vec3(0.5f, 0.5f, 0.5f));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}*/

void dibujarBloquePisoNivel(int xInicio, int xFin, int zInicio, int zFin, float yAltura, Shader& shader, GLuint VAO) {
	for (int x = xInicio; x < xFin; x++) {
		for (int z = zInicio; z < zFin; z++) {
			glm::mat4 PisoTemp = glm::mat4(1.0f);
			PisoTemp = glm::translate(PisoTemp, glm::vec3(x * 1.0f, yAltura, z * 1.0f));
			PisoTemp = glm::scale(PisoTemp, glm::vec3(1.0f, 0.5f, 1.0f)); // Piso delgado

			shader.setMat4("model", PisoTemp);
			shader.setVec3("aColor", glm::vec3(0.5f, 0.5f, 0.5f));
			glBindVertexArray(VAO	);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}

void dibujarParedFilaX(int zInicio, int zFin, int yInicio, int yFin, float xPosicion, Shader& shader, GLuint VAO) {
	// Dibujar una pared a lo largo del eje X en el rango zInicio a zFin y en las alturas yInicio a yFin
	for (int z = zInicio; z < zFin; z++) {
		for (int y = yInicio; y < yFin; y++) {
			glm::mat4 pared = glm::mat4(1.0f);

			// Las paredes se moverán en el eje Z y Y (y será variable aquí)
			pared = glm::translate(pared, glm::vec3(xPosicion, y * 5.0f, z * 1.0f));  // Traslación en X, Y y Z
			pared = glm::scale(pared, glm::vec3(1.0f, 5.0f, 1.0f));  // Ajusta el grosor de las paredes

			shader.setMat4("model", pared);
			shader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.2f));  // Color para las paredes

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);  // Dibuja la pared
		}
	}
}

void dibujarParedFilaZ(int xInicio, int xFin, int yInicio, int yFin, float zPosicion, Shader& shader, GLuint VAO) {
	// Dibujar una pared a lo largo del eje Z en el rango xInicio a xFin y en las alturas yInicio a yFin
	for (int x = xInicio; x < xFin; x++) {
		for (int y = yInicio; y < yFin; y++) {
			glm::mat4 pared = glm::mat4(1.0f);

			// Las paredes se moverán en el eje X y Y (y será variable aquí)
			pared = glm::translate(pared, glm::vec3(x * 1.0f, y * 5.0f, zPosicion));  // Se traslada a la posición correcta
			pared = glm::scale(pared, glm::vec3(1.0f, 5.0f, 1.0f));  // Ajusta el grosor de las paredes

			shader.setMat4("model", pared);
			shader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.2f));  // Color para las paredes

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);  // Dibuja la pared
		}
	}
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Final 2025-2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	// 🔥 AQUÍ INICIALIZAS GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Fallo al inicializar GLAD" << std::endl;
		return -1;
	}

	//glewInit();

	//This is new
		//Mis funciones
		//Datos a utilizar
	LoadTextures();	
	myData();
	glEnable(GL_DEPTH_TEST);

	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	//Shader myShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs"); //To use with primitives
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");	//To use with static models
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");	//To use with skybox
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");	//To use with animated models 

	vector<std::string> faces{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	Model BenQ("resources/objects/BenQ/BenQ.obj");
	//Model Table("resources/objects/Table/Table.obj");
	//Model chairminpolycount("resources/objects/chairminpolycount/chairminpolycount.obj");
	


	//myShader.use();


	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection
//	glm::mat4 TempPecho = glm::mat4(1.0f);
	
	glm::mat4 Cesped = glm::mat4(1.0f);
	glm::mat4 Piso = glm::mat4(1.0f);
	glm::mat4 Pared = glm::mat4(1.0f);

	//Use "projection" in order to change how we see the information
	//projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		//my_input(window);

		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		animate();

		// render
		// Background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", ambientColor);
		staticShader.setVec3("dirLight.diffuse", diffuseColor);
		staticShader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 20.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);


//		//Mi bloque de dibujo
//		/*******************************************/
//		glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
//		//Use "view" in order to affect all models
//		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ));
//		viewOp = glm::rotate(viewOp, glm::radians(angX), glm::vec3(1.0f, 0.0f, 0.0f)); //se agrego esta linea durante la sesion, viewOp va a respetar lo que ya tiene la matrix
//		viewOp = glm::rotate(viewOp, glm::radians(angY), glm::vec3(0.0f, 1.0f, 0.0f));
//		viewOp = glm::rotate(viewOp, glm::radians(angZ), glm::vec3(0.0f, 0.0f, 1.0f));
//		// pass them to the shaders
//		myShader.setMat4("model", modelOp);
//		myShader.setMat4("view", viewOp);
//		myShader.setMat4("projection", projectionOp);
//

				//glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		projectionOp = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
		viewOp = camera.GetViewMatrix();
		staticShader.setMat4("projection", projectionOp);
		staticShader.setMat4("view", viewOp);

		//Setup shader for primitives
		myShader.use();
		// view/projection transformations
		//projectionOp = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
		viewOp = camera.GetViewMatrix();
		// pass them to the shaders
		//myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);


		/**********/

		//Model
		glBindVertexArray(VAO);

		//altura tentativa de cad piso es de 2.5mts

		//dibujarBloquePiso(0, 12, 0, 40, myShader, VAO);
		//dibujarBloquePiso(12, 28, 26, 36, myShader, VAO);
		//dibujarBloquePiso(28, 40, 14, 66, myShader, VAO);

/*		// Piso 1 (nivel de planta baja)
		dibujarBloquePisoNivel(0, 12, 0, 40, 0.0f, myShader, VAO);  // Primer bloque
		dibujarBloquePisoNivel(12, 28, 26, 36, 0.0f, myShader, VAO); // Segundo bloque
		dibujarBloquePisoNivel(28, 40, 14, 66, 0.0f, myShader, VAO); // Pasillo largo

		// Piso 2 (primer nivel)
		dibujarBloquePisoNivel(0, 12, 0, 40, 5.0f, myShader, VAO);
		dibujarBloquePisoNivel(12, 28, 26, 36, 5.0f, myShader, VAO);
		dibujarBloquePisoNivel(28, 40, 14, 66, 5.0f, myShader, VAO);

		// Piso 3 (segundo nivel)
		dibujarBloquePisoNivel(0, 12, 0, 40, 10.0f, myShader, VAO);
		dibujarBloquePisoNivel(12, 28, 26, 36, 10.0f, myShader, VAO);
		dibujarBloquePisoNivel(28, 40, 14, 66, 10.0f, myShader, VAO);

		// Piso 4 (tercer nivel)
		dibujarBloquePisoNivel(0, 12, 0, 40, 15.0f, myShader, VAO);
		dibujarBloquePisoNivel(12, 28, 26, 36, 15.0f, myShader, VAO);
		dibujarBloquePisoNivel(28, 40, 14, 66, 15.0f, myShader, VAO);

		// Piso 5 (techo)
		dibujarBloquePisoNivel(0, 12, 0, 40, 20.0f, myShader, VAO);
		dibujarBloquePisoNivel(12, 28, 26, 36, 20.0f, myShader, VAO);
		dibujarBloquePisoNivel(28, 40, 14, 66, 20.0f, myShader, VAO);

		// Dibujar una pared 
		dibujarParedFilaZ(0, 12, 0, 5, 0.0f, myShader, VAO); 
		dibujarParedFilaZ(0, 12, 0, 5, 40.0f, myShader, VAO);

		dibujarParedFilaZ(12, 28, 0, 5, 26.0f, myShader, VAO);
		dibujarParedFilaZ(12, 28, 0, 5, 36.0f, myShader, VAO);

		dibujarParedFilaZ(28, 40, 0, 5, 14.0f, myShader, VAO); 
		dibujarParedFilaZ(28, 40, 0, 5, 66.0f, myShader, VAO); 

		dibujarParedFilaX(0, 40, 0, 5, 0.0f, myShader, VAO);
		dibujarParedFilaX(0, 26, 0, 5, 12.0f, myShader, VAO);
		dibujarParedFilaX(36, 40, 0, 5, 12.0f, myShader, VAO);

		dibujarParedFilaX(14, 26, 0, 5, 28.0f, myShader, VAO);
		dibujarParedFilaX(36, 66, 0, 5, 28.0f, myShader, VAO);
		dibujarParedFilaX(14, 66, 0, 5, 40.0f, myShader, VAO);*/


		//
		//

 

		// Dibujar una pared 
		//dibujarParedFilaZ(28, 40, 0, 14, 2.3f, myShader, VAO);



/*		// Piso 1 (nivel de planta baja)
		dibujarParedesNivel(0, 12, 0, 26, 0.0f, myShader, VAO);
		dibujarParedesNivel(12, 28, 26, 36, 0.0f, myShader, VAO);
		dibujarParedesNivel(28, 40, 14, 66, 0.0f, myShader, VAO);

		// Piso 2 (primer nivel)
		dibujarParedesNivel(0, 12, 0, 40, 5.0f, myShader, VAO);
		dibujarParedesNivel(12, 28, 26, 36, 5.0f, myShader, VAO);
		dibujarParedesNivel(28, 40, 14, 66, 5.0f, myShader, VAO);

		// Piso 3 (segundo nivel)
		dibujarParedesNivel(0, 12, 0, 40, 10.0f, myShader, VAO);
		dibujarParedesNivel(12, 28, 26, 36, 10.0f, myShader, VAO);
		dibujarParedesNivel(28, 40, 14, 66, 10.0f, myShader, VAO);

		// Piso 4 (tercer nivel)
		dibujarParedesNivel(0, 12, 0, 40, 15.0f, myShader, VAO);
		dibujarParedesNivel(12, 28, 26, 36, 15.0f, myShader, VAO);
		dibujarParedesNivel(28, 40, 14, 66, 15.0f, myShader, VAO);

		// Piso 5 (techo)
		dibujarParedesNivel(0, 12, 0, 40, 20.0f, myShader, VAO);
		dibujarParedesNivel(12, 28, 26, 36, 20.0f, myShader, VAO);
		dibujarParedesNivel(28, 40, 14, 66, 20.0f, myShader, VAO);
*/		

		glBindVertexArray(0);


		staticShader.use();
		staticShader.setMat4("projection", projectionOp);
		staticShader.setMat4("view", viewOp);


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//modelOp = glm::rotate(modelOp, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.1f));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		BenQ.Draw(staticShader);

		/*modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Table.Draw(staticShader);*/

		/*modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		chairminpolycount.Draw(staticShader);*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------

		//Con estas lineas se dibuja el mar y las montañas y sin esta linea el fondo es negro
		/*/skyboxShader.use();
		skybox.Draw(skyboxShader, viewOp, projectionOp, camera);*/

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	//glDeleteVertexArrays(2, VAO);
	//glDeleteBuffers(2, VBO);
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) //
		angX += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) //
		angX -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) //
		angY += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) //
		angY -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) //
		angZ += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS) //
		angZ -= 1.0f;

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

