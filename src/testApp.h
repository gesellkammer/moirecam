#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"


#define WIDTH 800
#define HEIGHT 600
#define FPS 30
#define PORT 22222

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void saveSettings();
		
		ofVideoGrabber    vidGrabber;
		unsigned char *   videoBuf;
		ofTexture	         videoTexture;
		int camWidth;
		int camHeight;
		int totalPixels;

		ofxOscReceiver receiver;

		float brightness;
		float minBrightness;
		float maxBrightness;
		int flipHorizontal;
         int fullscreen;
		unsigned char alpha;
        ofxXmlSettings settings;
};  
