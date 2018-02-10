#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Particle system");
	ofSetWindowShape(1000, 1000);
	ofSetFullscreen(true);
	ofSetFrameRate(60);
	ofBackground(255);

	gui.setup("Parameters", "settings.xml");
	gui.add(max_speed.setup("max speed", 1, 1, 50));
	gui.add(force.setup("force", 1, 0, 5));

	pop = 50000;

	mesh.setMode(OF_PRIMITIVE_POINTS);
	mass.resize(pop);

	for (int i = 0; i < pop; i++) {
		mesh.addVertex(ofVec2f(ofMap(ofRandomf(), -1, 1, 0, 1000), ofMap(ofRandomf(), -1, 1, 0, 1000)));
		mesh.addColor(ofFloatColor(i/pop*255, 0, (pop-i)/pop*255));
		mesh_velocity.addVertex(ofVec2f(0, 0));
		mass[i] = ofMap(ofRandomf(), -1, 1, 10, 100);
	}
	

	center.set(500, 500);
}

//--------------------------------------------------------------
void ofApp::update(){

	for (int i = 0; i < pop; i++) {
		ofVec2f target = mesh.getVertex(i);
		ofVec2f target_velocity = mesh_velocity.getVertex(i);
		ofVec2f desired = center - target;
		desired = desired.getNormalized();
		desired = (desired * force) / mass[i];
		acceleration += desired;

		target_velocity += acceleration;
		target_velocity = target_velocity.getLimited(max_speed);
		target += target_velocity;
		acceleration *= 0;
		mesh.setVertex(i, target);
		mesh_velocity.setVertex(i, target_velocity);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	mesh.draw();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RETURN) ofSaveScreen("screenshot" + ofToString(ofRandom(0, 1000), 0) + ".png");

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	int new_x = ofGetMouseX();
	int new_y = ofGetMouseY();

	float new_xf = (float)new_x;
	float new_yf = (float)new_y;
	center = ofVec2f(new_xf, new_yf);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
