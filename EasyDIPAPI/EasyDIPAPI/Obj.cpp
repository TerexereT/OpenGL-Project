#include "Obj.h"



CObj::CObj()
{
}

CObj::~CObj()
{
}

bool CObj::load(string path)
{
	string v1, v2, v3,v4;
	char * auxv;
	char * vv1;
	int tamV;
	vector<unsigned> caras(3);
	float vx, vy, vz;
	

	vector <string> info;
	string line;

	ifstream in(path, ios::in);
	
	if (!in)
	{
		exit(1);
		return false;
	}
	
	tipo = "OBJ";

	xMin = xMax = 0;
	yMin = yMax = 0;
	zMin = zMax = 0;

	while (getline(in, line))
	{

		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;

			if (v.x <= xMin)
				xMin = v.x;

			if (v.y <= yMin)
				yMin = v.y;

			if (v.z <= zMin)
				zMin = v.z;

			if (v.x >= xMax)
				xMax = v.x;

			if (v.y >= yMax)
				yMax = v.y;

			if (v.z >= zMax)
				zMax = v.z;
			

			mVertices.push_back(v);


		}

		else if ( line.substr(0, 2) == "f " && line.substr(2, 1) !=" " )
		{
		stringstream s(line.substr(2));
		int count = 0;

		while (s >> v1)
		{
			if (count < 2)
			{
				caras[count] = atof(v1.c_str());
				count++;

			}
			else if (count == 2)
			{
				caras[count] = atof(v1.c_str());
				count++;
				caras[0]--; caras[1]--; caras[2]--;
				mCaras.push_back(caras);
				//cout << caras[0] << " " << caras[1] << " " << caras[2] << " " << endl;
			}
			else if (count == 3)
			{
				caras[1] = caras[2];
				caras[2] = atof(v1.c_str());
				caras[2]--;
				mCaras.push_back(caras);
				//cout << caras[0] << " " << caras[1] << " " << caras[2] << " ";

			}

		}
		}

		else if (line.substr(0, 3) == "f  ")
		{
			stringstream s(line.substr(3));
			int count = 0;

			while (s >> v1)
			{
				if(count < 2)
				{
					caras[count] = atof(v1.c_str());
					count++;
					
				}
				else if(count == 2)
				{
					caras[count] = atof(v1.c_str());
					count++;
					caras[0]--; caras[1]--; caras[2]--;
					mCaras.push_back(caras);
				} 
				else if(count == 3)
				{
					//cout << caras[0] << " " << caras[1] << " " << caras[2] << " ";
					caras[1] = caras[2];

					caras[2] = atof(v1.c_str());
					caras[2]--;
					//cout << caras[2] << endl;
					mCaras.push_back(caras);

				}

			}

			//s >> v1;
			//s >> v2;
			//s >> v3;
			//caras[0] = atof(v1.c_str()); caras[1] = atof(v2.c_str()); caras[2] = atof(v3.c_str());
			//caras[0]--; caras[1]--; caras[2]--;
			//mCaras.push_back(caras);


		}

	}

	xCen = (xMax + xMin) / 2.0f;
	yCen = (yMax + yMin) / 2.0f;
	zCen = (zMax + zMin) / 2.0f;
	float auxx, auxy, auxz, auxxx, auxyy, auxzz, xMinA, yMinA, zMinA, xMaxA, yMaxA, zMaxA, xCenA, yCenA, zCenA;
	auxx = abs(xMax);
	auxy = abs(yMax);
	auxz = abs(zMax);
	auxxx = abs(xMin);
	auxyy = abs(yMin);
	auxzz = abs(zMin);
	maxVal = glm::max(glm::max(glm::max(auxx, auxy), glm::max(auxz, auxxx)), glm::max(auxyy, auxzz));
	
	
	xMinA = yMinA = zMinA = xMaxA = yMaxA = zMaxA = xCenA = yCenA = zCenA = 0;
	

	for (int f = 0; f < mVertices.size(); f++)
	{
		glm::vec3 v;
		//Normalizando:
		v.x = (mVertices[f].x - xCen) / maxVal;
		v.y = (mVertices[f].y - yCen) / maxVal;
		v.z = (mVertices[f].z - zCen) / maxVal;

		mVerticesNorm.push_back(v);

		if (v.x <= xMinA)
			xMinA = v.x;

		if (v.y <= yMinA)
			yMinA = v.y;

		if (v.z <= zMinA)
			zMinA = v.z;

		if (v.x >= xMaxA)
			xMaxA = v.x;

		if (v.y >= yMaxA)
			yMaxA = v.y;

		if (v.z >= zMaxA)
			zMaxA = v.z;
		
		v.x = v.y = v.z = 0;
		
	}

	//Para imprimir mVertices
	/*for (size_t i = 0; i < mVertices.size(); i++)
	{
		cout << mVertices[i].x << " " << mVertices[i].y << " " << mVertices[i].z << endl;
	}
	cout << endl; cout << endl;
	for (size_t i = 0; i < mVertices.size(); i++)
	{
		cout << mVerticesNorm[i].x << " " << mVerticesNorm[i].y << " " << mVerticesNorm[i].z << endl;
	}*/


	xCen = (xMaxA + xMinA) / 2.0f;
	yCen = (yMaxA + yMinA) / 2.0f;
	zCen = (zMaxA + zMinA) / 2.0f;
	xMax = xMaxA;
	xMin = xMinA;
	yMax = yMaxA;
	yMin = yMinA;
	zMax = zMaxA;
	zMin = zMinA;
	mVertices = mVerticesNorm;

	

	mNumOfCaras = mCaras.size();
	mNumOfVertices = mVertices.size();
	cantidad = mNumOfCaras * 3;
	in.close();
	return true;
	   
}