#include "ofApp.h"

ofApp::ofApp(int port, std::string address, std::string types) : _port(port), _address(address)
{
	auto t = ofSplitString(types, " ");
	ofLogNotice() << t.size();
	_types = t;
}
void ofApp::setup()
{
	ofSetWindowTitle("ofOSCPlotter");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	ofLog() << "listening for osc messages on port " << _port;
	_receiver.setup(_port);
	_values.resize(_types.size());

	// TODO: get colors from cli args
	_colors.push_back(ofColor::red);
	_colors.push_back(ofColor::green);
	_colors.push_back(ofColor::blue);
	_colors.push_back(ofColor::white);
	_colors.push_back(ofColor::purple);
	_colors.push_back(ofColor::orange);
}

void ofApp::update()
{
	while (_receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		_receiver.getNextMessage(m);

		if (m.getAddress() == _address)
		{
			for (auto i = 0; i < _types.size(); i++)
			{
				if (_types[i] == "f")
				{
					_values[i].push_back(m.getArgAsFloat(i));
				}
				else if (_types[i] == "i")
				{
					_values[i].push_back(m.getArgAsInt32(i));
				}
			}
		}
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
	for (auto i = 0; i < _values.size(); i++)
	{
		ofSetColor(_colors[i]);
		for (auto j = 0; j < _values[i].size(); j++)
		{
			ofDrawCircle(j, ofGetHeight() / 2 + _values[i][j], 2);
		}
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