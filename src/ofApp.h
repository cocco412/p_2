﻿#pragma once
#include "ofxGui.h"
#include "ofMain.h"

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
	void mouseClicked(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	int counter;
	bool isRunning;
	int box[4];
	int gene;

	vector<vector<float>> world;
	vector<vector<float>> pre_w;
	vector<vector<float>> n_w;
	vector<vector<vector<float>>> orbt;
	vector<vector<bool>> block;
	vector<vector<bool>> n_b;
	vector<vector<int>> blocks_n;
	void geneChange();
	void addVecter(vector<vector<float>> vv1, int x, int y);
	void addVecter(vector<vector<float>> vv1);
	void start();
	ofVec3f FlotoCol(float p);

	ofImage     img;
	bool videc;
	int pic;

	ofxFloatSlider d_al;
	ofxFloatSlider d_bt;
	ofxFloatSlider d_c;

	ofxPanel gui;
};
