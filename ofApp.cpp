#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofNoFill();
	ofEnableDepthTest();
	ofSetLineWidth(3);

	for (int x = -200; x <= 200; x += 1) {

		this->base_location_list.push_back(glm::vec3(x, -200, -200));
		this->base_location_list.push_back(glm::vec3(x, -200, 200));
		this->base_location_list.push_back(glm::vec3(x, 200, -200));
		this->base_location_list.push_back(glm::vec3(x, 200, 200));
	}

	for (int y = -200; y <= 200; y += 1) {

		this->base_location_list.push_back(glm::vec3(-200, y, -200));
		this->base_location_list.push_back(glm::vec3(-200, y, 200));
		this->base_location_list.push_back(glm::vec3(200, y, -200));
		this->base_location_list.push_back(glm::vec3(200, y, 200));
	}

	for (int z = -200; z <= 200; z += 1) {

		this->base_location_list.push_back(glm::vec3(-200, -200, z));
		this->base_location_list.push_back(glm::vec3(-200, 200, z));
		this->base_location_list.push_back(glm::vec3(200, -200, z));
		this->base_location_list.push_back(glm::vec3(200, 200, z));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	int radius = 5;
	ofColor color;
	while (this->log_list.size() < 6000) {

		int font_location_index = ofRandom(this->base_location_list.size());
		vector<glm::vec3> log;
		log.push_back(this->base_location_list[font_location_index]);
		this->log_list.push_back(log);
		if (this->base_location_list[font_location_index].x == 200 || this->base_location_list[font_location_index].x == -200) {
		
			if (this->base_location_list[font_location_index].y == 200 || this->base_location_list[font_location_index].y == -200) {

				color.setHsb(ofMap(this->base_location_list[font_location_index].z, -200, 200, 0, 255), ofRandom(0, 255), ofRandom(0, 255));
			}
			else {

				color.setHsb(ofMap(this->base_location_list[font_location_index].y, -200, 200, 0, 255), ofRandom(0, 255), ofRandom(0, 255));
			}
		}
		else if (this->base_location_list[font_location_index].y == 200 || this->base_location_list[font_location_index].y == -200) {

			color.setHsb(ofMap(this->base_location_list[font_location_index].x, -200, 200, 0, 255), ofRandom(100, 255), ofRandom(100, 255));
		}

		this->color_list.push_back(color);
		this->life_list.push_back(ofRandom(10, 120));
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);

			continue;
		}

		auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.005, ofGetFrameNum() * 0.003)), 0, 1, -360, 360);
		auto theta = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.005, (ofGetFrameNum() + 10000) * 0.003)), 0, 1, -360, 360);
		this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * cos(theta * DEG_TO_RAD)));

		if (this->log_list[i].back().x > 200) {

			this->log_list[i].back().x = 200;
		}
		else if (this->log_list[i].back().x < -200) {

			this->log_list[i].back().x = -200;
		}

		if (this->log_list[i].back().y > 200) {

			this->log_list[i].back().y = 200;
		}
		else if (this->log_list[i].back().y < -200) {

			this->log_list[i].back().y = -200;
		}

		if (this->log_list[i].back().z > 200) {

			this->log_list[i].back().z = 200;
		}
		else if (this->log_list[i].back().z < -200) {

			this->log_list[i].back().z = -200;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateY(ofGetFrameNum() * 0.666666666666);
	ofRotateZ(ofGetFrameNum() * 0.666666666666);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(this->color_list[i]);

		if (this->life_list[i] > 30) {

			ofSetLineWidth(1.5);
		}
		else {

			ofSetLineWidth(ofMap(this->life_list[i], 0, 30, 0, 1.5));
		}

		ofSetColor(this->color_list[i]);

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}