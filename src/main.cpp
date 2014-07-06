#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
	int camHeight = HEIGHT;
	int camWidth = WIDTH;
	ofSetupOpenGL(camWidth,camHeight, OF_WINDOW);			// <-------- setup the GL context
	//ofSetupOpenGL(camWidth,camHeight, OF_GAME_MODE);			// <-------- setup the GL context


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
