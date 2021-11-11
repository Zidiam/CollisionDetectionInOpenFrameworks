#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
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

	ofxAssimpModelLoader spaceship, asteroid;

	ofMesh spaceship_mesh, asteroid_mesh;
	ofLight	light;

	ofNode meshNode;

	//Camera
	ofEasyCam cam;

	//Distance
	glm::vec3 nearestVertex1, nearestVertex2, spaceshipCoords, asteroidCoords;

	//GUI
	ofxPanel gui;

	ofxButton button1;

	ofxLabel label1, label2, label3, label4, label5, label6;

	ofxIntSlider intSlider1;

	ofxToggle toggle1, toggle2;

	ofxVec3Slider vec3Slider1, vec3Slider2;
};

#endif
