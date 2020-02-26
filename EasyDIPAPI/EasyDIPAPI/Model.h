#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/quaternion.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "glm/gtx/transform.hpp"

using namespace std;

enum enumModo
{
	PUNTOS,
	LINEAS,
	TRIANGULOS
};

enum typeProjection
{
	PERSPECTIVE,
	ORTHOGONAL,
	Element_COUNT
};

//Para tarea 4
/*enum typeShading
{
	FLAT,
	GOURAUD
};*/

class CModel
{
	protected:
		vector<glm::vec3> mVertices;
		vector<glm::vec3> mVerticesNorm;
		unsigned int VBO, VAO, IBO;
		vector<vector<unsigned>> mCaras;
		glm::vec3 mTranslation;
		glm::vec4 mScale;
		glm::vec3 mRotate;
		glm::mat4 modl;
		glm::mat4 R;
		int mNumOfVertices;
		int mNumOfCaras;
		int cantidad;
		float xMin, xMax, yMin, yMax, zMin, zMax, xCen, yCen, zCen,maxVal, disN;
		float mBColor[3] /*Boundin box*/, mMColor[4], mMColor2[4], mMColor3[4], mNFColor[3], mNVColor[3];
		float shininess;
		string tipo;
		bool showPuntos = false, showTriangulos = false, showLineas = false, showbbox = false; //Para el display
		//enumModo modo;
		//typeShading shading;
		vector<glm::vec3> mNormalesC; //Normales Cara
		vector<glm::vec3> mNormalesV; //Normales Vertices
		vector<glm::vec3> mCentroideC; 
	public:
		CModel();
		~CModel();
		void Bind();
		void Draw();
		//virtual bool load(string path) = 0;
		virtual void display();
		void BoundingBox();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		glm::vec4 getScale();
		void calculateNormals();
		void displayNormalsFace();
		void displayNormalsVertex();
		vector<glm::vec3> getVertices();
		vector<vector<unsigned>> getCaras();
		unsigned int* getIndex();
		void setDisN(float distancia);
		float getDisN();
		void setMatRot();
		glm::mat4 getMatRot();
		void setMatModel();
		glm::mat4 getMatModel();
		void setScale(glm::vec4 scale);
		glm::vec3 boundingVertex(bool d);
		glm::vec3 getRotate();
		void setRotate(glm::vec3 quaternion);
		void setModo(enumModo modo);
		enumModo getModo();
		int getnumVert();
		bool getShowBox();
		void setShowBox();
		bool getShowPuntos();
		void setShowPuntos();
		bool getShowLineas();
		void setShowLineas();
		bool getShowTriangulos();
		void setShowTriangulos();
		//void setShading(typeShading shading); //Tarea 4
		//typeShading getShading(); //Tarea 4
		void setBColor(float r, float g, float b);
		void setMColor(float r, float g, float b, float a);
		//void setMColor2(float r, float g, float b, float a); //Tarea 4	
		//void setMColor3(float r, float g, float b, float a); //Tarea 4
		void setNFColor(float r, float g, float b);
		void setNVColor(float r, float g, float b);
		//void setshininess(float shini);

		float * getBColor();
		float * getMColor();
		//float * getMColor2();
		//float * getMColor3();
		float * getNFColor();
		float * getNVColor();
		//float getshininess();

		/*void dImmediate();
		void dDisplayList();
		void dVertexPointer();
		void dVBO();*/
};