#pragma once

#include "ofMain.h"
#include "ofxBlur.h"
#include "ofxMidiFighterTwister.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		ofxBlur blur;

		float time;
		int dir;
		float slider;

		ofxMidiFighterTwister twister;
		void onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs &);

		
};
