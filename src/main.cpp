#include "ofMain.h"
#include "ofApp.h"
#include "ofxCommandLineUtils.h"

int main(int argc, char *argv[])
{
	cxxopts::Options options("ofOSCPlotter", "A simple OSC plotter using openFrameworks");
	options.add_options()
		// ("d,debug", "Enable debugging")
		("p,port", "port", cxxopts::value<int>()->default_value("8000"))
		// address
		("a,address", "address", cxxopts::value<string>()->default_value("/values"))
		// types
		("t,types", "types", cxxopts::value<string>()->default_value("f f f"))
		// ("c,colors", "colors", cxxopts::value<string>()->default_value("f f f"))
		("s,scale", "scale", cxxopts::value<string>()->default_value("1 1 1"))
	// ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"));
		("o,offset", "offset", cxxopts::value<string>()->default_value("0 0 0"));
	auto result = options.parse(argc, argv);

	ofGLWindowSettings settings;
	settings.setSize(800, 450);
	settings.windowMode = OF_WINDOW;

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>(
						 result["p"].as<int>(),
						 result["a"].as<std::string>(),
						 result["t"].as<std::string>(),
						 result["s"].as<std::string>(),
						 result["o"].as<std::string>()));
	ofRunMainLoop();
}
