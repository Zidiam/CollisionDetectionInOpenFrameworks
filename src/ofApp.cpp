#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 0);

	ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

	//Model Setup
	spaceship.loadModel("spaceship/Feisar_Ship.3DS", true);
	spaceship.setScale(.68, .68, .68);
	spaceship.setRotation(2, 90, 1, 0, 0);
	spaceship.setRotation(0, 180, 0, 0, 1);

	asteroid.loadModel("asteroid/asteroid.obj", true);
	asteroid.setPosition(200, 0, 0);
	asteroid.setScale(.21, .21, .21);
	asteroid.setRotation(2, 180, 1, 0, 0);
	asteroid.setRotation(0, 180, 0, 1, 0);

	spaceshipCoords = spaceship.getPosition();
	asteroidCoords = asteroid.getPosition();
	
	//GUI Setup
	gui.setup();
	gui.setDefaultBackgroundColor(ofColor(255, 255, 255));
	gui.add(label1.setup("", "Model Manipulation:"));
	gui.add(intSlider1.setup("Percent Check:", 100, 1, 100));
	gui.add(vec3Slider1.setup("Spaceship Position", spaceshipCoords, ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	gui.add(vec3Slider2.setup("Asteroid Position", asteroidCoords, ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	gui.add(button1.setup("Press for distance"));
	gui.add(toggle1.setup("Constant Distance Calculating", false));
	gui.add(toggle2.setup("Draw Model's Faces", true));
	gui.add(label3.setup("Colliding", ofToString(false)));
	gui.add(label4.setup("Distance", "N/A"));
	gui.add(label2.setup("", "Vertex1 and Vertex2:"));
	gui.add(label5.setup("", ofToString(nearestVertex1)));
	gui.add(label6.setup("", ofToString(nearestVertex2)));
}

//--------------------------------------------------------------
void ofApp::update() {
	if (button1 || toggle1) {
		glm::vec3 midpoint((spaceship.getPosition().x + asteroid.getPosition().x) / 2, (spaceship.getPosition().y + asteroid.getPosition().y) / 2, (spaceship.getPosition().z + asteroid.getPosition().z) / 2);

		int n = spaceship_mesh.getNumVertices();
		int n2 = asteroid_mesh.getNumVertices();
		float nearestDistance = 0;

		int nearestIndex = 0;
		float distance;
		glm::vec3 cur, cur2;
		int val, val2;
		val = val2 = 0;
		if (intSlider1 != 100) {
			val = n / (intSlider1);
			val2 = n2 / (intSlider1);
		}
		for (int i = 0; i < n; i += 1+ val) {
			for (int z = 0; z < n2; z += 1+ val2) {
				cur = spaceship_mesh.getVertex(i);
				cur2 = asteroid_mesh.getVertex(z);
				distance = glm::distance(cur, cur2);
				if (i == 0 || distance < nearestDistance) {
					nearestDistance = distance;
					nearestVertex1 = cur;
					nearestVertex2 = cur2;
					nearestIndex = i;
				}
			}
		}

		ofSetColor(ofColor::red);
		ofDrawLine(nearestVertex1, nearestVertex2);

		ofNoFill();
		ofSetColor(ofColor::yellow);
		ofSetLineWidth(2);
		ofDrawCircle(nearestVertex1, 4);
		ofDrawCircle(nearestVertex2, 4);
		ofSetLineWidth(1);

		glm::vec2 offset(10, -10);
		ofDrawBitmapStringHighlight(ofToString(nearestIndex), midpoint + offset);

		int realdistance = (abs(abs(nearestVertex1.x) - abs(nearestVertex2.x)) + abs(abs(nearestVertex1.y) - abs(nearestVertex2.y)) + abs(abs(nearestVertex1.z) - abs(nearestVertex2.z))) / 3;

		if (realdistance <= 3) {
			label3 = "true";
		}
		else {
			label3 = "false";
		}
		label4 = ofToString(realdistance);
		label5 = ofToString(nearestVertex1);
		label6 = ofToString(nearestVertex2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor(64), ofColor(0));

	//GUI Lighting
	ofEnableLighting();
	light.enable();
	ofDisableLighting();

	ofSetColor(255, 255, 255);
	ofDisableDepthTest();
	gui.draw();
	ofEnableDepthTest();

	ofSetColor(255);

	spaceship_mesh = spaceship.getCurrentAnimatedMesh(0);
	asteroid_mesh = asteroid.getCurrentAnimatedMesh(0);
	cam.begin();

	int z = spaceship_mesh.getNumVertices();
	for (int i = 0; i < z; i++) {
		spaceship_mesh.setVertex(i, ofDefaultVertexType(spaceship_mesh.getVertex(i).x + vec3Slider1->x, spaceship_mesh.getVertex(i).y + vec3Slider1->y, spaceship_mesh.getVertex(i).z + vec3Slider1->z));
	}

	z = asteroid_mesh.getNumVertices();
	for (int i = 0; i < z; i++) {
		asteroid_mesh.setVertex(i, ofDefaultVertexType(asteroid_mesh.getVertex(i).x + vec3Slider2->x, asteroid_mesh.getVertex(i).y + vec3Slider2->y, asteroid_mesh.getVertex(i).z + vec3Slider2->z));
	}

	spaceship.setPosition((spaceshipCoords.x + vec3Slider1->x), (spaceshipCoords.y + vec3Slider1->y), (spaceshipCoords.z + vec3Slider1->z));
	asteroid.setPosition((asteroidCoords.x + vec3Slider2->x - 200), (asteroidCoords.y + vec3Slider2->y), (asteroidCoords.z + vec3Slider2->z));

	ofSetColor(ofColor::gray);
	spaceship_mesh.drawWireframe();
	asteroid_mesh.drawWireframe();

	glPointSize(2);
	ofSetColor(ofColor::white);
	spaceship_mesh.drawVertices();

	asteroid_mesh.drawVertices();

	if (toggle2) {
		spaceship.drawFaces();
		asteroid.drawFaces();
	}

	ofDisableDepthTest();

	ofSetColor(ofColor::red);

	ofDrawLine(nearestVertex1, nearestVertex2);
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	//
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

