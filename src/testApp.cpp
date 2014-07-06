#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);

    camHeight = HEIGHT;
    camWidth  = WIDTH;   // try to grab at this size.
    int fps = FPS;
    brightness = 1.0f;
    alpha = 255;
    minBrightness = 0.2f;
    maxBrightness = 1.0f;
    flipHorizontal = 0;
    fullscreen = 0;
	
    //we can now get back a list of devices. 

	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	int cameraindex = 0;
    
    numdevices = devices.size();
    
    for(unsigned i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName << endl;
		if( !ofIsStringInString(devices[i].deviceName, "Built-in") ) {
            cameraindex = i;
        }
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    current_device_index = cameraindex;
	vidGrabber.setDeviceID(current_device_index);
	vidGrabber.setDesiredFrameRate(fps);
	vidGrabber.initGrabber(camWidth, camHeight);
	
	videoBuf = new unsigned char[camWidth*camHeight*3];
	// videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetFrameRate(fps);
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
    
	cout << "listening for osc messages on port " << PORT << endl;
	receiver.setup(PORT);	

	// totalPixels = camWidth*camHeight*3;
    
    // read settings
    if( ofFile::doesFileExist("settings.xml") ) {
        cout << "settings file found";
        settings.loadFile("settings.xml");
        minBrightness = settings.getValue("minBrightness", 200) / 1000.0f;
        maxBrightness = settings.getValue("maxBrightness", 1000) / 1000.0f;
        cout << "loaded settings: \n";
        cout << "minBrightness: " << int(minBrightness*1000) << endl;
    } else {
        cout << "did not find settings, using default values";
        this->saveSettings();
    }
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.update();
	int br;

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		if(m.getAddress() == "/minbrightness") {
            br = m.getArgAsInt32(0);
			minBrightness = float(br / 1000.0f);
            cout << "setting minBrightness to " << br << "\n";
		} else {
			br = (float)m.getArgAsInt32(0);
			brightness = br / 1000.0f;
			brightness = brightness * (maxBrightness-minBrightness) + minBrightness;
			alpha = brightness * 255;
		}	
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	// ofSetHexColor(0xffffff);
	int h1 = ofGetHeight();
	int w1 = ofGetWidth();
	float ratio = HEIGHT / (float)WIDTH;
	int w = h1 / ratio;
	int x = (w1 - w) * 0.5f;

	ofSetColor(255, 255, 255, alpha);
	if( flipHorizontal == 0) {
		vidGrabber.draw(x, 0, w, h1);
	} else {
        glPushMatrix();
            ofTranslate(w, 0);
            glScalef(-1, 1, 1);
            vidGrabber.draw(-x, 0, w, h1);
        glPopMatrix();
	}
}

int testApp::setSource(int index) {
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    cout << "Number of devices: " << devices.size() << endl;
    if( index > (devices.size() - 1)) {
        index = 0;
    }
    current_device_index = index;
    if( devices[index].bAvailable ) {
        cout << "setting device to: " << index << endl;
        vidGrabber.setDeviceID(index);
        vidGrabber.initGrabber(camWidth, camHeight);
        return 1;
    }
    cout << "could not set device: " << index << endl;
    return 0;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){ vidGrabber.videoSettings(); }
    if (key == 'h') { flipHorizontal = 1 - flipHorizontal; }
    // full screen
    if (key == OF_KEY_F11 || key == 'f') {
        fullscreen = 1 - fullscreen;
        ofToggleFullscreen();
    }
    // this is not working
    /*
    if (key == 'n') {
        cout << "trying to set device to next" << endl;
        this->setSource(current_device_index+1);
    }
    */
}

void testApp::exit() {
    cout << "exiting...\n";
    this->saveSettings();
}

void testApp::saveSettings() {
    cout << "Saving settings\n";
    settings.setValue("minBrightness", int(minBrightness * 1000));
    settings.setValue("maxBrightness", int(maxBrightness * 1000));
    settings.saveFile("settings.xml");
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

