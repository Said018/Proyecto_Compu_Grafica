﻿/*---------------------------------------------------------*/
/* ----------------   Práctica  --------------------------*/
/*-----------------    2025-2   ---------------------------*/
/*----------- Alumno: Ruiz Gaspar José Ángel  -------------*/
/*------------- No. Cuenta  318263883       ---------------*/

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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor* monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 30.0f, 50.0f));
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

int estadoAnimacion1 = 1,
estadoAnimacion2 = 1,
estadoAnimacion3 = 1,
estadoAnimacion4 = 1;

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

// posiciones
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 90.0f;
bool	animacion = false,
animacion2 = false,
animacion3 = false,
animacion4 = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,					//VARIABLES DE DIBUJO
posY = -10.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,				//	CAMBIO EN EL CODIGO
giroCabeza = 0.0f,				//	CAMBIO EN EL CODIGO
giroBrazoDerecho = 0.0f,		//	CAMBIO EN EL CODIGO
girohora = 0.0f,				//	CAMBIO EN EL CODIGO
girominuto = 0.0f,
giropokeball = 0.0f,
girotapapokeball = 0.0f,
//Sillas translacion
movXsilla1 = 16.0f,
movYsilla1 = 13.0f,
movZsilla1 = 0.0f,
movXsilla2 = 16.0f,
movYsilla2 = 23.0f,
movZsilla2 = 0.0f,
movXsilla3 = 16.0f,
movYsilla3 = 35.0f,
movZsilla3 = 0.0f,
movXsilla4 = 16.0f,
movYsilla4 = 45.0f,
movZsilla4 = 0.0f,
movXsilla5 = 16.0f,
movYsilla5 = -10.0f,
movZsilla5 = 0.0f,
movXsilla6 = 16.0f,
movYsilla6 = -20.0f,
movZsilla6 = 0.0f,
movXsilla7 = 16.0f,
movYsilla7 = -33.0f,
movZsilla7 = 0.0f,
movXsilla8 = 16.0f,
movYsilla8 = -43.0f,
movZsilla8 = 0.0f,
movXsilla9 = -10.0f,
movYsilla9 = 13.0f,
movZsilla9 = 0.0f,
movXsilla10 = -10.0f,
movYsilla10 = 23.0f,
movZsilla10 = 0.0f,
movXsilla11 = -10.0f,
movYsilla11 = 35.0f,
movZsilla11 = 0.0f,
movXsilla12 = -10.0f,
movYsilla12 = 45.0f,
movZsilla12 = 0.0f,
movXsilla13 = -10.0f,
movYsilla13 = -10.0f,
movZsilla13 = 0.0f,
movXsilla14 = -10.0f,
movYsilla14 = -20.0f,
movZsilla14 = 0.0f,
movXsilla15 = -10.0f,
movYsilla15 = -33.0f,
movZsilla15 = 0.0f,
movXsilla16 = -10.0f,
movYsilla16 = -43.0f,
movZsilla16 = 0.0f,
movXsilla17 = -35.0f,
movYsilla17 = 13.0f,
movZsilla17 = 0.0f,
movXsilla18 = -35.0f,
movYsilla18 = 23.0f,
movZsilla18 = 0.0f,
movXsilla19 = -35.0f,
movYsilla19 = 35.0f,
movZsilla19 = 0.0f,
movXsilla20 = -35.0f,
movYsilla20 = 45.0f,
movZsilla20 = 0.0f,
movXsilla21 = -35.0f,
movYsilla21 = -10.0f,
movZsilla21 = 0.0f,
movXsilla22 = -35.0f,
movYsilla22 = -20.0f,
movZsilla22 = 0.0f,
movXsilla23 = -35.0f,
movYsilla23 = -33.0f,
movZsilla23 = 0.0f,
movXsilla24 = -35.0f,
movYsilla24 = -43.0f,
movZsilla24 = 0.0f,
//sillas rotacion SOLO SE OCUPA 1
giroZsillas = 90.0f,
//sillas scale SOLO SE OCUPA 1
scalesillas = 12.0f,
//Mesas translacion
movXmesa1 = 30.0f,
movYmesa1 = 16.0f,
movZmesa1 = 0.0f,
movXmesa2 = 30.0f,
movYmesa2 = 38.0f,
movZmesa2 = 0.0f,
movXmesa3 = 30.0f,
movYmesa3 = -16.0f,
movZmesa3 = 0.0f,
movXmesa4 = 30.0f,
movYmesa4 = -38.0f,
movZmesa4 = 0.0f,
movXmesa5 = 5.0f,
movYmesa5 = 16.0f,
movZmesa5 = 0.0f,
movXmesa6 = 5.0f,
movYmesa6 = 38.0f,
movZmesa6 = 0.0f,
movXmesa7 = 5.0f,
movYmesa7 = -16.0f,
movZmesa7 = 0.0f,
movXmesa8 = 5.0f,
movYmesa8 = -38.0f,
movZmesa8 = 0.0f,
movXmesa9 = -20.0f,
movYmesa9 = 16.0f,
movZmesa9 = 0.0f,
movXmesa10 = -20.0f,
movYmesa10 = 38.0f,
movZmesa10 = 0.0f,
movXmesa11 = -20.0f,
movYmesa11 = -16.0f,
movZmesa11 = 0.0f,
movXmesa12 = -20.0f,
movYmesa12 = -38.0f,
movZmesa12 = 0.0f,
//mesas rotacion SOLO SE OCUPA
giroZmesas = 270.0f,
//mesas scale SOLO SE OCUPAN 3 QUE SON 1
scaleXmesas = 19.0f,				//	VARIABLES DE ESCALADO
scaleYmesas = 15.0f,
scaleZmesas = 16.0f,
//display translacion
movXdisplay1 = 24.0f,
movYdisplay1 = 16.0f,
movZdisplay1 = 13.0f,
movXdisplay2 = 24.0f,
movYdisplay2 = 39.0f,
movZdisplay2 = 13.0f,
movXdisplay3 = 24.0f,
movYdisplay3 = -16.0f,
movZdisplay3 = 13.0f,
movXdisplay4 = 24.0f,
movYdisplay4 = -39.0f,
movZdisplay4 = 13.0f,
movXdisplay5 = -1.0f,
movYdisplay5 = 16.0f,
movZdisplay5 = 13.0f,
movXdisplay6 = -1.0f,
movYdisplay6 = 38.0f,
movZdisplay6 = 13.0f,
movXdisplay7 = -1.0f,
movYdisplay7 = -16.0f,
movZdisplay7 = 13.0f,
movXdisplay8 = -1.0f,
movYdisplay8 = -39.0f,
movZdisplay8 = 13.0f,
movXdisplay9 = -26.0f,
movYdisplay9 = 16.0f,
movZdisplay9 = 13.0f,
movXdisplay10 = -26.0f,
movYdisplay10 = 39.0f,
movZdisplay10 = 13.0f,
movXdisplay11 = -26.0f,
movYdisplay11 = -16.0f,
movZdisplay11 = 13.0f,
movXdisplay12 = -26.0f,
movYdisplay12 = -39.0f,
movZdisplay12 = 13.0f,
//display rotacion SOLO SE OCUPA 1
giroZdisplay = 270.0f,
//display scale SOLO SE OCUPA 1
scaledisplay = 2.5f,				//	VARIABLES DE ESCALADO	
//PC_Case translacion
movXpccase1 = 24.0f,
movYpccase1 = 25.0f,
movZpccase1 = 16.0f,
movXpccase2 = 24.0f,
movYpccase2 = 30.0f,
movZpccase2 = 16.0f,
movXpccase3 = 24.0f,
movYpccase3 = -25.0f,
movZpccase3 = 16.0f,
movXpccase4 = 24.0f,
movYpccase4 = -30.0f,
movZpccase4 = 16.0f,
movXpccase5 = -1.0f,
movYpccase5 = 25.0f,
movZpccase5 = 16.0f,
movXpccase6 = -1.0f,
movYpccase6 = 30.0f,
movZpccase6 = 16.0f,
movXpccase7 = -1.0f,
movYpccase7 = -25.0f,
movZpccase7 = 16.0f,
movXpccase8 = -1.0f,
movYpccase8 = -30.0f,
movZpccase8 = 16.0f,
movXpccase9 = -26.0f,
movYpccase9 = 25.0f,
movZpccase9 = 16.0f,
movXpccase10 = -26.0f,
movYpccase10 = 30.0f,
movZpccase10 = 16.0f,
movXpccase11 = -26.0f,
movYpccase11 = -25.0f,
movZpccase11 = 16.0f,
movXpccase12 = -26.0f,
movYpccase12 = -30.0f,
movZpccase12 = 16.0f,
//PC_Case rotacion SOLO SE OCUPA 1
giroZpccases = 180.0f,
//PC_Case scale SOLO SSE OCUPA 1
scalepccases = 2.5f;				//	VARIABLES DE ESCALADO

//Variables de incremento
float	incX = 0.0f,					//	VARIABLE DE CALCULO
incY = 0.0f,
incZ = 0.0f,
rotRodIzqInc = 0.0f,
giroMonitoInc = 0.0f,			//	CAMBIO EN EL CODIGO
giroCabezaInc = 0.0f,			//	CAMBIO EN EL CODIGO
giroBrazoDerechoInc = 0.0f,		//	CAMBIO EN EL CODIGO
girohoraInc = 0.0f,			//	CAMBIO EN EL CODIGO
girominutoInc = 0.0f,			//	CAMBIO EN EL CODIGO
giropokeballInc = 0.0f,
girotapapokeballInc = 0.0f,

//Sillas translacion
movXsilla1Inc = 16.0f,
movYsilla1Inc = 13.0f,
movZsilla1Inc = 0.0f,
movXsilla2Inc = 16.0f,
movYsilla2Inc = 23.0f,
movZsilla2Inc = 0.0f,
movXsilla3Inc = 16.0f,
movYsilla3Inc = 35.0f,
movZsilla3Inc = 0.0f,
movXsilla4Inc = 16.0f,
movYsilla4Inc = 45.0f,
movZsilla4Inc = 0.0f,
movXsilla5Inc = 16.0f,
movYsilla5Inc = -10.0f,
movZsilla5Inc = 0.0f,
movXsilla6Inc = 16.0f,
movYsilla6Inc = -20.0f,
movZsilla6Inc = 0.0f,
movXsilla7Inc = 16.0f,
movYsilla7Inc = -33.0f,
movZsilla7Inc = 0.0f,
movXsilla8Inc = 16.0f,
movYsilla8Inc = -43.0f,
movZsilla8Inc = 0.0f,
movXsilla9Inc = -10.0f,
movYsilla9Inc = 13.0f,
movZsilla9Inc = 0.0f,
movXsilla10Inc = -10.0f,
movYsilla10Inc = 13.0f,
movZsilla10Inc = 0.0f,
movXsilla11Inc = -10.0f,
movYsilla11Inc = 35.0f,
movZsilla11Inc = 0.0f,
movXsilla12Inc = -10.0f,
movYsilla12Inc = 45.0f,
movZsilla12Inc = 0.0f,
movXsilla13Inc = -10.0f,
movYsilla13Inc = -10.0f,
movZsilla13Inc = 0.0f,
movXsilla14Inc = -10.0f,
movYsilla14Inc = -20.0f,
movZsilla14Inc = 0.0f,
movXsilla15Inc = -10.0f,
movYsilla15Inc = -33.0f,
movZsilla15Inc = 0.0f,
movXsilla16Inc = -10.0f,
movYsilla16Inc = -43.0f,
movZsilla16Inc = 0.0f,
movXsilla17Inc = -35.0f,
movYsilla17Inc = 13.0f,
movZsilla17Inc = 0.0f,
movXsilla18Inc = -35.0f,
movYsilla18Inc = 23.0f,
movZsilla18Inc = 0.0f,
movXsilla19Inc = -35.0f,
movYsilla19Inc = 35.0f,
movZsilla19Inc = 0.0f,
movXsilla20Inc = -35.0f,
movYsilla20Inc = 45.0f,
movZsilla20Inc = 0.0f,
movXsilla21Inc = -35.0f,
movYsilla21Inc = -10.0f,
movZsilla21Inc = 0.0f,
movXsilla22Inc = -35.0f,
movYsilla22Inc = -20.0f,
movZsilla22Inc = 0.0f,
movXsilla23Inc = -35.0f,
movYsilla23Inc = -33.0f,
movZsilla23Inc = 0.0f,
movXsilla24Inc = -35.0f,
movYsilla24Inc = -43.0f,
movZsilla24Inc = 0.0f,
//sillas rotacion
giroZsillasInc = 90.0f,
//sillas scale
scalesillasInc = 12.0f,
//Mesas translacion
movXmesa1Inc = 0.0f,
movYmesa1Inc = 0.0f,
movZmesa1Inc = 0.0f,
movXmesa2Inc = 0.0f,
movYmesa2Inc = 0.0f,
movZmesa2Inc = 0.0f,
movXmesa3Inc = 0.0f,
movYmesa3Inc = 0.0f,
movZmesa3Inc = 0.0f,
movXmesa4Inc = 0.0f,
movYmesa4Inc = 0.0f,
movZmesa4Inc = 0.0f,
movXmesa5Inc = 0.0f,
movYmesa5Inc = 0.0f,
movZmesa5Inc = 0.0f,
movXmesa6Inc = 0.0f,
movYmesa6Inc = 0.0f,
movZmesa6Inc = 0.0f,
movXmesa7Inc = 0.0f,
movYmesa7Inc = 0.0f,
movZmesa7Inc = 0.0f,
movXmesa8Inc = 0.0f,
movYmesa8Inc = 0.0f,
movZmesa8Inc = 0.0f,
movXmesa9Inc = 0.0f,
movYmesa9Inc = 0.0f,
movZmesa9Inc = 0.0f,
movXmesa10Inc = 0.0f,
movYmesa10Inc = 0.0f,
movZmesa10Inc = 0.0f,
movXmesa11Inc = 0.0f,
movYmesa11Inc = 0.0f,
movZmesa11Inc = 0.0f,
movXmesa12Inc = 0.0f,
movYmesa12Inc = 0.0f,
movZmesa12Inc = 0.0f,
//mesas rotacion
giroZmesasInc = 0.0f,
//mesas scale
scaleXmesasInc = 0.0f,				//	VARIABLES DE ESCALADO
scaleYmesasInc = 0.0f,
scaleZmesasInc = 0.0f,
//display translacion
movXdisplay1Inc = 0.0f,
movYdisplay1Inc = 0.0f,
movZdisplay1Inc = 0.0f,
movXdisplay2Inc = 0.0f,
movYdisplay2Inc = 0.0f,
movZdisplay2Inc = 0.0f,
movXdisplay3Inc = 0.0f,
movYdisplay3Inc = 0.0f,
movZdisplay3Inc = 0.0f,
movXdisplay4Inc = 0.0f,
movYdisplay4Inc = 0.0f,
movZdisplay4Inc = 0.0f,
movXdisplay5Inc = 0.0f,
movYdisplay5Inc = 0.0f,
movZdisplay5Inc = 0.0f,
movXdisplay6Inc = 0.0f,
movYdisplay6Inc = 0.0f,
movZdisplay6Inc = 0.0f,
movXdisplay7Inc = 0.0f,
movYdisplay7Inc = 0.0f,
movZdisplay7Inc = 0.0f,
movXdisplay8Inc = 0.0f,
movYdisplay8Inc = 0.0f,
movZdisplay8Inc = 0.0f,
movXdisplay9Inc = 0.0f,
movYdisplay9Inc = 0.0f,
movZdisplay9Inc = 0.0f,
movXdisplay10Inc = 0.0f,
movYdisplay10Inc = 0.0f,
movZdisplay10Inc = 0.0f,
movXdisplay11Inc = 0.0f,
movYdisplay11Inc = 0.0f,
movZdisplay11Inc = 0.0f,
movXdisplay12Inc = 0.0f,
movYdisplay12Inc = 0.0f,
movZdisplay12Inc = 0.0f,
//display rotacion
giroZdisplayInc = 0.0f,
//display scale
scaledisplayInc = 0.0f,				//	VARIABLES DE ESCALADO	
//PC_Case translacion
movXpccase1Inc = 0.0f,
movYpccase1Inc = 0.0f,
movZpccase1Inc = 0.0f,
movXpccase2Inc = 0.0f,
movYpccase2Inc = 0.0f,
movZpccase2Inc = 0.0f,
movXpccase3Inc = 0.0f,
movYpccase3Inc = 0.0f,
movZpccase3Inc = 0.0f,
movXpccase4Inc = 0.0f,
movYpccase4Inc = 0.0f,
movZpccase4Inc = 0.0f,
movXpccase5Inc = 0.0f,
movYpccase5Inc = 0.0f,
movZpccase5Inc = 0.0f,
movXpccase6Inc = 0.0f,
movYpccase6Inc = 0.0f,
movZpccase6Inc = 0.0f,
movXpccase7Inc = 0.0f,
movYpccase7Inc = 0.0f,
movZpccase7Inc = 0.0f,
movXpccase8Inc = 0.0f,
movYpccase8Inc = 0.0f,
movZpccase8Inc = 0.0f,
movXpccase9Inc = 0.0f,
movYpccase9Inc = 0.0f,
movZpccase9Inc = 0.0f,
movXpccase10Inc = 0.0f,
movYpccase10Inc = 0.0f,
movZpccase10Inc = 0.0f,
movXpccase11Inc = 0.0f,
movYpccase11Inc = 0.0f,
movZpccase11Inc = 0.0f,
movXpccase12Inc = 0.0f,
movYpccase12Inc = 0.0f,
movZpccase12Inc = 0.0f,
//PC_Case rotacion
giroZpccasesInc = 0.0f,
//PC_Case scale
scalepccasesInc = 0.0f;				//	VARIABLES DE ESCALADO

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
	float movXsilla1;
	float movYsilla1;
	float movZsilla1;
	float movXsilla2;
	float movYsilla2;
	float movZsilla2;
	float movXsilla3;
	float movYsilla3;
	float movZsilla3;
	float movXsilla4;
	float movYsilla4;
	float movZsilla4;
	float movXsilla5;
	float movYsilla5;
	float movZsilla5;
	float movXsilla6;
	float movYsilla6;
	float movZsilla6;
	float movXsilla7;
	float movYsilla7;
	float movZsilla7;
	float movXsilla8;
	float movYsilla8;
	float movZsilla8;
	float movXsilla9;
	float movYsilla9;
	float movZsilla9;
	float movXsilla10;
	float movYsilla10;
	float movZsilla10;
	float movXsilla11;
	float movYsilla11;
	float movZsilla11;
	float movXsilla12;
	float movYsilla12;
	float movZsilla12;
	float movXsilla13;
	float movYsilla13;
	float movZsilla13;
	float movXsilla14;
	float movYsilla14;
	float movZsilla14;
	float movXsilla15;
	float movYsilla15;
	float movZsilla15;
	float movXsilla16;
	float movYsilla16;
	float movZsilla16;
	float movXsilla17;
	float movYsilla17;
	float movZsilla17;
	float movXsilla18;
	float movYsilla18;
	float movZsilla18;
	float movXsilla19;
	float movYsilla19;
	float movZsilla19;
	float movXsilla20;
	float movYsilla20;
	float movZsilla20;
	float movXsilla21;
	float movYsilla21;
	float movZsilla21;
	float movXsilla22;
	float movYsilla22;
	float movZsilla22;
	float movXsilla23;
	float movYsilla23;
	float movZsilla23;
	float movXsilla24;
	float movYsilla24;
	float movZsilla24;
	float giroZsillas;
	float scalesillas;
	float movXmesa1;
	float movYmesa1;
	float movZmesa1;
	float movXmesa2;
	float movYmesa2;
	float movZmesa2;
	float movXmesa3;
	float movYmesa3;
	float movZmesa3;
	float movXmesa4;
	float movYmesa4;
	float movZmesa4;
	float movXmesa5;
	float movYmesa5;
	float movZmesa5;
	float movXmesa6;
	float movYmesa6;
	float movZmesa6;
	float movXmesa7;
	float movYmesa7;
	float movZmesa7;
	float movXmesa8;
	float movYmesa8;
	float movZmesa8;
	float movXmesa9;
	float movYmesa9;
	float movZmesa9;
	float movXmesa10;
	float movYmesa10;
	float movZmesa10;
	float movXmesa11;
	float movYmesa11;
	float movZmesa11;
	float movXmesa12;
	float movYmesa12;
	float movZmesa12;
	float giroZmesas;
	float scaleXmesas;
	float scaleYmesas;
	float scaleZmesas;
	float movXdisplay1;
	float movYdisplay1;
	float movZdisplay1;
	float movXdisplay2;
	float movYdisplay2;
	float movZdisplay2;
	float movXdisplay3;
	float movYdisplay3;
	float movZdisplay3;
	float movXdisplay4;
	float movYdisplay4;
	float movZdisplay4;
	float movXdisplay5;
	float movYdisplay5;
	float movZdisplay5;
	float movXdisplay6;
	float movYdisplay6;
	float movZdisplay6;
	float movXdisplay7;
	float movYdisplay7;
	float movZdisplay7;
	float movXdisplay8;
	float movYdisplay8;
	float movZdisplay8;
	float movXdisplay9;
	float movYdisplay9;
	float movZdisplay9;
	float movXdisplay10;
	float movYdisplay10;
	float movZdisplay10;
	float movXdisplay11;
	float movYdisplay11;
	float movZdisplay11;
	float movXdisplay12;
	float movYdisplay12;
	float movZdisplay12;
	float giroZdisplay;
	float scaledisplay;
	float movXpccase1;
	float movYpccase1;
	float movZpccase1;
	float movXpccase2;
	float movYpccase2;
	float movZpccase2;
	float movXpccase3;
	float movYpccase3;
	float movZpccase3;
	float movXpccase4;
	float movYpccase4;
	float movZpccase4;
	float movXpccase5;
	float movYpccase5;
	float movZpccase5;
	float movXpccase6;
	float movYpccase6;
	float movZpccase6;
	float movXpccase7;
	float movYpccase7;
	float movZpccase7;
	float movXpccase8;
	float movYpccase8;
	float movZpccase8;
	float movXpccase9;
	float movYpccase9;
	float movZpccase9;
	float movXpccase10;
	float movYpccase10;
	float movZpccase10;
	float movXpccase11;
	float movYpccase11;
	float movZpccase11;
	float movXpccase12;
	float movYpccase12;
	float movZpccase12;
	float giroZpccases;
	float scalepccases;
	float giropokeball;
	float girotapapokeball;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 15;			//introducir número en caso de tener Key guardados //	SIRVE PARA YA HACER LAS ANIMACIONES CON SOLO COMPILAR
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
	KeyFrame[FrameIndex].giropokeball = giropokeball;
	KeyFrame[FrameIndex].girotapapokeball = girotapapokeball;
	KeyFrame[FrameIndex].movXsilla1 = movXsilla1;
	KeyFrame[FrameIndex].movYsilla1 = movYsilla1;
	KeyFrame[FrameIndex].movZsilla1 = movZsilla1;
	KeyFrame[FrameIndex].movXsilla2 = movXsilla2;
	KeyFrame[FrameIndex].movYsilla2 = movYsilla2;
	KeyFrame[FrameIndex].movZsilla2 = movZsilla2;
	KeyFrame[FrameIndex].movXsilla3 = movXsilla3;
	KeyFrame[FrameIndex].movYsilla3 = movYsilla3;
	KeyFrame[FrameIndex].movZsilla3 = movZsilla3;
	KeyFrame[FrameIndex].movXsilla4 = movXsilla4;
	KeyFrame[FrameIndex].movYsilla4 = movYsilla4;
	KeyFrame[FrameIndex].movZsilla4 = movZsilla4;
	KeyFrame[FrameIndex].movXsilla5 = movXsilla5;
	KeyFrame[FrameIndex].movYsilla5 = movYsilla5;
	KeyFrame[FrameIndex].movZsilla5 = movZsilla5;
	KeyFrame[FrameIndex].movXsilla6 = movXsilla6;
	KeyFrame[FrameIndex].movYsilla6 = movYsilla6;
	KeyFrame[FrameIndex].movZsilla6 = movZsilla6;
	KeyFrame[FrameIndex].movXsilla7 = movXsilla7;
	KeyFrame[FrameIndex].movYsilla7 = movYsilla7;
	KeyFrame[FrameIndex].movZsilla7 = movZsilla7;
	KeyFrame[FrameIndex].movXsilla8 = movXsilla8;
	KeyFrame[FrameIndex].movYsilla8 = movYsilla8;
	KeyFrame[FrameIndex].movZsilla8 = movZsilla8;
	KeyFrame[FrameIndex].movXsilla9 = movXsilla9;
	KeyFrame[FrameIndex].movYsilla9 = movYsilla9;
	KeyFrame[FrameIndex].movZsilla9 = movZsilla9;
	KeyFrame[FrameIndex].movXsilla10 = movXsilla10;
	KeyFrame[FrameIndex].movYsilla10 = movYsilla10;
	KeyFrame[FrameIndex].movZsilla10 = movZsilla10;
	KeyFrame[FrameIndex].movXsilla11 = movXsilla11;
	KeyFrame[FrameIndex].movYsilla11 = movYsilla11;
	KeyFrame[FrameIndex].movZsilla11 = movZsilla11;
	KeyFrame[FrameIndex].movXsilla12 = movXsilla12;
	KeyFrame[FrameIndex].movYsilla12 = movYsilla12;
	KeyFrame[FrameIndex].movZsilla12 = movZsilla12;
	KeyFrame[FrameIndex].movXsilla13 = movXsilla13;
	KeyFrame[FrameIndex].movYsilla13 = movYsilla13;
	KeyFrame[FrameIndex].movZsilla13 = movZsilla13;
	KeyFrame[FrameIndex].movXsilla14 = movXsilla14;
	KeyFrame[FrameIndex].movYsilla14 = movYsilla14;
	KeyFrame[FrameIndex].movZsilla14 = movZsilla14;
	KeyFrame[FrameIndex].movXsilla15 = movXsilla15;
	KeyFrame[FrameIndex].movYsilla15 = movYsilla15;
	KeyFrame[FrameIndex].movZsilla15 = movZsilla15;
	KeyFrame[FrameIndex].movXsilla16 = movXsilla16;
	KeyFrame[FrameIndex].movYsilla16 = movYsilla16;
	KeyFrame[FrameIndex].movZsilla16 = movZsilla16;
	KeyFrame[FrameIndex].movXsilla17 = movXsilla17;
	KeyFrame[FrameIndex].movYsilla17 = movYsilla17;
	KeyFrame[FrameIndex].movZsilla17 = movZsilla17;
	KeyFrame[FrameIndex].movXsilla18 = movXsilla18;
	KeyFrame[FrameIndex].movYsilla18 = movYsilla18;
	KeyFrame[FrameIndex].movZsilla18 = movZsilla18;
	KeyFrame[FrameIndex].movXsilla19 = movXsilla19;
	KeyFrame[FrameIndex].movYsilla19 = movYsilla19;
	KeyFrame[FrameIndex].movZsilla19 = movZsilla19;
	KeyFrame[FrameIndex].movXsilla20 = movXsilla20;
	KeyFrame[FrameIndex].movYsilla20 = movYsilla20;
	KeyFrame[FrameIndex].movZsilla20 = movZsilla20;
	KeyFrame[FrameIndex].movXsilla21 = movXsilla21;
	KeyFrame[FrameIndex].movYsilla21 = movYsilla21;
	KeyFrame[FrameIndex].movZsilla21 = movZsilla21;
	KeyFrame[FrameIndex].movXsilla22 = movXsilla22;
	KeyFrame[FrameIndex].movYsilla22 = movYsilla22;
	KeyFrame[FrameIndex].movZsilla22 = movZsilla22;
	KeyFrame[FrameIndex].movXsilla23 = movXsilla23;
	KeyFrame[FrameIndex].movYsilla23 = movYsilla23;
	KeyFrame[FrameIndex].movZsilla23 = movZsilla23;
	KeyFrame[FrameIndex].movXsilla24 = movXsilla24;
	KeyFrame[FrameIndex].movYsilla24 = movYsilla24;
	KeyFrame[FrameIndex].movZsilla24 = movZsilla24;
	KeyFrame[FrameIndex].giroZsillas = giroZsillas;
	KeyFrame[FrameIndex].scalesillas = scalesillas;
	KeyFrame[FrameIndex].movXmesa1 = movXmesa1;
	KeyFrame[FrameIndex].movYmesa1 = movYmesa1;
	KeyFrame[FrameIndex].movZmesa1 = movZmesa1;
	KeyFrame[FrameIndex].movXmesa2 = movXmesa2;
	KeyFrame[FrameIndex].movYmesa2 = movYmesa2;
	KeyFrame[FrameIndex].movZmesa2 = movZmesa2;
	KeyFrame[FrameIndex].movXmesa3 = movXmesa3;
	KeyFrame[FrameIndex].movYmesa3 = movYmesa3;
	KeyFrame[FrameIndex].movZmesa3 = movZmesa3;
	KeyFrame[FrameIndex].movXmesa4 = movXmesa4;
	KeyFrame[FrameIndex].movYmesa4 = movYmesa4;
	KeyFrame[FrameIndex].movZmesa4 = movZmesa4;
	KeyFrame[FrameIndex].movXmesa5 = movXmesa5;
	KeyFrame[FrameIndex].movYmesa5 = movYmesa5;
	KeyFrame[FrameIndex].movZmesa5 = movZmesa5;
	KeyFrame[FrameIndex].movXmesa6 = movXmesa6;
	KeyFrame[FrameIndex].movYmesa6 = movYmesa6;
	KeyFrame[FrameIndex].movZmesa6 = movZmesa6;
	KeyFrame[FrameIndex].movXmesa7 = movXmesa7;
	KeyFrame[FrameIndex].movYmesa7 = movYmesa7;
	KeyFrame[FrameIndex].movZmesa7 = movZmesa7;
	KeyFrame[FrameIndex].movXmesa8 = movXmesa8;
	KeyFrame[FrameIndex].movYmesa8 = movYmesa8;
	KeyFrame[FrameIndex].movZmesa8 = movZmesa8;
	KeyFrame[FrameIndex].movXmesa9 = movXmesa9;
	KeyFrame[FrameIndex].movYmesa9 = movYmesa9;
	KeyFrame[FrameIndex].movZmesa9 = movZmesa9;
	KeyFrame[FrameIndex].movXmesa10 = movXmesa10;
	KeyFrame[FrameIndex].movYmesa10 = movYmesa10;
	KeyFrame[FrameIndex].movZmesa10 = movZmesa10;
	KeyFrame[FrameIndex].movXmesa11 = movXmesa11;
	KeyFrame[FrameIndex].movYmesa11 = movYmesa11;
	KeyFrame[FrameIndex].movZmesa11 = movZmesa11;
	KeyFrame[FrameIndex].movXmesa12 = movXmesa12;
	KeyFrame[FrameIndex].movYmesa12 = movYmesa12;
	KeyFrame[FrameIndex].movZmesa12 = movZmesa12;
	KeyFrame[FrameIndex].giroZmesas = giroZmesas;
	KeyFrame[FrameIndex].scaleXmesas = scaleXmesas;
	KeyFrame[FrameIndex].scaleYmesas = scaleYmesas;
	KeyFrame[FrameIndex].scaleZmesas = scaleZmesas;
	KeyFrame[FrameIndex].movXdisplay1 = movXdisplay1;
	KeyFrame[FrameIndex].movYdisplay1 = movYdisplay1;
	KeyFrame[FrameIndex].movZdisplay1 = movZdisplay1;
	KeyFrame[FrameIndex].movXdisplay2 = movXdisplay2;
	KeyFrame[FrameIndex].movYdisplay2 = movYdisplay2;
	KeyFrame[FrameIndex].movZdisplay2 = movZdisplay2;
	KeyFrame[FrameIndex].movXdisplay3 = movXdisplay3;
	KeyFrame[FrameIndex].movYdisplay3 = movYdisplay3;
	KeyFrame[FrameIndex].movZdisplay3 = movZdisplay3;
	KeyFrame[FrameIndex].movXdisplay4 = movXdisplay4;
	KeyFrame[FrameIndex].movYdisplay4 = movYdisplay4;
	KeyFrame[FrameIndex].movZdisplay4 = movZdisplay4;
	KeyFrame[FrameIndex].movXdisplay5 = movXdisplay5;
	KeyFrame[FrameIndex].movYdisplay5 = movYdisplay5;
	KeyFrame[FrameIndex].movZdisplay5 = movZdisplay5;
	KeyFrame[FrameIndex].movXdisplay6 = movXdisplay6;
	KeyFrame[FrameIndex].movYdisplay6 = movYdisplay6;
	KeyFrame[FrameIndex].movZdisplay6 = movZdisplay6;
	KeyFrame[FrameIndex].movXdisplay7 = movXdisplay7;
	KeyFrame[FrameIndex].movYdisplay7 = movYdisplay7;
	KeyFrame[FrameIndex].movZdisplay7 = movZdisplay7;
	KeyFrame[FrameIndex].movXdisplay8 = movXdisplay8;
	KeyFrame[FrameIndex].movYdisplay8 = movYdisplay8;
	KeyFrame[FrameIndex].movZdisplay8 = movZdisplay8;
	KeyFrame[FrameIndex].movXdisplay9 = movXdisplay9;
	KeyFrame[FrameIndex].movYdisplay9 = movYdisplay9;
	KeyFrame[FrameIndex].movZdisplay9 = movZdisplay9;
	KeyFrame[FrameIndex].movXdisplay10 = movXdisplay10;
	KeyFrame[FrameIndex].movYdisplay10 = movYdisplay10;
	KeyFrame[FrameIndex].movZdisplay10 = movZdisplay10;
	KeyFrame[FrameIndex].movXdisplay11 = movXdisplay11;
	KeyFrame[FrameIndex].movYdisplay11 = movYdisplay11;
	KeyFrame[FrameIndex].movZdisplay11 = movZdisplay11;
	KeyFrame[FrameIndex].movXdisplay12 = movXdisplay12;
	KeyFrame[FrameIndex].movYdisplay12 = movYdisplay12;
	KeyFrame[FrameIndex].movZdisplay12 = movZdisplay12;
	KeyFrame[FrameIndex].giroZdisplay = giroZdisplay;
	KeyFrame[FrameIndex].scaledisplay = scaledisplay;
	KeyFrame[FrameIndex].movXpccase1 = movXpccase1;
	KeyFrame[FrameIndex].movYpccase1 = movYpccase1;
	KeyFrame[FrameIndex].movZpccase1 = movZpccase1;
	KeyFrame[FrameIndex].movXpccase2 = movXpccase2;
	KeyFrame[FrameIndex].movYpccase2 = movYpccase2;
	KeyFrame[FrameIndex].movZpccase2 = movZpccase2;
	KeyFrame[FrameIndex].movXpccase3 = movXpccase3;
	KeyFrame[FrameIndex].movYpccase3 = movYpccase3;
	KeyFrame[FrameIndex].movZpccase3 = movZpccase3;
	KeyFrame[FrameIndex].movXpccase4 = movXpccase4;
	KeyFrame[FrameIndex].movYpccase4 = movYpccase4;
	KeyFrame[FrameIndex].movZpccase4 = movZpccase4;
	KeyFrame[FrameIndex].movXpccase5 = movXpccase5;
	KeyFrame[FrameIndex].movYpccase5 = movYpccase5;
	KeyFrame[FrameIndex].movZpccase5 = movZpccase5;
	KeyFrame[FrameIndex].movXpccase6 = movXpccase6;
	KeyFrame[FrameIndex].movYpccase6 = movYpccase6;
	KeyFrame[FrameIndex].movZpccase6 = movZpccase6;
	KeyFrame[FrameIndex].movXpccase7 = movXpccase7;
	KeyFrame[FrameIndex].movYpccase7 = movYpccase7;
	KeyFrame[FrameIndex].movZpccase7 = movZpccase7;
	KeyFrame[FrameIndex].movXpccase8 = movXpccase8;
	KeyFrame[FrameIndex].movYpccase8 = movYpccase8;
	KeyFrame[FrameIndex].movZpccase8 = movZpccase8;
	KeyFrame[FrameIndex].movXpccase9 = movXpccase9;
	KeyFrame[FrameIndex].movYpccase9 = movYpccase9;
	KeyFrame[FrameIndex].movZpccase9 = movZpccase9;
	KeyFrame[FrameIndex].movXpccase10 = movXpccase10;
	KeyFrame[FrameIndex].movYpccase10 = movYpccase10;
	KeyFrame[FrameIndex].movZpccase10 = movZpccase10;
	KeyFrame[FrameIndex].movXpccase11 = movXpccase11;
	KeyFrame[FrameIndex].movYpccase11 = movYpccase11;
	KeyFrame[FrameIndex].movZpccase11 = movZpccase11;
	KeyFrame[FrameIndex].movXpccase12 = movXpccase12;
	KeyFrame[FrameIndex].movYpccase12 = movYpccase12;
	KeyFrame[FrameIndex].movZpccase12 = movZpccase12;
	KeyFrame[FrameIndex].giroZpccases = giroZpccases;
	KeyFrame[FrameIndex].scalepccases = scalepccases;

	std::cout << "posX = " << posX << std::endl;
	std::cout << "Giro = " << giroMonito << std::endl;
	//std::cout << "Cabeza = " << giroCabeza << std::endl;
	//std::cout << "Brazo = " << giroBraDer << std::endl;

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
	giropokeball = KeyFrame[0].giropokeball;
	girotapapokeball = KeyFrame[0].girotapapokeball;
	movXsilla1 = KeyFrame[0].movXsilla1;
	movYsilla1 = KeyFrame[0].movYsilla1;
	movZsilla1 = KeyFrame[0].movZsilla1;
	movXsilla2 = KeyFrame[0].movXsilla2;
	movYsilla2 = KeyFrame[0].movYsilla2;
	movZsilla2 = KeyFrame[0].movZsilla2;
	movXsilla3 = KeyFrame[0].movXsilla3;
	movYsilla3 = KeyFrame[0].movYsilla3;
	movZsilla3 = KeyFrame[0].movZsilla3;
	movXsilla4 = KeyFrame[0].movXsilla4;
	movYsilla4 = KeyFrame[0].movYsilla4;
	movZsilla4 = KeyFrame[0].movZsilla4;
	movXsilla5 = KeyFrame[0].movXsilla5;
	movYsilla5 = KeyFrame[0].movYsilla5;
	movZsilla5 = KeyFrame[0].movZsilla5;
	movXsilla6 = KeyFrame[0].movXsilla6;
	movYsilla6 = KeyFrame[0].movYsilla6;
	movZsilla6 = KeyFrame[0].movZsilla6;
	movXsilla7 = KeyFrame[0].movXsilla7;
	movYsilla7 = KeyFrame[0].movYsilla7;
	movZsilla7 = KeyFrame[0].movZsilla7;
	movXsilla8 = KeyFrame[0].movXsilla8;
	movYsilla8 = KeyFrame[0].movYsilla8;
	movZsilla8 = KeyFrame[0].movZsilla8;
	movXsilla9 = KeyFrame[0].movXsilla9;
	movYsilla9 = KeyFrame[0].movYsilla9;
	movZsilla9 = KeyFrame[0].movZsilla9;
	movXsilla10 = KeyFrame[0].movXsilla10;
	movYsilla10 = KeyFrame[0].movYsilla10;
	movZsilla10 = KeyFrame[0].movZsilla10;
	movXsilla11 = KeyFrame[0].movXsilla11;
	movYsilla11 = KeyFrame[0].movYsilla11;
	movZsilla11 = KeyFrame[0].movZsilla11;
	movXsilla12 = KeyFrame[0].movXsilla12;
	movYsilla12 = KeyFrame[0].movYsilla12;
	movZsilla12 = KeyFrame[0].movZsilla12;
	movXsilla13 = KeyFrame[0].movXsilla13;
	movYsilla13 = KeyFrame[0].movYsilla13;
	movZsilla13 = KeyFrame[0].movZsilla13;
	movXsilla14 = KeyFrame[0].movXsilla14;
	movYsilla14 = KeyFrame[0].movYsilla14;
	movZsilla14 = KeyFrame[0].movZsilla14;
	movXsilla15 = KeyFrame[0].movXsilla15;
	movYsilla15 = KeyFrame[0].movYsilla15;
	movZsilla15 = KeyFrame[0].movZsilla15;
	movXsilla16 = KeyFrame[0].movXsilla16;
	movYsilla16 = KeyFrame[0].movYsilla16;
	movZsilla16 = KeyFrame[0].movZsilla16;
	movXsilla17 = KeyFrame[0].movXsilla17;
	movYsilla17 = KeyFrame[0].movYsilla17;
	movZsilla17 = KeyFrame[0].movZsilla17;
	movXsilla18 = KeyFrame[0].movXsilla18;
	movYsilla18 = KeyFrame[0].movYsilla18;
	movZsilla18 = KeyFrame[0].movZsilla18;
	movXsilla19 = KeyFrame[0].movXsilla19;
	movYsilla19 = KeyFrame[0].movYsilla19;
	movZsilla19 = KeyFrame[0].movZsilla19;
	movXsilla20 = KeyFrame[0].movXsilla20;
	movYsilla20 = KeyFrame[0].movYsilla20;
	movZsilla20 = KeyFrame[0].movZsilla20;
	movXsilla21 = KeyFrame[0].movXsilla21;
	movYsilla21 = KeyFrame[0].movYsilla21;
	movZsilla21 = KeyFrame[0].movZsilla21;
	movXsilla22 = KeyFrame[0].movXsilla22;
	movYsilla22 = KeyFrame[0].movYsilla22;
	movZsilla22 = KeyFrame[0].movZsilla22;
	movXsilla23 = KeyFrame[0].movXsilla23;
	movYsilla23 = KeyFrame[0].movYsilla23;
	movZsilla23 = KeyFrame[0].movZsilla23;
	movXsilla24 = KeyFrame[0].movXsilla24;
	movYsilla24 = KeyFrame[0].movYsilla24;
	movZsilla24 = KeyFrame[0].movZsilla24;
	giroZsillas = KeyFrame[0].giroZsillas;
	scalesillas = KeyFrame[0].scalesillas;
	movXmesa1 = KeyFrame[0].movXmesa1;
	movYmesa1 = KeyFrame[0].movYmesa1;
	movZmesa1 = KeyFrame[0].movZmesa1;
	movXmesa2 = KeyFrame[0].movXmesa2;
	movYmesa2 = KeyFrame[0].movYmesa2;
	movZmesa2 = KeyFrame[0].movZmesa2;
	movXmesa3 = KeyFrame[0].movXmesa3;
	movYmesa3 = KeyFrame[0].movYmesa3;
	movZmesa3 = KeyFrame[0].movZmesa3;
	movXmesa4 = KeyFrame[0].movXmesa4;
	movYmesa4 = KeyFrame[0].movYmesa4;
	movZmesa4 = KeyFrame[0].movZmesa4;
	movXmesa5 = KeyFrame[0].movXmesa5;
	movYmesa5 = KeyFrame[0].movYmesa5;
	movZmesa5 = KeyFrame[0].movZmesa5;
	movXmesa6 = KeyFrame[0].movXmesa6;
	movYmesa6 = KeyFrame[0].movYmesa6;
	movZmesa6 = KeyFrame[0].movZmesa6;
	movXmesa7 = KeyFrame[0].movXmesa7;
	movYmesa7 = KeyFrame[0].movYmesa7;
	movZmesa7 = KeyFrame[0].movZmesa7;
	movXmesa8 = KeyFrame[0].movXmesa8;
	movYmesa8 = KeyFrame[0].movYmesa8;
	movZmesa8 = KeyFrame[0].movZmesa8;
	movXmesa9 = KeyFrame[0].movXmesa9;
	movYmesa9 = KeyFrame[0].movYmesa9;
	movZmesa9 = KeyFrame[0].movZmesa9;
	movXmesa10 = KeyFrame[0].movXmesa10;
	movYmesa10 = KeyFrame[0].movYmesa10;
	movZmesa10 = KeyFrame[0].movZmesa10;
	movXmesa11 = KeyFrame[0].movXmesa11;
	movYmesa11 = KeyFrame[0].movYmesa11;
	movZmesa11 = KeyFrame[0].movZmesa11;
	movXmesa12 = KeyFrame[0].movXmesa12;
	movYmesa12 = KeyFrame[0].movYmesa12;
	movZmesa12 = KeyFrame[0].movZmesa12;
	giroZmesas = KeyFrame[0].giroZmesas;
	scaleXmesas = KeyFrame[0].scaleXmesas;
	scaleYmesas = KeyFrame[0].scaleYmesas;
	scaleZmesas = KeyFrame[0].scaleZmesas;
	movXdisplay1 = KeyFrame[0].movXdisplay1;
	movYdisplay1 = KeyFrame[0].movYdisplay1;
	movZdisplay1 = KeyFrame[0].movZdisplay1;
	movXdisplay2 = KeyFrame[0].movXdisplay2;
	movYdisplay2 = KeyFrame[0].movYdisplay2;
	movZdisplay2 = KeyFrame[0].movZdisplay2;
	movXdisplay3 = KeyFrame[0].movXdisplay3;
	movYdisplay3 = KeyFrame[0].movYdisplay3;
	movZdisplay3 = KeyFrame[0].movZdisplay3;
	movXdisplay4 = KeyFrame[0].movXdisplay4;
	movYdisplay4 = KeyFrame[0].movYdisplay4;
	movZdisplay4 = KeyFrame[0].movZdisplay4;
	movXdisplay5 = KeyFrame[0].movXdisplay5;
	movYdisplay5 = KeyFrame[0].movYdisplay5;
	movZdisplay5 = KeyFrame[0].movZdisplay5;
	movXdisplay6 = KeyFrame[0].movXdisplay6;
	movYdisplay6 = KeyFrame[0].movYdisplay6;
	movZdisplay6 = KeyFrame[0].movZdisplay6;
	movXdisplay7 = KeyFrame[0].movXdisplay7;
	movYdisplay7 = KeyFrame[0].movYdisplay7;
	movZdisplay7 = KeyFrame[0].movZdisplay7;
	movXdisplay8 = KeyFrame[0].movXdisplay8;
	movYdisplay8 = KeyFrame[0].movYdisplay8;
	movZdisplay8 = KeyFrame[0].movZdisplay8;
	movXdisplay9 = KeyFrame[0].movXdisplay9;
	movYdisplay9 = KeyFrame[0].movYdisplay9;
	movZdisplay9 = KeyFrame[0].movZdisplay9;
	movXdisplay10 = KeyFrame[0].movXdisplay10;
	movYdisplay10 = KeyFrame[0].movYdisplay10;
	movZdisplay10 = KeyFrame[0].movZdisplay10;
	movXdisplay11 = KeyFrame[0].movXdisplay11;
	movYdisplay11 = KeyFrame[0].movYdisplay11;
	movZdisplay11 = KeyFrame[0].movZdisplay11;
	movXdisplay12 = KeyFrame[0].movXdisplay12;
	movYdisplay12 = KeyFrame[0].movYdisplay12;
	movZdisplay12 = KeyFrame[0].movZdisplay12;
	giroZdisplay = KeyFrame[0].giroZdisplay;
	scaledisplay = KeyFrame[0].scaledisplay;
	movXpccase1 = KeyFrame[0].movXpccase1;
	movYpccase1 = KeyFrame[0].movYpccase1;
	movZpccase1 = KeyFrame[0].movZpccase1;
	movXpccase2 = KeyFrame[0].movXpccase2;
	movYpccase2 = KeyFrame[0].movYpccase2;
	movZpccase2 = KeyFrame[0].movZpccase2;
	movXpccase3 = KeyFrame[0].movXpccase3;
	movYpccase3 = KeyFrame[0].movYpccase3;
	movZpccase3 = KeyFrame[0].movZpccase3;
	movXpccase4 = KeyFrame[0].movXpccase4;
	movYpccase4 = KeyFrame[0].movYpccase4;
	movZpccase4 = KeyFrame[0].movZpccase4;
	movXpccase5 = KeyFrame[0].movXpccase5;
	movYpccase5 = KeyFrame[0].movYpccase5;
	movZpccase5 = KeyFrame[0].movZpccase5;
	movXpccase6 = KeyFrame[0].movXpccase6;
	movYpccase6 = KeyFrame[0].movYpccase6;
	movZpccase6 = KeyFrame[0].movZpccase6;
	movXpccase7 = KeyFrame[0].movXpccase7;
	movYpccase7 = KeyFrame[0].movYpccase7;
	movZpccase7 = KeyFrame[0].movZpccase7;
	movXpccase8 = KeyFrame[0].movXpccase8;
	movYpccase8 = KeyFrame[0].movYpccase8;
	movZpccase8 = KeyFrame[0].movZpccase8;
	movXpccase9 = KeyFrame[0].movXpccase9;
	movYpccase9 = KeyFrame[0].movYpccase9;
	movZpccase9 = KeyFrame[0].movZpccase9;
	movXpccase10 = KeyFrame[0].movXpccase10;
	movYpccase10 = KeyFrame[0].movYpccase10;
	movZpccase10 = KeyFrame[0].movZpccase10;
	movXpccase11 = KeyFrame[0].movXpccase11;
	movYpccase11 = KeyFrame[0].movYpccase11;
	movZpccase11 = KeyFrame[0].movZpccase11;
	movXpccase12 = KeyFrame[0].movXpccase12;
	movYpccase12 = KeyFrame[0].movYpccase12;
	movZpccase12 = KeyFrame[0].movZpccase12;
	giroZpccases = KeyFrame[0].giroZpccases;
	scalepccases = KeyFrame[0].scalepccases;

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

	giropokeballInc = (KeyFrame[playIndex + 1].giropokeball - KeyFrame[playIndex].giropokeball) / i_max_steps;
	girotapapokeballInc = (KeyFrame[playIndex + 1].girotapapokeball - KeyFrame[playIndex].girotapapokeball) / i_max_steps;

	movXsilla1Inc = (KeyFrame[playIndex + 1].movXsilla1 - KeyFrame[playIndex].movXsilla1) / i_max_steps;
	movYsilla1Inc = (KeyFrame[playIndex + 1].movYsilla1 - KeyFrame[playIndex].movYsilla1) / i_max_steps;
	movZsilla1Inc = (KeyFrame[playIndex + 1].movZsilla1 - KeyFrame[playIndex].movZsilla1) / i_max_steps;
	movXsilla2Inc = (KeyFrame[playIndex + 1].movXsilla2 - KeyFrame[playIndex].movXsilla2) / i_max_steps;
	movYsilla2Inc = (KeyFrame[playIndex + 1].movYsilla2 - KeyFrame[playIndex].movYsilla2) / i_max_steps;
	movZsilla2Inc = (KeyFrame[playIndex + 1].movZsilla2 - KeyFrame[playIndex].movZsilla2) / i_max_steps;
	movXsilla3Inc = (KeyFrame[playIndex + 1].movXsilla3 - KeyFrame[playIndex].movXsilla3) / i_max_steps;
	movYsilla3Inc = (KeyFrame[playIndex + 1].movYsilla3 - KeyFrame[playIndex].movYsilla3) / i_max_steps;
	movZsilla3Inc = (KeyFrame[playIndex + 1].movZsilla3 - KeyFrame[playIndex].movZsilla3) / i_max_steps;
	movXsilla4Inc = (KeyFrame[playIndex + 1].movXsilla4 - KeyFrame[playIndex].movXsilla4) / i_max_steps;
	movYsilla4Inc = (KeyFrame[playIndex + 1].movYsilla4 - KeyFrame[playIndex].movYsilla4) / i_max_steps;
	movZsilla4Inc = (KeyFrame[playIndex + 1].movZsilla4 - KeyFrame[playIndex].movZsilla4) / i_max_steps;
	movXsilla5Inc = (KeyFrame[playIndex + 1].movXsilla5 - KeyFrame[playIndex].movXsilla5) / i_max_steps;
	movYsilla5Inc = (KeyFrame[playIndex + 1].movYsilla5 - KeyFrame[playIndex].movYsilla5) / i_max_steps;
	movZsilla5Inc = (KeyFrame[playIndex + 1].movZsilla5 - KeyFrame[playIndex].movZsilla5) / i_max_steps;
	movXsilla6Inc = (KeyFrame[playIndex + 1].movXsilla6 - KeyFrame[playIndex].movXsilla6) / i_max_steps;
	movYsilla6Inc = (KeyFrame[playIndex + 1].movYsilla6 - KeyFrame[playIndex].movYsilla6) / i_max_steps;
	movZsilla6Inc = (KeyFrame[playIndex + 1].movZsilla6 - KeyFrame[playIndex].movZsilla6) / i_max_steps;
	movXsilla7Inc = (KeyFrame[playIndex + 1].movXsilla7 - KeyFrame[playIndex].movXsilla7) / i_max_steps;
	movYsilla7Inc = (KeyFrame[playIndex + 1].movYsilla7 - KeyFrame[playIndex].movYsilla7) / i_max_steps;
	movZsilla7Inc = (KeyFrame[playIndex + 1].movZsilla7 - KeyFrame[playIndex].movZsilla7) / i_max_steps;
	movXsilla8Inc = (KeyFrame[playIndex + 1].movXsilla8 - KeyFrame[playIndex].movXsilla8) / i_max_steps;
	movYsilla8Inc = (KeyFrame[playIndex + 1].movYsilla8 - KeyFrame[playIndex].movYsilla8) / i_max_steps;
	movZsilla8Inc = (KeyFrame[playIndex + 1].movZsilla8 - KeyFrame[playIndex].movZsilla8) / i_max_steps;
	movXsilla9Inc = (KeyFrame[playIndex + 1].movXsilla9 - KeyFrame[playIndex].movXsilla9) / i_max_steps;
	movYsilla9Inc = (KeyFrame[playIndex + 1].movYsilla9 - KeyFrame[playIndex].movYsilla9) / i_max_steps;
	movZsilla9Inc = (KeyFrame[playIndex + 1].movZsilla9 - KeyFrame[playIndex].movZsilla9) / i_max_steps;
	movXsilla10Inc = (KeyFrame[playIndex + 1].movXsilla10 - KeyFrame[playIndex].movXsilla10) / i_max_steps;
	movYsilla10Inc = (KeyFrame[playIndex + 1].movYsilla10 - KeyFrame[playIndex].movYsilla10) / i_max_steps;
	movZsilla10Inc = (KeyFrame[playIndex + 1].movZsilla10 - KeyFrame[playIndex].movZsilla10) / i_max_steps;
	movXsilla11Inc = (KeyFrame[playIndex + 1].movXsilla11 - KeyFrame[playIndex].movXsilla11) / i_max_steps;
	movYsilla11Inc = (KeyFrame[playIndex + 1].movYsilla11 - KeyFrame[playIndex].movYsilla11) / i_max_steps;
	movZsilla11Inc = (KeyFrame[playIndex + 1].movZsilla11 - KeyFrame[playIndex].movZsilla11) / i_max_steps;
	movXsilla12Inc = (KeyFrame[playIndex + 1].movXsilla12 - KeyFrame[playIndex].movXsilla12) / i_max_steps;
	movYsilla12Inc = (KeyFrame[playIndex + 1].movYsilla12 - KeyFrame[playIndex].movYsilla12) / i_max_steps;
	movZsilla12Inc = (KeyFrame[playIndex + 1].movZsilla12 - KeyFrame[playIndex].movZsilla12) / i_max_steps;
	movXsilla13Inc = (KeyFrame[playIndex + 1].movXsilla13 - KeyFrame[playIndex].movXsilla13) / i_max_steps;
	movYsilla13Inc = (KeyFrame[playIndex + 1].movYsilla13 - KeyFrame[playIndex].movYsilla13) / i_max_steps;
	movZsilla13Inc = (KeyFrame[playIndex + 1].movZsilla13 - KeyFrame[playIndex].movZsilla13) / i_max_steps;
	movXsilla14Inc = (KeyFrame[playIndex + 1].movXsilla14 - KeyFrame[playIndex].movXsilla14) / i_max_steps;
	movYsilla14Inc = (KeyFrame[playIndex + 1].movYsilla14 - KeyFrame[playIndex].movYsilla14) / i_max_steps;
	movZsilla14Inc = (KeyFrame[playIndex + 1].movZsilla14 - KeyFrame[playIndex].movZsilla14) / i_max_steps;
	movXsilla15Inc = (KeyFrame[playIndex + 1].movXsilla15 - KeyFrame[playIndex].movXsilla15) / i_max_steps;
	movYsilla15Inc = (KeyFrame[playIndex + 1].movYsilla15 - KeyFrame[playIndex].movYsilla15) / i_max_steps;
	movZsilla15Inc = (KeyFrame[playIndex + 1].movZsilla15 - KeyFrame[playIndex].movZsilla15) / i_max_steps;
	movXsilla16Inc = (KeyFrame[playIndex + 1].movXsilla16 - KeyFrame[playIndex].movXsilla16) / i_max_steps;
	movYsilla16Inc = (KeyFrame[playIndex + 1].movYsilla16 - KeyFrame[playIndex].movYsilla16) / i_max_steps;
	movZsilla16Inc = (KeyFrame[playIndex + 1].movZsilla16 - KeyFrame[playIndex].movZsilla16) / i_max_steps;
	movXsilla17Inc = (KeyFrame[playIndex + 1].movXsilla17 - KeyFrame[playIndex].movXsilla17) / i_max_steps;
	movYsilla17Inc = (KeyFrame[playIndex + 1].movYsilla17 - KeyFrame[playIndex].movYsilla17) / i_max_steps;
	movZsilla17Inc = (KeyFrame[playIndex + 1].movZsilla17 - KeyFrame[playIndex].movZsilla17) / i_max_steps;
	movXsilla18Inc = (KeyFrame[playIndex + 1].movXsilla18 - KeyFrame[playIndex].movXsilla18) / i_max_steps;
	movYsilla18Inc = (KeyFrame[playIndex + 1].movYsilla18 - KeyFrame[playIndex].movYsilla18) / i_max_steps;
	movZsilla18Inc = (KeyFrame[playIndex + 1].movZsilla18 - KeyFrame[playIndex].movZsilla18) / i_max_steps;
	movXsilla19Inc = (KeyFrame[playIndex + 1].movXsilla19 - KeyFrame[playIndex].movXsilla19) / i_max_steps;
	movYsilla19Inc = (KeyFrame[playIndex + 1].movYsilla19 - KeyFrame[playIndex].movYsilla19) / i_max_steps;
	movZsilla19Inc = (KeyFrame[playIndex + 1].movZsilla19 - KeyFrame[playIndex].movZsilla19) / i_max_steps;
	movXsilla20Inc = (KeyFrame[playIndex + 1].movXsilla20 - KeyFrame[playIndex].movXsilla20) / i_max_steps;
	movYsilla20Inc = (KeyFrame[playIndex + 1].movYsilla20 - KeyFrame[playIndex].movYsilla20) / i_max_steps;
	movZsilla20Inc = (KeyFrame[playIndex + 1].movZsilla20 - KeyFrame[playIndex].movZsilla20) / i_max_steps;
	movXsilla21Inc = (KeyFrame[playIndex + 1].movXsilla21 - KeyFrame[playIndex].movXsilla21) / i_max_steps;
	movYsilla21Inc = (KeyFrame[playIndex + 1].movYsilla21 - KeyFrame[playIndex].movYsilla21) / i_max_steps;
	movZsilla21Inc = (KeyFrame[playIndex + 1].movZsilla21 - KeyFrame[playIndex].movZsilla21) / i_max_steps;
	movXsilla22Inc = (KeyFrame[playIndex + 1].movXsilla22 - KeyFrame[playIndex].movXsilla22) / i_max_steps;
	movYsilla22Inc = (KeyFrame[playIndex + 1].movYsilla22 - KeyFrame[playIndex].movYsilla22) / i_max_steps;
	movZsilla22Inc = (KeyFrame[playIndex + 1].movZsilla22 - KeyFrame[playIndex].movZsilla22) / i_max_steps;
	movXsilla23Inc = (KeyFrame[playIndex + 1].movXsilla23 - KeyFrame[playIndex].movXsilla23) / i_max_steps;
	movYsilla23Inc = (KeyFrame[playIndex + 1].movYsilla23 - KeyFrame[playIndex].movYsilla23) / i_max_steps;
	movZsilla23Inc = (KeyFrame[playIndex + 1].movZsilla23 - KeyFrame[playIndex].movZsilla23) / i_max_steps;
	movXsilla24Inc = (KeyFrame[playIndex + 1].movXsilla24 - KeyFrame[playIndex].movXsilla24) / i_max_steps;
	movYsilla24Inc = (KeyFrame[playIndex + 1].movYsilla24 - KeyFrame[playIndex].movYsilla24) / i_max_steps;
	movZsilla24Inc = (KeyFrame[playIndex + 1].movZsilla24 - KeyFrame[playIndex].movZsilla24) / i_max_steps;
	giroZsillasInc = (KeyFrame[playIndex + 1].giroZsillas - KeyFrame[playIndex].giroZsillas) / i_max_steps;
	scalesillasInc = (KeyFrame[playIndex + 1].scalesillas - KeyFrame[playIndex].scalesillas) / i_max_steps;
	movXmesa1Inc = (KeyFrame[playIndex + 1].movXmesa1 - KeyFrame[playIndex].movXmesa1) / i_max_steps;
	movYmesa1Inc = (KeyFrame[playIndex + 1].movYmesa1 - KeyFrame[playIndex].movYmesa1) / i_max_steps;
	movZmesa1Inc = (KeyFrame[playIndex + 1].movZmesa1 - KeyFrame[playIndex].movZmesa1) / i_max_steps;
	movXmesa2Inc = (KeyFrame[playIndex + 1].movXmesa2 - KeyFrame[playIndex].movXmesa2) / i_max_steps;
	movYmesa2Inc = (KeyFrame[playIndex + 1].movYmesa2 - KeyFrame[playIndex].movYmesa2) / i_max_steps;
	movZmesa2Inc = (KeyFrame[playIndex + 1].movZmesa2 - KeyFrame[playIndex].movZmesa2) / i_max_steps;
	movXmesa3Inc = (KeyFrame[playIndex + 1].movXmesa3 - KeyFrame[playIndex].movXmesa3) / i_max_steps;
	movYmesa3Inc = (KeyFrame[playIndex + 1].movYmesa3 - KeyFrame[playIndex].movYmesa3) / i_max_steps;
	movZmesa3Inc = (KeyFrame[playIndex + 1].movZmesa3 - KeyFrame[playIndex].movZmesa3) / i_max_steps;
	movXmesa4Inc = (KeyFrame[playIndex + 1].movXmesa4 - KeyFrame[playIndex].movXmesa4) / i_max_steps;
	movYmesa4Inc = (KeyFrame[playIndex + 1].movYmesa4 - KeyFrame[playIndex].movYmesa4) / i_max_steps;
	movZmesa4Inc = (KeyFrame[playIndex + 1].movZmesa4 - KeyFrame[playIndex].movZmesa4) / i_max_steps;
	movXmesa5Inc = (KeyFrame[playIndex + 1].movXmesa5 - KeyFrame[playIndex].movXmesa5) / i_max_steps;
	movYmesa5Inc = (KeyFrame[playIndex + 1].movYmesa5 - KeyFrame[playIndex].movYmesa5) / i_max_steps;
	movZmesa5Inc = (KeyFrame[playIndex + 1].movZmesa5 - KeyFrame[playIndex].movZmesa5) / i_max_steps;
	movXmesa6Inc = (KeyFrame[playIndex + 1].movXmesa6 - KeyFrame[playIndex].movXmesa6) / i_max_steps;
	movYmesa6Inc = (KeyFrame[playIndex + 1].movYmesa6 - KeyFrame[playIndex].movYmesa6) / i_max_steps;
	movZmesa6Inc = (KeyFrame[playIndex + 1].movZmesa6 - KeyFrame[playIndex].movZmesa6) / i_max_steps;
	movXmesa7Inc = (KeyFrame[playIndex + 1].movXmesa7 - KeyFrame[playIndex].movXmesa7) / i_max_steps;
	movYmesa7Inc = (KeyFrame[playIndex + 1].movYmesa7 - KeyFrame[playIndex].movYmesa7) / i_max_steps;
	movZmesa7Inc = (KeyFrame[playIndex + 1].movZmesa7 - KeyFrame[playIndex].movZmesa7) / i_max_steps;
	movXmesa8Inc = (KeyFrame[playIndex + 1].movXmesa8 - KeyFrame[playIndex].movXmesa8) / i_max_steps;
	movYmesa8Inc = (KeyFrame[playIndex + 1].movYmesa8 - KeyFrame[playIndex].movYmesa8) / i_max_steps;
	movZmesa8Inc = (KeyFrame[playIndex + 1].movZmesa8 - KeyFrame[playIndex].movZmesa8) / i_max_steps;
	movXmesa9Inc = (KeyFrame[playIndex + 1].movXmesa9 - KeyFrame[playIndex].movXmesa9) / i_max_steps;
	movYmesa9Inc = (KeyFrame[playIndex + 1].movYmesa9 - KeyFrame[playIndex].movYmesa9) / i_max_steps;
	movZmesa9Inc = (KeyFrame[playIndex + 1].movZmesa9 - KeyFrame[playIndex].movZmesa9) / i_max_steps;
	movXmesa10Inc = (KeyFrame[playIndex + 1].movXmesa10 - KeyFrame[playIndex].movXmesa10) / i_max_steps;
	movYmesa10Inc = (KeyFrame[playIndex + 1].movYmesa10 - KeyFrame[playIndex].movYmesa10) / i_max_steps;
	movZmesa10Inc = (KeyFrame[playIndex + 1].movZmesa10 - KeyFrame[playIndex].movZmesa10) / i_max_steps;
	movXmesa11Inc = (KeyFrame[playIndex + 1].movXmesa11 - KeyFrame[playIndex].movXmesa11) / i_max_steps;
	movYmesa11Inc = (KeyFrame[playIndex + 1].movYmesa11 - KeyFrame[playIndex].movYmesa11) / i_max_steps;
	movZmesa11Inc = (KeyFrame[playIndex + 1].movZmesa11 - KeyFrame[playIndex].movZmesa11) / i_max_steps;
	movXmesa12Inc = (KeyFrame[playIndex + 1].movXmesa12 - KeyFrame[playIndex].movXmesa12) / i_max_steps;
	movYmesa12Inc = (KeyFrame[playIndex + 1].movYmesa12 - KeyFrame[playIndex].movYmesa12) / i_max_steps;
	movZmesa12Inc = (KeyFrame[playIndex + 1].movZmesa12 - KeyFrame[playIndex].movZmesa12) / i_max_steps;
	giroZmesasInc = (KeyFrame[playIndex + 1].giroZmesas - KeyFrame[playIndex].giroZmesas) / i_max_steps;
	scaleXmesasInc = (KeyFrame[playIndex + 1].scaleXmesas - KeyFrame[playIndex].scaleXmesas) / i_max_steps;
	scaleYmesasInc = (KeyFrame[playIndex + 1].scaleYmesas - KeyFrame[playIndex].scaleYmesas) / i_max_steps;
	scaleZmesasInc = (KeyFrame[playIndex + 1].scaleZmesas - KeyFrame[playIndex].scaleZmesas) / i_max_steps;
	movXdisplay1Inc = (KeyFrame[playIndex + 1].movXdisplay1 - KeyFrame[playIndex].movXdisplay1) / i_max_steps;
	movYdisplay1Inc = (KeyFrame[playIndex + 1].movYdisplay1 - KeyFrame[playIndex].movYdisplay1) / i_max_steps;
	movZdisplay1Inc = (KeyFrame[playIndex + 1].movZdisplay1 - KeyFrame[playIndex].movZdisplay1) / i_max_steps;
	movXdisplay2Inc = (KeyFrame[playIndex + 1].movXdisplay2 - KeyFrame[playIndex].movXdisplay2) / i_max_steps;
	movYdisplay2Inc = (KeyFrame[playIndex + 1].movYdisplay2 - KeyFrame[playIndex].movYdisplay2) / i_max_steps;
	movZdisplay2Inc = (KeyFrame[playIndex + 1].movZdisplay2 - KeyFrame[playIndex].movZdisplay2) / i_max_steps;
	movXdisplay3Inc = (KeyFrame[playIndex + 1].movXdisplay3 - KeyFrame[playIndex].movXdisplay3) / i_max_steps;
	movYdisplay3Inc = (KeyFrame[playIndex + 1].movYdisplay3 - KeyFrame[playIndex].movYdisplay3) / i_max_steps;
	movZdisplay3Inc = (KeyFrame[playIndex + 1].movZdisplay3 - KeyFrame[playIndex].movZdisplay3) / i_max_steps;
	movXdisplay4Inc = (KeyFrame[playIndex + 1].movXdisplay4 - KeyFrame[playIndex].movXdisplay4) / i_max_steps;
	movYdisplay4Inc = (KeyFrame[playIndex + 1].movYdisplay4 - KeyFrame[playIndex].movYdisplay4) / i_max_steps;
	movZdisplay4Inc = (KeyFrame[playIndex + 1].movZdisplay4 - KeyFrame[playIndex].movZdisplay4) / i_max_steps;
	movXdisplay5Inc = (KeyFrame[playIndex + 1].movXdisplay5 - KeyFrame[playIndex].movXdisplay5) / i_max_steps;
	movYdisplay5Inc = (KeyFrame[playIndex + 1].movYdisplay5 - KeyFrame[playIndex].movYdisplay5) / i_max_steps;
	movZdisplay5Inc = (KeyFrame[playIndex + 1].movZdisplay5 - KeyFrame[playIndex].movZdisplay5) / i_max_steps;
	movXdisplay6Inc = (KeyFrame[playIndex + 1].movXdisplay6 - KeyFrame[playIndex].movXdisplay6) / i_max_steps;
	movYdisplay6Inc = (KeyFrame[playIndex + 1].movYdisplay6 - KeyFrame[playIndex].movYdisplay6) / i_max_steps;
	movZdisplay6Inc = (KeyFrame[playIndex + 1].movZdisplay6 - KeyFrame[playIndex].movZdisplay6) / i_max_steps;
	movXdisplay7Inc = (KeyFrame[playIndex + 1].movXdisplay7 - KeyFrame[playIndex].movXdisplay7) / i_max_steps;
	movYdisplay7Inc = (KeyFrame[playIndex + 1].movYdisplay7 - KeyFrame[playIndex].movYdisplay7) / i_max_steps;
	movZdisplay7Inc = (KeyFrame[playIndex + 1].movZdisplay7 - KeyFrame[playIndex].movZdisplay7) / i_max_steps;
	movXdisplay8Inc = (KeyFrame[playIndex + 1].movXdisplay8 - KeyFrame[playIndex].movXdisplay8) / i_max_steps;
	movYdisplay8Inc = (KeyFrame[playIndex + 1].movYdisplay8 - KeyFrame[playIndex].movYdisplay8) / i_max_steps;
	movZdisplay8Inc = (KeyFrame[playIndex + 1].movZdisplay8 - KeyFrame[playIndex].movZdisplay8) / i_max_steps;
	movXdisplay9Inc = (KeyFrame[playIndex + 1].movXdisplay9 - KeyFrame[playIndex].movXdisplay9) / i_max_steps;
	movYdisplay9Inc = (KeyFrame[playIndex + 1].movYdisplay9 - KeyFrame[playIndex].movYdisplay9) / i_max_steps;
	movZdisplay9Inc = (KeyFrame[playIndex + 1].movZdisplay9 - KeyFrame[playIndex].movZdisplay9) / i_max_steps;
	movXdisplay10Inc = (KeyFrame[playIndex + 1].movXdisplay10 - KeyFrame[playIndex].movXdisplay10) / i_max_steps;
	movYdisplay10Inc = (KeyFrame[playIndex + 1].movYdisplay10 - KeyFrame[playIndex].movYdisplay10) / i_max_steps;
	movZdisplay10Inc = (KeyFrame[playIndex + 1].movZdisplay10 - KeyFrame[playIndex].movZdisplay10) / i_max_steps;
	movXdisplay11Inc = (KeyFrame[playIndex + 1].movXdisplay11 - KeyFrame[playIndex].movXdisplay11) / i_max_steps;
	movYdisplay11Inc = (KeyFrame[playIndex + 1].movYdisplay11 - KeyFrame[playIndex].movYdisplay11) / i_max_steps;
	movZdisplay11Inc = (KeyFrame[playIndex + 1].movZdisplay11 - KeyFrame[playIndex].movZdisplay11) / i_max_steps;
	movXdisplay12Inc = (KeyFrame[playIndex + 1].movXdisplay12 - KeyFrame[playIndex].movXdisplay12) / i_max_steps;
	movYdisplay12Inc = (KeyFrame[playIndex + 1].movYdisplay12 - KeyFrame[playIndex].movYdisplay12) / i_max_steps;
	movZdisplay12Inc = (KeyFrame[playIndex + 1].movZdisplay12 - KeyFrame[playIndex].movZdisplay12) / i_max_steps;
	giroZdisplayInc = (KeyFrame[playIndex + 1].giroZdisplay - KeyFrame[playIndex].giroZdisplay) / i_max_steps;
	scaledisplayInc = (KeyFrame[playIndex + 1].scaledisplay - KeyFrame[playIndex].scaledisplay) / i_max_steps;
	movXpccase1Inc = (KeyFrame[playIndex + 1].movXpccase1 - KeyFrame[playIndex].movXpccase1) / i_max_steps;
	movYpccase1Inc = (KeyFrame[playIndex + 1].movYpccase1 - KeyFrame[playIndex].movYpccase1) / i_max_steps;
	movZpccase1Inc = (KeyFrame[playIndex + 1].movZpccase1 - KeyFrame[playIndex].movZpccase1) / i_max_steps;
	movXpccase2Inc = (KeyFrame[playIndex + 1].movXpccase2 - KeyFrame[playIndex].movXpccase2) / i_max_steps;
	movYpccase2Inc = (KeyFrame[playIndex + 1].movYpccase2 - KeyFrame[playIndex].movYpccase2) / i_max_steps;
	movZpccase2Inc = (KeyFrame[playIndex + 1].movZpccase2 - KeyFrame[playIndex].movZpccase2) / i_max_steps;
	movXpccase3Inc = (KeyFrame[playIndex + 1].movXpccase3 - KeyFrame[playIndex].movXpccase3) / i_max_steps;
	movYpccase3Inc = (KeyFrame[playIndex + 1].movYpccase3 - KeyFrame[playIndex].movYpccase3) / i_max_steps;
	movZpccase3Inc = (KeyFrame[playIndex + 1].movZpccase3 - KeyFrame[playIndex].movZpccase3) / i_max_steps;
	movXpccase4Inc = (KeyFrame[playIndex + 1].movXpccase4 - KeyFrame[playIndex].movXpccase4) / i_max_steps;
	movYpccase4Inc = (KeyFrame[playIndex + 1].movYpccase4 - KeyFrame[playIndex].movYpccase4) / i_max_steps;
	movZpccase4Inc = (KeyFrame[playIndex + 1].movZpccase4 - KeyFrame[playIndex].movZpccase4) / i_max_steps;
	movXpccase5Inc = (KeyFrame[playIndex + 1].movXpccase5 - KeyFrame[playIndex].movXpccase5) / i_max_steps;
	movYpccase5Inc = (KeyFrame[playIndex + 1].movYpccase5 - KeyFrame[playIndex].movYpccase5) / i_max_steps;
	movZpccase5Inc = (KeyFrame[playIndex + 1].movZpccase5 - KeyFrame[playIndex].movZpccase5) / i_max_steps;
	movXpccase6Inc = (KeyFrame[playIndex + 1].movXpccase6 - KeyFrame[playIndex].movXpccase6) / i_max_steps;
	movYpccase6Inc = (KeyFrame[playIndex + 1].movYpccase6 - KeyFrame[playIndex].movYpccase6) / i_max_steps;
	movZpccase6Inc = (KeyFrame[playIndex + 1].movZpccase6 - KeyFrame[playIndex].movZpccase6) / i_max_steps;
	movXpccase7Inc = (KeyFrame[playIndex + 1].movXpccase7 - KeyFrame[playIndex].movXpccase7) / i_max_steps;
	movYpccase7Inc = (KeyFrame[playIndex + 1].movYpccase7 - KeyFrame[playIndex].movYpccase7) / i_max_steps;
	movZpccase7Inc = (KeyFrame[playIndex + 1].movZpccase7 - KeyFrame[playIndex].movZpccase7) / i_max_steps;
	movXpccase8Inc = (KeyFrame[playIndex + 1].movXpccase8 - KeyFrame[playIndex].movXpccase8) / i_max_steps;
	movYpccase8Inc = (KeyFrame[playIndex + 1].movYpccase8 - KeyFrame[playIndex].movYpccase8) / i_max_steps;
	movZpccase8Inc = (KeyFrame[playIndex + 1].movZpccase8 - KeyFrame[playIndex].movZpccase8) / i_max_steps;
	movXpccase9Inc = (KeyFrame[playIndex + 1].movXpccase9 - KeyFrame[playIndex].movXpccase9) / i_max_steps;
	movYpccase9Inc = (KeyFrame[playIndex + 1].movYpccase9 - KeyFrame[playIndex].movYpccase9) / i_max_steps;
	movZpccase9Inc = (KeyFrame[playIndex + 1].movZpccase9 - KeyFrame[playIndex].movZpccase9) / i_max_steps;
	movXpccase10Inc = (KeyFrame[playIndex + 1].movXpccase10 - KeyFrame[playIndex].movXpccase10) / i_max_steps;
	movYpccase10Inc = (KeyFrame[playIndex + 1].movYpccase10 - KeyFrame[playIndex].movYpccase10) / i_max_steps;
	movZpccase10Inc = (KeyFrame[playIndex + 1].movZpccase10 - KeyFrame[playIndex].movZpccase10) / i_max_steps;
	movXpccase11Inc = (KeyFrame[playIndex + 1].movXpccase11 - KeyFrame[playIndex].movXpccase11) / i_max_steps;
	movYpccase11Inc = (KeyFrame[playIndex + 1].movYpccase11 - KeyFrame[playIndex].movYpccase11) / i_max_steps;
	movZpccase11Inc = (KeyFrame[playIndex + 1].movZpccase11 - KeyFrame[playIndex].movZpccase11) / i_max_steps;
	movXpccase12Inc = (KeyFrame[playIndex + 1].movXpccase12 - KeyFrame[playIndex].movXpccase12) / i_max_steps;
	movYpccase12Inc = (KeyFrame[playIndex + 1].movYpccase12 - KeyFrame[playIndex].movYpccase12) / i_max_steps;
	movZpccase12Inc = (KeyFrame[playIndex + 1].movZpccase12 - KeyFrame[playIndex].movZpccase12) / i_max_steps;
	giroZpccasesInc = (KeyFrame[playIndex + 1].giroZpccases - KeyFrame[playIndex].giroZpccases) / i_max_steps;
	scalepccasesInc = (KeyFrame[playIndex + 1].scalepccases - KeyFrame[playIndex].scalepccases) / i_max_steps;
}

unsigned int generateTextures(const char* filename, bool alfa, bool isPrimitive) {
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
			giropokeball += giropokeballInc;
			girotapapokeball += girotapapokeballInc;

			movXsilla1 += movXsilla1Inc;
			movYsilla1 += movXsilla1Inc;
			movZsilla1 += movZsilla1Inc;
			movXsilla2 += movXsilla2Inc;
			movYsilla2 += movYsilla2Inc;
			movZsilla2 += movZsilla2Inc;
			movXsilla3 += movXsilla3Inc;
			movYsilla3 += movYsilla3Inc;
			movZsilla3 += movZsilla3Inc;
			movXsilla4 += movXsilla4Inc;
			movYsilla4 += movYsilla4Inc;
			movZsilla4 += movZsilla4Inc;
			movXsilla5 += movXsilla5Inc;
			movYsilla5 += movYsilla5Inc;
			movZsilla5 += movZsilla5Inc;
			movXsilla6 += movXsilla6Inc;
			movYsilla6 += movYsilla6Inc;
			movZsilla6 += movZsilla6Inc;
			movXsilla7 += movXsilla7Inc;
			movYsilla7 += movYsilla7Inc;
			movZsilla7 += movZsilla7Inc;
			movXsilla8 += movXsilla8Inc;
			movYsilla8 += movYsilla8Inc;
			movZsilla8 += movZsilla8Inc;
			movXsilla9 += movXsilla9Inc;
			movYsilla9 += movYsilla9Inc;
			movZsilla9 += movZsilla9Inc;
			movXsilla10 += movXsilla10Inc;
			movYsilla10 += movYsilla10Inc;
			movZsilla10 += movZsilla10Inc;
			movXsilla11 += movXsilla11Inc;
			movYsilla11 += movYsilla11Inc;
			movZsilla11 += movZsilla11Inc;
			movXsilla12 += movXsilla12Inc;
			movYsilla12 += movYsilla12Inc;
			movZsilla12 += movZsilla12Inc;
			movXsilla13 += movXsilla13Inc;
			movYsilla13 += movYsilla13Inc;
			movZsilla13 += movZsilla13Inc;
			movXsilla14 += movXsilla14Inc;
			movYsilla14 += movYsilla14Inc;
			movZsilla14 += movZsilla14Inc;
			movXsilla15 += movXsilla15Inc;
			movYsilla15 += movYsilla15Inc;
			movZsilla15 += movZsilla15Inc;
			movXsilla16 += movXsilla16Inc;
			movYsilla16 += movYsilla16Inc;
			movZsilla16 += movZsilla16Inc;
			movXsilla17 += movXsilla17Inc;
			movYsilla17 += movYsilla17Inc;
			movZsilla17 += movZsilla17Inc;
			movXsilla18 += movXsilla18Inc;
			movYsilla18 += movYsilla18Inc;
			movZsilla18 += movZsilla18Inc;
			movXsilla19 += movXsilla19Inc;
			movYsilla19 += movYsilla19Inc;
			movZsilla19 += movZsilla19Inc;
			movXsilla20 += movXsilla20Inc;
			movYsilla20 += movYsilla20Inc;
			movZsilla20 += movZsilla20Inc;
			movXsilla21 += movXsilla21Inc;
			movYsilla21 += movYsilla21Inc;
			movZsilla21 += movZsilla21Inc;
			movXsilla22 += movXsilla22Inc;
			movYsilla22 += movYsilla22Inc;
			movZsilla22 += movZsilla22Inc;
			movXsilla23 += movXsilla23Inc;
			movYsilla23 += movYsilla23Inc;
			movZsilla23 += movZsilla23Inc;
			movXsilla24 += movXsilla24Inc;
			movYsilla24 += movYsilla24Inc;
			movZsilla24 += movZsilla24Inc;
			giroZsillas += giroZsillasInc;
			scalesillas += scalesillasInc;
			movXmesa1 += movXmesa1Inc;
			movYmesa1 += movYmesa1Inc;
			movZmesa1 += movZmesa1Inc;
			movXmesa2 += movXmesa2Inc;
			movYmesa2 += movYmesa2Inc;
			movZmesa2 += movZmesa2Inc;
			movXmesa3 += movXmesa3Inc;
			movYmesa3 += movYmesa3Inc;
			movZmesa3 += movZmesa3Inc;
			movXmesa4 += movXmesa4Inc;
			movYmesa4 += movYmesa4Inc;
			movZmesa4 += movZmesa4Inc;
			movXmesa5 += movXmesa5Inc;
			movYmesa5 += movYmesa5Inc;
			movZmesa5 += movZmesa5Inc;
			movXmesa6 += movXmesa6Inc;
			movYmesa6 += movYmesa6Inc;
			movZmesa6 += movZmesa6Inc;
			movXmesa7 += movXmesa7Inc;
			movYmesa7 += movYmesa7Inc;
			movZmesa7 += movZmesa7Inc;
			movXmesa8 += movXmesa8Inc;
			movYmesa8 += movYmesa8Inc;
			movZmesa8 += movZmesa8Inc;
			movXmesa9 += movXmesa9Inc;
			movYmesa9 += movYmesa9Inc;
			movZmesa9 += movZmesa9Inc;
			movXmesa10 += movXmesa10Inc;
			movYmesa10 += movYmesa10Inc;
			movZmesa10 += movZmesa10Inc;
			movXmesa11 += movXmesa11Inc;
			movYmesa11 += movYmesa11Inc;
			movZmesa11 += movZmesa11Inc;
			movXmesa12 += movXmesa12Inc;
			movYmesa12 += movYmesa12Inc;
			movZmesa12 += movZmesa12Inc;
			giroZmesas += giroZmesasInc;
			scaleXmesas += scaleXmesasInc;
			scaleYmesas += scaleYmesasInc;
			scaleZmesas += scaleZmesasInc;
			movXdisplay1 += movXdisplay1Inc;
			movYdisplay1 += movYdisplay1Inc;
			movZdisplay1 += movZdisplay1Inc;
			movXdisplay2 += movXdisplay2Inc;
			movYdisplay2 += movYdisplay2Inc;
			movZdisplay2 += movZdisplay2Inc;
			movXdisplay3 += movXdisplay3Inc;
			movYdisplay3 += movYdisplay3Inc;
			movZdisplay3 += movZdisplay3Inc;
			movXdisplay4 += movXdisplay4Inc;
			movYdisplay4 += movYdisplay4Inc;
			movZdisplay4 += movZdisplay4Inc;
			movXdisplay5 += movXdisplay5Inc;
			movYdisplay5 += movYdisplay5Inc;
			movZdisplay5 += movZdisplay5Inc;
			movXdisplay6 += movXdisplay6Inc;
			movYdisplay6 += movYdisplay6Inc;
			movZdisplay6 += movZdisplay6Inc;
			movXdisplay7 += movXdisplay7Inc;
			movYdisplay7 += movYdisplay7Inc;
			movZdisplay7 += movZdisplay7Inc;
			movXdisplay8 += movXdisplay8Inc;
			movYdisplay8 += movYdisplay8Inc;
			movZdisplay8 += movZdisplay8Inc;
			movXdisplay9 += movXdisplay9Inc;
			movYdisplay9 += movYdisplay9Inc;
			movZdisplay9 += movZdisplay9Inc;
			movXdisplay10 += movXdisplay10Inc;
			movYdisplay10 += movYdisplay10Inc;
			movZdisplay10 += movZdisplay10Inc;
			movXdisplay11 += movXdisplay11Inc;
			movYdisplay11 += movYdisplay11Inc;
			movZdisplay11 += movZdisplay11Inc;
			movXdisplay12 += movXdisplay12Inc;
			movYdisplay12 += movYdisplay12Inc;
			movZdisplay12 += movZdisplay12Inc;
			giroZdisplay += giroZdisplayInc;
			scaledisplay += scaledisplayInc;
			movXpccase1 += movXpccase1Inc;
			movYpccase1 += movYpccase1Inc;
			movZpccase1 += movZpccase1Inc;
			movXpccase2 += movXpccase2Inc;
			movYpccase2 += movYpccase2Inc;
			movZpccase2 += movZpccase2Inc;
			movXpccase3 += movXpccase3Inc;
			movYpccase3 += movYpccase3Inc;
			movZpccase3 += movZpccase3Inc;
			movXpccase4 += movXpccase4Inc;
			movYpccase4 += movYpccase4Inc;
			movZpccase4 += movZpccase4Inc;
			movXpccase5 += movXpccase5Inc;
			movYpccase5 += movYpccase5Inc;
			movZpccase5 += movZpccase5Inc;
			movXpccase6 += movXpccase6Inc;
			movYpccase6 += movYpccase6Inc;
			movZpccase6 += movZpccase6Inc;
			movXpccase7 += movXpccase7Inc;
			movYpccase7 += movYpccase7Inc;
			movZpccase7 += movZpccase7Inc;
			movXpccase8 += movXpccase8Inc;
			movYpccase8 += movYpccase8Inc;
			movZpccase8 += movZpccase8Inc;
			movXpccase9 += movXpccase9Inc;
			movYpccase9 += movYpccase9Inc;
			movZpccase9 += movZpccase9Inc;
			movXpccase10 += movXpccase10Inc;
			movYpccase10 += movYpccase10Inc;
			movZpccase10 += movZpccase10Inc;
			movXpccase11 += movXpccase11Inc;
			movYpccase11 += movYpccase11Inc;
			movZpccase11 += movZpccase11Inc;
			movXpccase12 += movXpccase12Inc;
			movYpccase12 += movYpccase12Inc;
			movZpccase12 += movZpccase12Inc;
			giroZpccases += giroZpccasesInc;
			scalepccases += scalepccasesInc;

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacion)
	{
		return;
	}
	if (animacion2) {
		return;
	}
	if (animacion3) {
		return;
	}
	if (animacion4) {
		return;
	}

}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData() {
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
	//Modelo de la Fachada_Q
	Model Fachada_Q("resources/objects/Fachada_Q/Fachada_Q.obj");

	//Modelo del Laboratorio de Cisco
	Model Cisco("resources/objects/Cisco/Cisco.obj");
	Model Pizarron("resources/objects/Pizarron/Pizarron.obj");
	Model Display("resources/objects/Display/Display.obj");
	Model PC_Case("resources/objects/PC_Case/PC_Case.obj");

	//Modelo del Laboratorio de Microsoft
	Model Microsoft("resources/objects/Microsoft/Microsoft.obj");

	//Modelo del Laboratorio de Computacion Grafica
	Model Grafica("resources/objects/Grafica/Grafica.obj");


	//Model BenQ("resources/objects/BenQ/BenQ.obj");
	//Model Table("resources/objects/Table/Table.obj");
	//Model chairminpolycount("resources/objects/chairminpolycount/chairminpolycount.obj");
	Model Desk("resources/objects/Desk/Desk.obj");
	Model Table("resources/objects/Table/Table.obj");
	//Model Pokeball1("resources/objects/Pokeball1/Pokeball1.obj");	modelos de prueba para cargar el modelo
	Model PC_Chair("resources/objects/PC_Chair/PC_Chair.obj");

	Model Base_Labs("resources/objects/Base_Labs/Base_Labs.obj");

	//Modelo para la pokeball
	Model pivote_pokeball("resources/objects/Pokeball/pivote_pokeball.obj");
	Model base_pokeball("resources/objects/Pokeball/base_pokeball.obj");
	Model tapa_pokeball("resources/objects/Pokeball/tapa_pokeball.obj");

	//Modelo para el dron
	Model dron("resources/objects/Dron/Dron.obj");
	Model helice("resources/objects/Dron/Helice.obj");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{	// Frame Index = 0
		KeyFrame[0].posX = 0;
		KeyFrame[0].posY = 0.5;
		KeyFrame[0].posZ = 0;
		KeyFrame[0].giroMonito = 0;

		KeyFrame[1].posX = 0;
		KeyFrame[1].posY = 0.5;
		KeyFrame[1].posZ = 0;
		KeyFrame[1].giroMonito = 360.0f;

		KeyFrame[2].posX = 0.0f;
		KeyFrame[2].posY = 40.0f;
		KeyFrame[2].posZ = 0.0f;
		KeyFrame[2].giroMonito = 720.0f;
		
		KeyFrame[3].posX = 0.0f;
		KeyFrame[3].posY = 40.0f;
		KeyFrame[3].posZ = 0.0f;
		KeyFrame[3].giroMonito = 1080.0f;

		KeyFrame[4].posX = 20.0f;
		KeyFrame[4].posY = 40.0f;
		KeyFrame[4].posZ = 20.0;
		KeyFrame[4].giroMonito = 1440.0f;

		KeyFrame[5].posX = 20.0f;
		KeyFrame[5].posY = 40.0f;
		KeyFrame[5].posZ = 20.0;
		KeyFrame[5].giroMonito = 1800.0f;

		KeyFrame[6].posX = 20.0f;
		KeyFrame[6].posY = 40.0f;
		KeyFrame[6].posZ = -20.0;
		KeyFrame[6].giroMonito = 2160.0f;

		KeyFrame[7].posX = 20.0f;
		KeyFrame[7].posY = 40.0f;
		KeyFrame[7].posZ = -20.0f;
		KeyFrame[7].giroMonito = 2520.0f;

		KeyFrame[8].posX = -20.0f;
		KeyFrame[8].posY = 40.0f;
		KeyFrame[8].posZ = -20.0f;
		KeyFrame[8].giroMonito = 2880.0f;
		
		KeyFrame[9].posX = -20.0f;
		KeyFrame[9].posY = 40.0f;
		KeyFrame[9].posZ = -20.0f;
		KeyFrame[9].giroMonito = 3240.0f;
		
		KeyFrame[10].posX = -20.0f;
		KeyFrame[10].posY = 40.0f;
		KeyFrame[10].posZ = 20.0f;
		KeyFrame[10].giroMonito = 3600.0f;
		
		KeyFrame[11].posX = -20.0f;
		KeyFrame[11].posY = 40.0f;
		KeyFrame[11].posZ = 20.0f;
		KeyFrame[11].giroMonito = 3960.0f;
		
		KeyFrame[12].posX = 0.0f;
		KeyFrame[12].posY = 40.0f;
		KeyFrame[12].posZ = 0.0f;
		KeyFrame[12].giroMonito = 4320.0f;
		
		KeyFrame[13].posX = 0.0f;
		KeyFrame[13].posY = 40.0f;
		KeyFrame[13].posZ = 0.0f;
		KeyFrame[13].giroMonito = 4680.0f;

		KeyFrame[14].posX = 0.0f;
		KeyFrame[14].posY = 0.5f;
		KeyFrame[14].posZ = 0.0f;
		KeyFrame[14].giroMonito = 5040.0f;

	}


		// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection
	//	glm::mat4 TempPecho = glm::mat4(1.0f);

	glm::mat4 Cesped = glm::mat4(1.0f);
	glm::mat4 Piso = glm::mat4(1.0f);
	glm::mat4 Pared = glm::mat4(1.0f);

	glm::mat4 tmpPokeball = glm::mat4(1.0f); // Matriz temporal para hacer la animacion de la pokeball 

	glm::mat4 tmpDron = glm::mat4(1.0f); //Matriz temporal para conectar las helices al cuerpo principal

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

		glBindVertexArray(0);

		staticShader.use();
		staticShader.setMat4("projection", projectionOp);
		staticShader.setMat4("view", viewOp);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(90.0f, 10.0f, 150.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f));	// it's a bit too big for our scene, so scale it down	
		staticShader.setMat4("model", modelOp);
		Fachada_Q.Draw(staticShader);

		//LABORATORIO DE CISCO
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down	
		staticShader.setMat4("model", modelOp);
		Cisco.Draw(staticShader);	//Ubicacion aproximadamente de la puerta es 45,0,-30

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(49.5f, 25.0f, 13.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f));	// it's a bit too big for our scene, so scale it down	
		staticShader.setMat4("model", modelOp);
		Pizarron.Draw(staticShader);

		/*
			Dron
		*/

		tmpDron = modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));
		staticShader.setMat4("model", modelOp);
		dron.Draw(staticShader);

		modelOp = glm::translate(tmpDron, glm::vec3(2.36f, 0.4f, 2.54f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));
		modelOp = glm::rotate(modelOp, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		helice.Draw(staticShader);
		
		modelOp = glm::translate(tmpDron, glm::vec3(2.37f, 0.4f, -2.33f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));
		modelOp = glm::rotate(modelOp, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		helice.Draw(staticShader);
		
		modelOp = glm::translate(tmpDron, glm::vec3(-2.34f, 0.4f, 2.53f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));
		modelOp = glm::rotate(modelOp, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		helice.Draw(staticShader);
		
		modelOp = glm::translate(tmpDron, glm::vec3(-2.34f, 0.4f, -2.33f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f));
		modelOp = glm::rotate(modelOp, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		helice.Draw(staticShader);

		/*
				Sillas de las primera fila primera seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla1, movZsilla1, movYsilla1));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla2, movZsilla1, movYsilla2));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla3, movZsilla1, movYsilla3));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla4, movZsilla1, movYsilla4));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
		*/
		/*
				Mesas de la primera fila primera seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa1, movZmesa1, movYmesa1));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa2, movZmesa2, movYmesa2));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay1, movZdisplay1, movYdisplay1));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay2, movZdisplay2, movYdisplay2));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
*/
		/*
			PC_Case 1.1
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase1, movZpccase1, movYpccase1));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase2, movZpccase2, movYpccase2));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
*/
		/*
			Mouse 1.1
		*/
		

		/*
				Sillas de las primera fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla5, movZsilla5, movYsilla5));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla6, movZsilla6, movYsilla6));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla7, movZsilla7, movYsilla7));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla8, movZsilla8, movYsilla8));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
*/
		/*
				Mesas de la primera fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa3, movZmesa3, movYmesa3));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa4, movZmesa4, movYmesa4));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display 
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay3, movZdisplay3, movYdisplay3));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay4, movZdisplay4, movYdisplay4));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
*/
		/*
			PC_Case 1.2
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase3, movZpccase3, movYpccase3));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase4, movZpccase4, movYpccase4));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
*/
		/*
		Sillas de las segunda fila primera seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla9, movZsilla9, movYsilla9));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla10, movZsilla10, movYsilla10));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla11, movZsilla11, movYsilla11));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla12, movZsilla12, movYsilla12));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
*/
		/*
			Mesas de la segunda fila primera seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa5, movZmesa5, movYmesa5));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa6, movZmesa6, movYmesa6));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display 2.1
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay5, movZdisplay5, movYdisplay5));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay6, movZdisplay6, movYdisplay6));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
*/
		/*
			PC_Case
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase5, movZpccase5, movYpccase5));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase6, movZpccase6, movYpccase6));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
*/
		/*
		Sillas de las segunda fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla13, movZsilla13, movYsilla13));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla14, movZsilla14, movYsilla14));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla15, movZsilla15, movYsilla15));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla16, movZsilla16, movYsilla16));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
*/
		/*
			Mesas de la segunda fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa7, movZmesa7, movYmesa7));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa8, movZmesa8, movYmesa8));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay7, movZdisplay7, movYdisplay7));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay8, movZdisplay8, movYdisplay8));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
*/
		/*
			PC_Case 2.2
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase7, movZpccase7, movYpccase7));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase8, movZpccase8, movYpccase8));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
*/
		/*
			Sillas de las tercera fila primera seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla17, movZsilla17, movYsilla17));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla18, movZsilla18, movYsilla18));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla19, movZsilla19, movYsilla19));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla20, movZsilla20, movYsilla20));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
*/
		/*
			Mesas de la segunda fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa9, movZmesa9, movYmesa9));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleXmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa10, movZmesa10, movYmesa10));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleXmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay9, movZdisplay9, movYdisplay9));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay9, movZdisplay9, movYdisplay9));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
*/
		/*
			PC_Case 3.1
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase9, movZpccase9, movYpccase9));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase10, movZpccase10, movYpccase10));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
*/
		/*
			Sillas de las tercera fila segunda seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla21, movZsilla21, movYsilla21));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla22, movZsilla22, movYsilla22));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXsilla23, movZsilla23, movYsilla23));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 0.0f, -43.0f));
		modelOp = glm::rotate(modelOp, glm::radians(giroZsillas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalesillas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Chair.Draw(staticShader);
*/
		/*
			Mesas de la tercera fila segundaa seccion
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa11, movZmesa11, movYmesa11));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXmesa12, movZmesa12, movYmesa12));
		modelOp = glm::rotate(modelOp, glm::radians(giroZmesas), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaleXmesas, scaleZmesas, scaleYmesas));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Desk.Draw(staticShader);
*/
		/*
			Display
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay11, movZdisplay11, movYdisplay11));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXdisplay12, movZdisplay12, movYdisplay12));
		modelOp = glm::rotate(modelOp, glm::radians(giroZdisplay), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scaledisplay ));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		Display.Draw(staticShader);
		*/
		/*
			PC_Case 3.2 glBindVertexArray(VAO[0]);
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase11, movZpccase11, movYpccase11));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(movXpccase12, movZpccase12, movYpccase12));
		modelOp = glm::rotate(modelOp, glm::radians(giroZpccases), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(scalepccases));	// it's a bit too big for our scene, so scale it down
		staticShader.setMat4("model", modelOp);
		PC_Case.Draw(staticShader);
		

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(160.0f, 0.0f, 50.0f));
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down	
		staticShader.setMat4("model", modelOp);
		Microsoft.Draw(staticShader);
	*/
		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, viewOp, projectionOp, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	//glDeleteVertexArrays(2, VAO);
	//glDeleteBuffers(2, VBO);
	//skybox.Terminate();
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		giroCabeza++;
	if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
		giroCabeza--;
	/*if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		giroBraDer++;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		giroBraDer--;
*/
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

	double xoffset = (xpos - lastX) * 0.3;
	double yoffset = (lastY - ypos) * 0.3; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}