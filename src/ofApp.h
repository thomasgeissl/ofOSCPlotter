#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 8088

class ofApp : public ofBaseApp
{
public:
	ofApp(int port, std::string address, std::string values, std::string scale, std::string offset);
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOscReceiver _receiver;
	int _port;
	std::string _address;
	std::vector<std::string> _types;
	std::vector<float> _scale;
	std::vector<float> _offsets;
	std::vector<ofColor> _colors;
	std::vector<std::vector<float>> _values;
};
