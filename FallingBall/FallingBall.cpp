// Simulation draft
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Vector.h"
#include "../ForceModelLib/include/ForceModel.h" // I don't know why ' #include "ForceModel.h" ' generates error!!!

using namespace std;

int main(int argc, char **argv){
//Particle particle;

	// Coordinate system
	vector <double> origin(3,0);
	vector <double> xVersor(3,0);
	vector <double> yVersor(3,0);
	vector <double> zVersor(3,0);
	xVersor[0] = yVersor[1] = zVersor[2] = 1;
	
	// Initialize gravity
	vector <double> gravity;
	gravity.resize(3);
	double G[3] = {0, -9.81, 0};
	for(unsigned i = 0; i<3; ++i){
		gravity[i] = G[i];
	}
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 1;
	double finalTime = 100;
	
	// Initialize particle
	vector < vector <double> > particlePosition;
	particlePosition.resize(3);
	for(unsigned i = 0 ; i < 3 ; ++i ){
		particlePosition[i].resize(3, 0);
	}
	
	// Output
	ofstream outFile;
	outFile.open("output.txt");
	
	// Simulation
	outFile << "Particle 1\n";
	outFile << "\tPosition\n";
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particlePosition[2] = gravity;
		particlePosition = ForceModel::taylorPredictor( particlePosition, 2, timeStep );
		
		// Saving to file
		outFile << "\t\t" << t << "\n";
		// Prints every derivative of particlePosition
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			outFile << "\t\t";
			
			// Saves each component of the i-th derivative of the position
			for(unsigned j = 0 ; j < 3 ; ++j){
				outFile << "\t" << particlePosition[i][j];
			}
			
			outFile << "\n";
		}
		outFile << "\n";
	}
	
	// Test
	cout << "\nOrigin:" << endl;
	for( vector <double>::iterator k = origin.begin() ; k != origin.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nX:" << endl;
	for( vector <double>::iterator k = xVersor.begin() ; k != xVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nY:" << endl;
	for( vector <double>::iterator k = yVersor.begin() ; k != yVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nZ:" << endl;
	for( vector <double>::iterator k = zVersor.begin() ; k != zVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nGravity:" << endl;
	for(unsigned i = 0; i<3; ++i){
		cout << gravity[i] << endl;
	}
	
	
	outFile.close();
	
	cout << endl << "Success" << endl << endl;
	system("pause");	
	
}

