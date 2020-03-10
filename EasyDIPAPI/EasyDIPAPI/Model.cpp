#include "Model.h"

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

CModel::CModel()
{
	modl = glm::mat4(1.0f);
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;	
	mScale[0] = mScale[1] = mScale[2] = mScale[3] = 1.0f;
	mRotate = glm::quat(1.0f,0.0f, 0.0f, 0.0f);
	mMColor[0] = mMColor[1] = mMColor[2] = mMColor[3] = 1.0f;
	mMColor[3] = mMColor2[0] = mMColor2[1] = mMColor2[2] = mMColor2[3] = 1.0f;
	mMColor3[0] = mMColor3[1] = mMColor3[2] = mMColor3[3] = 1.0f;
	mBColor[0] = mBColor[1] = mBColor[2] = 1.0f;
	mNFColor[0] = mNFColor[1] = mNFColor[2] = 1.0f; 
	mNVColor[0] = mNVColor[1] = mNVColor[2] = 1.0f;
	disN = 0.6f;
	shininess = 32.0f;

}

CModel::~CModel()
{
}



void CModel::Bind()
{
	glBindVertexArray(VAO);
}

void CModel::DrawP()
{
	if (showPuntos)
	{
	
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(2.0f);
		glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
		glPointSize(1.0f);
	}
}
void CModel::DrawL()
{
	if (showLineas)
	{
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonOffset(4.0f, 4.0f);
		glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
		glDisable(GL_POLYGON_OFFSET_LINE);
	}
}
void CModel::DrawT()
{
	if (showTriangulos)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(8.0f, 8.0f);
		glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}

void CModel::BoundingBox()
{
	
	//glDisable(GL_LIGHTING);
	
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex3f(xMin,yMin, zMax);
		glVertex3f(xMax, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMax);
		glVertex3f(xMax, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMax);
		glVertex3f(xMin, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMax);
		glVertex3f(xMin, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMax);
		glVertex3f(xMin, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMin);
		glVertex3f(xMax, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMin);
		glVertex3f(xMax, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMin);
		glVertex3f(xMax, yMin, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMin);
		glVertex3f(xMax, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMin);
		glVertex3f(xMin, yMin, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMin, zMin);
		glVertex3f(xMin, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMin, zMin);
		glVertex3f(xMin, yMin, zMax);
	glEnd();
	glColor3f(mBColor[0], mBColor[1], mBColor[2]);
	glLineWidth(1);
}

//typeShading CModel::getShading()
//{
//	return shading;
//}

int CModel::getnumVert()
{
	return mNumOfVertices;
}

int CModel::getNumIndex()
{
	return cantidad;
}

bool CModel::getShowBox()
{
	return showbbox;
}

void CModel::setShowBox()
{
	showbbox = !showbbox;
}

bool CModel::getShowPuntos()
{
	return showPuntos;
}

void CModel::setShowPuntos()
{
	showPuntos = !showPuntos;
}

bool CModel::getShowLineas()
{
	return showLineas;
}

void CModel::setShowLineas()
{
	showLineas = !showLineas;
}

bool CModel::getShowTriangulos()
{
	return showTriangulos;
}

void CModel::setShowTriangulos()
{
	showTriangulos = !showTriangulos;
}

void CModel::setBColor(float r, float g, float b)
{
	mBColor[0] = r;
	mBColor[1] = g;
	mBColor[2] = b;
}

void CModel::setMColor(float r, float g, float b, float a)
{
	mMColor[0] = r;
	mMColor[1] = g;
	mMColor[2] = b;
	mMColor[3] = a;
}

void CModel::setMColor2(float r, float g, float b, float a)
{
	mMColor2[0] = r;
	mMColor2[1] = g;
	mMColor2[2] = b;
	mMColor2[3] = a;
}

void CModel::setMColor3(float r, float g, float b, float a)
{
	mMColor3[0] = r;
	mMColor3[1] = g;
	mMColor3[2] = b;
	mMColor3[3] = a;
}

void CModel::setNFColor(float r, float g, float b)
{
	mNFColor[0] = r;
	mNFColor[1] = g;
	mNFColor[2] = b;
}

void CModel::setNVColor(float r, float g, float b)
{
	mNVColor[0] = r;
	mNVColor[1] = g;
	mNVColor[2] = b;
}

void CModel::setshininess(float shini)
{
	shininess = shini;
}

float CModel::getshininess()
{
	return shininess;
}

float* CModel::getBColor()
{
	return mBColor;
}

float* CModel::getMColor()
{
	return mMColor;
}

float* CModel::getMColor2()
{
	return mMColor2;
}

float* CModel::getMColor3()
{
	return mMColor3;
}

float* CModel::getNFColor()
{
	return mNFColor;
}

float* CModel::getNVColor()
{
	return mNVColor;
}

void CModel::setTranslation(glm::vec3 translation)
{
	if (&translation != NULL) 
		mTranslation = translation;
	this->setMatModel();
	
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec4 scale)
{
	if (&scale != NULL)
		mScale = scale;
	this->setMatModel();

}

glm::vec3 CModel::boundingVertex(bool d)
{
	if (d)
	{
		return glm::vec3(xMin, yMin, zMin);
	}
	else
	{
		return glm::vec3(xMax, yMax, zMax);
	}
}

glm::vec3 CModel::getCenter()
{
	return mTranslation;
}

/*glm::vec3 CModel::getRotate()
{
	return mRotate;
}*/

glm::quat CModel::getRotateQ()
{
	//glm::quat quaternion = { 1.0f, mRotate.x,mRotate.y,mRotate.z };
	return mRotate;
}

void CModel::setRotate(glm::vec3 quaternion)
{
	mRotate = quaternion;
	this->setMatRot();
	this->setMatModel();
}

void CModel::setRotateQ(glm::quat quaternion)
{
	mRotate = quaternion;
	//R = mat4_cast(quaternion);
	this->setMatRot();
	this->setMatModel();
}

/*void CModel::setModo(enumModo modo)
{
	
	this->modo = modo;
}

enumModo CModel::getModo()
{
	return modo;
}

//void CModel::setShading(typeShading shading)
//{
//	this->shading = shading;
//}*/

glm::vec4 CModel::getScale()
{
	return mScale;
} 

void CModel::calculateNormals() 
{
	vector<vector<int>> incidences(mNumOfVertices);
	/*glm::vec3 maxbboxh = this->boundingVertex(false);
	glm::vec3 minbboxh = this->boundingVertex(true);
	float maxscaleh = max(max(abs(maxbboxh.x - minbboxh.x), abs(maxbboxh.y - minbboxh.y)), abs(maxbboxh.z - minbboxh.z));
	glm::vec3 auxnc; */
	for (int i = 0; i < mNumOfCaras; i++)
	{
		mCentroideC.push_back(glm::vec3((mVertices[mCaras[i][2]].x + mVertices[mCaras[i][1]].x + mVertices[mCaras[i][0]].x) / 3,
										(mVertices[mCaras[i][2]].y + mVertices[mCaras[i][1]].y + mVertices[mCaras[i][0]].y) / 3,
										(mVertices[mCaras[i][2]].z + mVertices[mCaras[i][1]].z + mVertices[mCaras[i][0]].z) / 3));

		/*auxnc = glm::cross(mVertices[mCaras[i][1]] - mVertices[mCaras[i][0]], mVertices[mCaras[i][2]] - mVertices[mCaras[i][0]]);
		auxnc.x = auxnc.x / maxscaleh;
		auxnc.y = auxnc.y / maxscaleh;
		auxnc.z = auxnc.z / maxscaleh;
		auxnc = glm::normalize(auxnc);
		mNormalesC.push_back(auxnc);*/
		mNormalesC.push_back(glm::normalize(glm::cross(mVertices[mCaras[i][1]]- mVertices[mCaras[i][0]], mVertices[mCaras[i][2]]- mVertices[mCaras[i][0]])));
		//mNormalesC.push_back(glm::cross(mVertices[mCaras[i][2]] - mVertices[mCaras[i][0]], mVertices[mCaras[i][1]] - mVertices[mCaras[i][0]]));
		incidences[mCaras[i][0]].push_back(i);
		incidences[mCaras[i][1]].push_back(i);
		incidences[mCaras[i][2]].push_back(i);
	}
	glm::vec3 auxnorm2;
	glm::vec3 vec0 = glm::vec3(0, 0, 0);
	int cant = 1;
	for (int i = 0; i < incidences.size(); i++)
	{
		auxnorm2.x = vec0.x;
		auxnorm2.y = vec0.y;
		auxnorm2.z = vec0.z;
		for (int j = 0; j < incidences[i].size(); j++)
		{
			auxnorm2.x += mNormalesC[incidences[i][j]].x;
			auxnorm2.y += mNormalesC[incidences[i][j]].y;
			auxnorm2.z += mNormalesC[incidences[i][j]].z;
		}
		if (incidences[i].size() > 0)
		{
			cant = incidences[i].size();
		}
		auxnorm2.x = auxnorm2.x / cant;
		auxnorm2.y = auxnorm2.y / cant;
		auxnorm2.z = auxnorm2.z / cant;
		mNormalesV.push_back(auxnorm2);
		cant = 1;
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (2 * mNumOfVertices + mNumOfCaras), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * mNumOfVertices, &mVertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mNumOfVertices, sizeof(glm::vec3) * mNumOfVertices, &mNormalesV[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (mNumOfVertices + mNumOfVertices) , sizeof(glm::vec3) * mNumOfCaras, &mNormalesC[0]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * cantidad, this->getIndex(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(glm::vec3) * mNumOfVertices));// BUFFER_OFFSET(sizeof(glm::vec3) * mNumOfVertices));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(glm::vec3) * (mNumOfVertices*2)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void CModel::displayNormalsFace()
{

	glPointSize(1.0);
	for (int i = 0; i < mNormalesC.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(mCentroideC[i].x, mCentroideC[i].y, mCentroideC[i].z);
		glVertex3f((mNormalesC[i].x + mCentroideC[i].x) * disN, (mNormalesC[i].y + mCentroideC[i].y) * disN, (mNormalesC[i].z + mCentroideC[i].z) * disN);
		glEnd();
		
		/*glBegin(GL_LINES);
			glVertex3f(mCentroideC[i].x, mCentroideC[i].y, mCentroideC[i].z);
			glVertex3f((-mNormalesC[i].x + mCentroideC[i].x) *disN , (-mNormalesC[i].y + mCentroideC[i].y)*disN, (-mNormalesC[i].z + mCentroideC[i].z)*disN);
		glEnd();*/
	}

	glPointSize(1.0);
}

void CModel::displayNormalsVertex()
{

	glPointSize(1.0);
	for (int i = 0; i < mNormalesV.size(); i++)
	{
		glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((mNormalesV[i].x + mVertices[i].x) * disN, (mNormalesV[i].y + mVertices[i].y) * disN, (mNormalesV[i].z + mVertices[i].z) * disN);
		glEnd();

		/*glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((-mNormalesV[i].x + mVertices[i].x)*disN, (-mNormalesV[i].y + mVertices[i].y)*disN, (-mNormalesV[i].z + mVertices[i].z)*disN);
		glEnd();*/
	}
	glPointSize(1.0);
}

vector<glm::vec3> CModel::getVertices()
{
	return mVertices;
}

vector<vector<unsigned>> CModel::getCaras()
{
	return mCaras;
}

unsigned int* CModel::getIndex() {
	unsigned* indices;
	indices = new unsigned[cantidad];
	int canI = 0;
	for (int i = 0; i < cantidad; i += 3) {
		if (canI < mNumOfCaras) {
			indices[i] = (unsigned int)mCaras[canI][0];
			indices[i + 1] = (unsigned int)mCaras[canI][1];
			indices[i + 2] = (unsigned int)mCaras[canI][2];
			canI++;
		}
	}
	return indices;
}

void CModel::setDisN(float distancia)
{
	disN = distancia;
}

float CModel::getDisN()
{
	return disN;
}

void CModel::setMatRot()
{
	/*glm::vec3 rotacion = this->getRotate();
	glm::mat4 rotXm = glm::rotate(rotacion.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rotYm = glm::rotate(rotacion.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rotZm = glm::rotate(rotacion.z, glm::vec3(0.0, 0.0, 1.0));
	R = rotZm * rotYm * rotXm;*/
	R = mat4_cast(mRotate);
}

void CModel::setMatModel()
{
	glm::vec4 vecScale = this->getScale();
	glm::mat4 S;
	if (vecScale.w != 1.0f)
	{
		S = glm::scale(glm::vec3(vecScale.w, vecScale.w, vecScale.w));
	}
	else {
		S = glm::scale(glm::vec3(vecScale.x, vecScale.y, vecScale.z));
	}

	glm::mat4 T = glm::translate(this->getTranslation());

	modl = T * S * R;
	
}

glm::mat4 CModel::getMatModel()
{
	return modl;
}