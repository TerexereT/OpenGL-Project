#include "Model.h"

unsigned int CModel::VBO = 0;
unsigned int CModel::VAO = 0;


CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;	
	mScale[0] = mScale[1] = mScale[2] = mScale[3] = 1.0f;
	mRotate = glm::vec3(0.0f, 0.0f, 0.0f);
	//modo = PUNTOS;
	mMColor[0] = mMColor[1] = mMColor[2] = mMColor[3] = 1.0f;
	//mMColor[3] = mMColor2[0] = mMColor2[1] = mMColor2[2] = mMColor2[3] = 1.0f;
	//mMColor3[0] = mMColor3[1] = mMColor3[2] = mMColor3[3] = 1.0f;
	mBColor[0] = mBColor[1] = mBColor[2] = 1.0f;
	mNFColor[0] = mNFColor[1] = mNFColor[2] = 1.0f; 
	mNVColor[0] = mNVColor[1] = mNVColor[2] = 1.0f;
	disN = 0.6f;
	//shininess = 20.0f;

	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/

}

CModel::~CModel()
{
}



void CModel::Bind()
{
	
}

void CModel::Draw()
{
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

void CModel::display()
{
	
	//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);

	if (showPuntos)
	{
		glDisable(GL_LIGHTING);
		//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	}
	if (showLineas)
	{
		//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonOffset();
	}
	
	if (showTriangulos)
	{
		//glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	}


//------------------------------------------------------------------//
	if (showbbox)
	{
		this->BoundingBox();
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

/*void CModel::setMColor2(float r, float g, float b, float a)
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
}*/

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

/*void CModel::setshininess(float shini)
{
	shininess = shini;
}

float CModel::getshininess()
{
	return shininess;
}*/

float* CModel::getBColor()
{
	return mBColor;
}

float* CModel::getMColor()
{
	return mMColor;
}

/*float* CModel::getMColor2()
{
	return mMColor2;
}

float* CModel::getMColor3()
{
	return mMColor3;
}*/

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
	
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec4 scale)
{
	if (&scale != NULL)
		mScale = scale;

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

glm::vec3 CModel::getRotate()
{
	return mRotate;
}

void CModel::setRotate(glm::vec3 quaternion)
{
	mRotate = quaternion;
}

/*void CModel::setModo(enumModo modo)
{
	
	this->modo = modo;
}

enumModo CModel::getModo()
{
	return modo;
}*/

//void CModel::setShading(typeShading shading)
//{
//	this->shading = shading;
//}

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
}

void CModel::displayNormalsFace()
{

	//glDisable(GL_LIGHTING);
	glColor3f(mNFColor[0], mNFColor[1], mNFColor[2]);
	glPointSize(1.0);



	for (int i = 0; i < mNormalesC.size(); i++)
	{
		glBegin(GL_LINES);
			glVertex3f(mCentroideC[i].x, mCentroideC[i].y, mCentroideC[i].z);
			glVertex3f((-mNormalesC[i].x + mCentroideC[i].x) *disN , (-mNormalesC[i].y + mCentroideC[i].y)*disN, (-mNormalesC[i].z + mCentroideC[i].z)*disN);
		glEnd();
	}

	glPointSize(1.0);
}

void CModel::displayNormalsVertex()
{
	//glDisable(GL_LIGHTING);
	glColor3f(mNVColor[0], mNVColor[1], mNVColor[2]);
	glPointSize(1.0);
	for (int i = 0; i < mNormalesV.size(); i++)
	{
		/*glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((mNormalesV[i].x + mVertices[i].x), (mNormalesV[i].y + mVertices[i].y), (mNormalesV[i].z + mVertices[i].z));
		glEnd();*/

		glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((-mNormalesV[i].x + mVertices[i].x)*disN, (-mNormalesV[i].y + mVertices[i].y)*disN, (-mNormalesV[i].z + mVertices[i].z)*disN);
		glEnd();
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

unsigned* CModel::getIndex() {
	unsigned* indices;
	int cantidad = mNumOfCaras * 3;
	indices = new unsigned[cantidad];
	int canI = 0;
	for (int i = 0; i < cantidad; i += 3) {
		//cout << "en el arreglo: "<<i << endl;
		if (canI < mNumOfCaras) {
			indices[i] = (unsigned)mCaras[canI][0];
			indices[i + 1] = (unsigned)mCaras[canI][1];
			indices[i + 2] = (unsigned)mCaras[canI][2];
			canI++;
			//cout <<"en el indice: "<< canI << endl;
			//cout << indices[i] << " " << indices[i + 1] << " " << indices[i + 2] << endl;
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