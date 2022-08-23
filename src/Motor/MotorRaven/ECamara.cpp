
#include "ECamara.hpp"
//#include "RShader.hpp"

// GLM library
#include "gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <iostream>

ECamara::ECamara (bool perspectiva ,float izq, float der, float inf, float sup, float cerc, float lej)
: esPerspectiva(perspectiva), izquierda(izq), derecha(der), inferior(inf), superior(sup), cercano(cerc), lejano(lej) 
{
	if(perspectiva)
		matrizProyeccion = glm::frustum(izquierda, derecha, inferior, superior, cercano, lejano); // o glm::perspective
	else
		matrizProyeccion = glm::ortho(izquierda, derecha, inferior, superior, cercano, lejano);
}

ECamara::~ECamara () {}

void ECamara::setPerspectiva(float izq, float der, float inf, float sup, float cerc, float lej){
	izquierda = izq;
	derecha = der;
	inferior = inf;
	superior = sup;
	cercano = cerc;
	lejano = lej;
	esPerspectiva = true;
	matrizProyeccion = glm::frustum(izquierda, derecha, inferior, superior, cercano, lejano); // o glm::perspective
}

void ECamara::setParalela(float izq, float der, float inf, float sup, float cerc, float lej) {
	izquierda = izq;
	derecha = der;
	inferior = inf;
	superior = sup;
	cercano = cerc;
	lejano = lej;
	esPerspectiva = false;
	matrizProyeccion = glm::ortho(izquierda, derecha, inferior, superior, cercano, lejano);
}

glm::mat4x4 ECamara::getMatrizProyeccion () {
	return matrizProyeccion;
}

bool ECamara::getPerspectiva () {
	return esPerspectiva;
}

void ECamara::setIzquierda (float izq){
	izquierda = izq;
}

float ECamara::getIzquierda () {
	return izquierda;
}

void ECamara::setDerecha (float der) {
	derecha = der;
}

float ECamara::getDerecha () {
	return derecha;
}

void ECamara::setInferior (float inf) {
	inferior = inf;
}

float ECamara::getInferior () {
	return inferior;
}

void ECamara::setSuperior (float sup) {
	superior = sup;
}

float ECamara::getSuperior () {
	return superior;
}

void ECamara::setCercano (float cerc) {
	cercano = cerc;
}

float ECamara::getCercano () {
	return cercano;
}

void ECamara::setLejano (float lej) {
	lejano = lej;
}

float ECamara::getLejano () {
	return lejano;
}

void ECamara::setCameraTarget(glm::vec3 pos) {
	cameraTarget = pos;
}

void ECamara::setCameraUp(glm::vec3 pos) {
	cameraUp = pos;
}

glm::vec3 ECamara::getCameraTarget() {
	return cameraTarget;
}

glm::vec3 ECamara::getCameraUp() {
	return cameraUp;
}

void ECamara::dibujar(glm::mat4x4 mat, unsigned int shader) {
	/*//std::cout << "Entro al dibujar de entidad cámara" << std::endl;
	int projec = glGetUniformLocation(shader, "projection");
	//std::cout << "Int matriz projection = " << projec << std::endl;
	glUniformMatrix4fv(projec, 1, GL_FALSE, glm::value_ptr(matrizProyeccion));


	int vist = glGetUniformLocation(shader, "view");
	//std::cout << "Int matriz view = " << vist << std::endl;
	glUniformMatrix4fv(vist, 1, GL_FALSE, glm::value_ptr(glm::inverse(mat)));*/
}
