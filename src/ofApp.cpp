#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//our starting variables
	time = -PI;
	dir = 1;
	slider = 0.7;

	//setup the blur
	blur.setup(ofGetWidth(), ofGetHeight(), 4, .2, 8);

	ofBackground(0);
	ofSetFrameRate(24);

	//setup the Midi Knob
	twister.setup();
	ofAddListener(twister.eventEncoder, this, &ofApp::onEncoderUpdate);

}

//--------------------------------------------------------------
void ofApp::update(){
	//change the framerate from the knob
	ofSetFrameRate(slider*24.0);

	//these are the triggers for when the rotation switches direction
	if (time < -3.669 && time > -3.671) {
		dir = -1;
		time = 3.67;
	}

	if (time > 3.774 && time < 3.776) {
		dir = 1;
		time = -3.775;
	}

	if (time < -4.044 && time > -4.045) {
		dir = -1;
		time = 4.0448;
	}

	twister.update();

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	//draw everything into the blur object
	blur.begin();

	ofBackground(0);

	//move everything to the middle
	ofPushMatrix();
	ofTranslate(800, 600);

	//the very first point is in the middle
	glm::vec2 oldPt = { 0,0 };
	//tick time forward
	time -= 0.0006*dir;
	//print the time variable so we can track incoming positions
	cout << time << endl;

	//the core code - we are actually just making a spiral that has been over-wound until it turns into triangles
	//there are 150 points and each one is connected to the last point with a line
	for(int i = 0; i<150; i++) {

		float angle = (i * time);

		glm::vec2 p1 = oldPt;
		//calculate the polar coordinates for the new point
		float x = i * 3.0*sin(angle);
		float y= i * 3.0*cos(angle);
		glm::vec2 p2 = { x, y};

		ofSetLineWidth(1);
		ofSetColor(255, 250);
		ofDrawLine(p1, p2);
		//store the new point as the old one
		oldPt = p2;
	}
	ofPopMatrix();
	blur.end();

	//add these for a cumulative effect
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	blur.draw();
	blur.draw();
	blur.draw();

}

//--------------------------------------------------------------
void ofApp::onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs & a) {
	//store the incoming midi knob changes
	slider = ofMap(a.value, 0, 127, 0.05, 1.2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//space bar to reset the animation for ease of recording
	if (key == ' ') time = -PI+.001;
}

