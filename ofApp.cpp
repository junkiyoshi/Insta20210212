#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 350, true, true, true);

	vector<string> word_list = { "P", "C", "D", "2", "0", "2", "1" };

	for (auto word : word_list) {

		ofFbo fbo;
		fbo.allocate(ofGetWidth(), ofGetHeight());
		fbo.begin();
		ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
		ofClear(0);
		ofSetColor(0);

		font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word));

		fbo.end();

		auto span = 15;

		ofPixels pixels;
		fbo.readToPixels(pixels);
		vector<glm::vec3> location;
		for (int x = 0; x < fbo.getWidth(); x += span) {

			for (int y = 0; y < fbo.getHeight(); y += span) {

				ofColor color = pixels.getColor(x, y);
				if (color != ofColor(0, 0)) {

					for (int z = span * -1; z <= span * 1; z += span) {

						location.push_back(glm::vec3(x - ofGetWidth() * 0.5, ofGetHeight() - y - ofGetWidth() * 0.25, z));
					}
				}
			}
		}

		this->location_list.push_back(location);
	}

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}
//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	for (int i = 0; i < this->location_list.size(); i++) {

		for (int k = 0; k < this->location_list[i].size(); k++) {

			if (i < 3) {

				this->setBoxToMesh(this->face, this->line, this->location_list[i][k], glm::vec3(i * 300 - 300, 180, 0), 15, 15, 15);
			}
			else {

				this->setBoxToMesh(this->face, this->line, this->location_list[i][k], glm::vec3((i - 3) * 250 - 425, -250, 0), 15, 15, 15);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->line.draw();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, glm::vec3 word_location, float height, float width, float depth) {

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 1);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 0);

	frame_target.addIndex(index + 4); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 5); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 7);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 7);

	for (int i = index; i < face_target.getNumVertices(); i++) {

		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise((word_location.y + face_target.getVertex(i).y) * 0.0008 + ofGetFrameNum() * 0.01), 0, 1, PI * -2.5, PI * 2.5), glm::vec3(0, 1, 0));
		auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise((word_location.x + face_target.getVertex(i).x) * 0.0008 + ofGetFrameNum() * 0.01), 0, 1, PI * -2.5, PI * 2.5), glm::vec3(1, 0, 0));

		glm::vec3 rotated_location = word_location + glm::vec4(face_target.getVertex(i), 0) * rotation_y * rotation_x;
		face_target.setVertex(i, rotated_location);

		rotated_location = word_location + glm::vec4(frame_target.getVertex(i), 0) * rotation_y * rotation_x;
		frame_target.setVertex(i, rotated_location);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}