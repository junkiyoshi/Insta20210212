#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, glm::vec3 word_location, float height, float width, float depth);

	ofEasyCam cam;
	vector<vector<glm::vec3>> location_list;

	ofMesh face, line;
};