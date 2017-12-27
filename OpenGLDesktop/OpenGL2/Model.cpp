#include "Model.h"

Model::Model()
{
	static GLfloat  standard_model[] = {
		-1.0f,-1.0f,-1.0f
	};
	GLfloat *data = standard_model;
	this->m_modelData = data;
	this->m_modelSize = sizeof(standard_model);
	printf("");


}

GLuint Model::Init_Model(GLfloat * m_modelData)
{
	return 0;
}

void Model::convertMaxiData(vector <float> maxiVector)
{
	static GLfloat convertedData[201] = { 0.0f };		//ACHTUNG DAS IST NUR EIN TEST!!! KEINE CONST VALUES
	for (int i = 0; i < maxiVector.size(); i++) {
				
		convertedData[i] = ((maxiVector.at(i) - 0) / (1000 - 0)) * (1 - (-1)) + (-1);
		
	}
			/*			if (isnan(maxiVector[i].getComp(j))) conData[i * 3 + j] = 0.0f;
			if (maxiVector[i].getComp(j) > 1000.0f) conData[i * 3 + j] = 1000.0f;
			if (maxiVector[i].getComp(j) < -1000.0f) conData[i * 3 + j] = -1.0f;		*/

	
	GLfloat* data1 = convertedData;
	//GLfloat testCopy = conData;
	this->m_modelSize = sizeof(convertedData);
	this->m_convertedModelData = data1;
}
