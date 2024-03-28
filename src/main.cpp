#include "ofMain.h"
#include "ofApp.h"
#include "ofxCommandLineUtils.h"

int main(int argc, char *argv[])
{
	cxxopts::Options options("ofOSCPlotter", "A simple OSC plotter using openFrameworks");
	options.add_options()
	// ("d,debug", "Enable debugging")
	("p,port", "port", cxxopts::value<int>()->default_value("8000")) 
	("a,address", "address", cxxopts::value<string>()->default_value("/values"))
	;
		// ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"));
	auto result = options.parse(argc, argv);

	ofLogNotice("port") << result["p"].as<int>();
	ofLogNotice("address") << result["a"].as<string>();

	ofGLWindowSettings settings;
	settings.setSize(640, 480);
	settings.windowMode = OF_WINDOW; // can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>(
		result["p"].as<int>(),
		result["a"].as<std::string>()
		));
	ofRunMainLoop();
}
