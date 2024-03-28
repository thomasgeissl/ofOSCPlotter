#include "ofApp.h"

ofApp::ofApp(int port, std::string address) : _port(port), _address(address)
{
}
void ofApp::setup()
{
	ofSetWindowTitle("ofOSCPlotter");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	// listen on the given port
	ofLog() << "listening for osc messages on port " << _port;
	_receiver.setup(_port);
	_values.resize(3);
}

void ofApp::update()
{
	while (_receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		_receiver.getNextMessage(m);

		if (m.getAddress() == _address)
		{
			_values[0].push_back(m.getArgAsFloat(0));
			_values[1].push_back(m.getArgAsFloat(1));
			_values[2].push_back(m.getArgAsFloat(2));
		}
		// if (m.getAddress() == "/bno/orientation")
		// {
		// 	_values[0].push_back(m.getArgAsFloat(0));
		// 	_values[1].push_back(m.getArgAsFloat(1));
		// 	_values[2].push_back(m.getArgAsFloat(2));
		// }
	}

	while (_values[0].size() > ofGetWidth())
	{
		for (auto i = 0; i < _values.size(); i++)
		{
			_values[i].erase(_values[i].begin());
		}
	}
}

void ofApp::draw()
{
	ofBackground(0);
	for (auto i = 0; _values.size() > 2 && i < _values[0].size(); i++)
	{
		ofSetColor(ofColor::red);
		ofDrawCircle(i, ofGetHeight() / 2 + _values[0][i], 2);
		ofSetColor(ofColor::green);
		ofDrawCircle(i, ofGetHeight() / 2 + _values[1][i], 2);
		ofSetColor(ofColor::blue);
		ofDrawCircle(i, ofGetHeight() / 2 + _values[2][i] - 9.8, 2);
	}
}
void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}