// OpenGL2.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <time.h>
#include "GL\glew.h"
#include "GL\glut.h"
#include "GLFW\glfw3.h"
#include "OpenGL2\Init_Window.h"
#include "OpenGL2\Triangle.h"
#include "OpenGL2\LoadShaders.h"
#include "glm\glm.hpp"
#include "OpenGL2\Transform.h"
#include "OpenGL2\MVP.h"
#include "OpenGL2\Cube.h"
#include "OpenGL2\Color.h"
#include "OpenGL2\Controls.h"
#include "OpenGL2\Draw.h"
#include "OpenGL2\StartingSequence.h"
#include <thread>
#include "OpenGL2\Model.h"
#include "OpenGL2\Line.h"

#include "GA\PopulationHandler.h"
#include "GA\myGraph.h"
#include "GA\myVec3d.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>	

#include <mutex>
#include <thread>

#define popSize 50
#define poolSize 10
#define initStructSize 50
#define connectionsPerNode 5
#define spawnThreshold 100
#define stopGA 100000000
#define timestep 100

#define mutationRate_move 0.05
#define mutationRate_add 0.01
#define mutationRate_remove 0.01

static GLfloat* color_change_buffer[12 * 3 * 3];
vector <float> dataStorage;
void OpenGL();
void GA();
void testGA_withSkelton(vector<Spine> blueprint, int maxIteration);
std::mutex SecurityGuard;


int main() {

	std::thread Graphics(&OpenGL);
	std::thread GeneticThread(&GA);
	
	
	Graphics.join();
	GeneticThread.join();
}



void OpenGL()
{

	Init_Window* window = new Init_Window;
	window->SetGLFWHints(4, 4, 3, GL_TRUE);
	window->CheckInitGLFW();
	GLFWwindow* windowLive = window->SetWindowProperties(1920, 1080, "GENS", NULL, NULL);
	glfwSetInputMode(windowLive, GLFW_STICKY_KEYS, GL_TRUE);
	Model* test_model = new Model();
	Line* target_line = new Line();
	Color* color = new Color();
	Controls* controls = new Controls();
	StartingSequence* startingSequence = new StartingSequence();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("Vertex_Shader.glsl", "Fragment_Shader.glsl");

	GLuint dataStorageBuffer;
	glGenVertexArrays(1, &dataStorageBuffer);
	glBindVertexArray(dataStorageBuffer);

	GLuint lineBuffer;
	glGenVertexArrays(1, &lineBuffer);
	glBindVertexArray(lineBuffer);
	glBufferData(GL_ARRAY_BUFFER, target_line->GetLineSize(), target_line->GetLineData(), GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, color->GetColorSize(), color->GetColorData(), GL_STATIC_DRAW);

	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	MVP* mvp = new MVP;
	GLuint MatrixID = glGetUniformLocation(programID, "mvp");

	glm::mat4 MVPMatrix = mvp->CreateMVPMatrix(45, 1920, 1080);
	GLuint TransformationID = glGetUniformLocation(programID, "transformation");
	glm::mat4 test = glm::mat4(1.0f);
	Transform Transformation;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(programID);

	Transformation.SetPos(glm::vec3(0.0f));
	Transformation.SetRotation(glm::vec3(0.0f));
	Transformation.SetScale(glm::vec3(1.5f));
	glm::mat4 testtrans = Transformation.GetModel();
	
	glm::mat4 oldtrans = glm::mat4(0.0f);

	vector <float> oldstorage = { 0.0f };
	glfwSwapInterval(1);		//Should change the frequency of changing the framebuffer but doesnt do shit

	startingSequence->StartStartingSequence(TransformationID, MatrixID, MVPMatrix, colorbuffer, &color, windowLive, testtrans);

	color->setCustomColor(1.0, 1.0, 1.0, popSize * 2);		//investigate
	mvp->SetViewMatrix(glm::lookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	MVPMatrix = mvp->recalculateMatrix();

	do {
		Transformation.SetPos(glm::vec3(controls->GetzPos(), controls->GetxPos(), controls->GetyPos()));
		Transformation.SetRotation(glm::vec3(controls->GetzRot(), controls->GetyRot(), controls->GetxRot()));
		Transformation.SetScale(glm::vec3(1.0f));
		glm::mat4 trans = Transformation.GetModel();
		SecurityGuard.lock();
		if (oldtrans != trans || oldstorage != dataStorage) {

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			sendMatrixtoGPUUniform(TransformationID, trans);
			sendMatrixtoGPUUniform(MatrixID, MVPMatrix);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, dataStorageBuffer);

			test_model->convertMaxiData(dataStorage);
			glBufferData(GL_ARRAY_BUFFER, test_model->GetSize(), test_model->GetConvertedData(), GL_STATIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_LINE_STRIP, 0, 150);
			glEnable(GL_PROGRAM_POINT_SIZE);
			glDisableVertexAttribArray(0);		

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);						//WORKING TRANSFORMATION TEST WITH AN TRIANGLE THAT IS NOT TRANSFORMED
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glBufferData(GL_ARRAY_BUFFER, target_line->GetLineSize(), target_line->GetLineData(), GL_STATIC_DRAW);
			glDrawArrays(GL_LINES, 0, 2);
			glDisableVertexAttribArray(0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glBufferData(GL_ARRAY_BUFFER, color->GetColorSize(), color->GetColorData(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDisableVertexAttribArray(0);


			glfwSwapBuffers(windowLive);	
		}
		SecurityGuard.unlock();
		oldtrans = trans;
		oldstorage = dataStorage;
		/*
		sendMatrixtoGPUUniform(TransformationID, trans);
		sendMatrixtoGPUUniform(MatrixID, MVPMatrix);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);						//WORKING TRANSFORMATION TEST WITH AN TRIANGLE THAT IS NOT TRANSFORMED
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 4*3);
		glDisableVertexAttribArray(0);	*/

		//cube->fadingProperties();


		/*	sendMatrixtoGPUUniform(TransformationID, trans);
		sendMatrixtoGPUUniform(MatrixID, MVPMatrix);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		//color->fadingColor(Red, Green, Blue);
		glBufferData(GL_ARRAY_BUFFER, color->GetColorSize(), color->GetColorData(), GL_STATIC_DRAW);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDisableVertexAttribArray(0);	*/


		glfwPollEvents();
		controls->CheckControls(windowLive);
	} while (glfwGetKey(windowLive, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(windowLive) == 0);

}

void GA()
{

		srand(static_cast <unsigned> (time(0)));		// init random number generation

		//testGraph();
		//testStructure();
		//testPath();
		//testPath1();
		//testMultiSpine();
		//testBuild();
		//testGA(stopGA);


		//configure skleton
		const int numSpines = 1, numJoints = 2;
		myVec3d skeleton[numSpines][numJoints] = { { myVec3d(0,20,100), myVec3d(1000,10,30) } };
		vector<Spine>blueprint;
		Spine s;
		for (int i = 0; i < numSpines; i++) {
			for (int j = 0; j < numJoints; j++) {
				s.joints.push_back(skeleton[i][j]);
			}
			blueprint.push_back(s);
		}

		testGA_withSkelton(blueprint, stopGA);

	}

	void testGA_withSkelton(vector<Spine>skeleton, int stop) {

		cout << "\nSetup Popualtion:\n -popSize: " << popSize << "\n -initStructSize: " << initStructSize << "\n -connections: " << connectionsPerNode << endl;
		cout << "With Skeleton: " << endl;
		PopulationHandler population(popSize, initStructSize);
		population.setCreationSpace(1000, 1000, 1500);
		population.build(skeleton, initStructSize, connectionsPerNode, spawnThreshold);
		//population.random();
		population.calcFitnessValues();
		population.updateStatistics();

		cout << "\nEnd of population setup:\nStop GA in " << stop << " itreations.\n\nInitValues: ";
		cout << population.toString() << endl;
		cout << "Starting generative process ...\n\n";

		Structure kid1, kid2;
		Structure *parent1, *parent2;

		for (int i = 1; i < stop; i++) {

			population.tournamentSelect(poolSize, &parent1, &parent2);

			//kid1 = parent1->crossover(parent2);
			//kid2 = parent2->crossover(parent1);

			parent1->crossover(&parent2, &kid1, &kid2);

			kid1.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);
			kid2.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);

			kid1.calcFitness();
			kid2.calcFitness();

			population.replace(parent1, parent2, &kid1, &kid2);

			if (i % timestep == 0) {
				population.replaceWorst();
				population.updateStatistics();
				cout << "\rIteration: " << i << "  " << population.toString() << endl;
				cout << population.showPopulation();
				
				SecurityGuard.lock();
				dataStorage = population.getBestStructureData();
				SecurityGuard.unlock();

			}
			else if (i % 10 == 0) cout << "\r" << i % timestep << " of " << timestep << " iterations completed.";
		}

		cout << "\n\nEnd of generative process!" << endl << endl;
		population.updateStatistics();
		cout << "Last Statistics: " << population.toString() << endl << endl;
	}
