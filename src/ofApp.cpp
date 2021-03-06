﻿#include "ofApp.h"

#define SIZE 256
//--------------------------------------------------------------
void ofApp::setup() {
	//ofDisableAntiAliasing();
	isRunning = false;
	counter = 0;
	gene = 0;
	videc = false;
	pic = 0;

	gui.setup();
	float a = 0.805f;
	float b = 0.2f;
	float c = 0.645f;
	gui.add(d_al.setup("alpha",a, 0.0f, 1.0f));
	gui.add(d_bt.setup("beta", b, 0.0f, 1.0f));
	gui.add(d_c.setup("c", c, 0.0f, 1.0f));
	
	box[0] = 10;  //x座標
	box[1] = 10;  //y座標
	box[2] = 512;  //x幅
	box[3] = 512;  //y幅

	ofBackground(200, 200, 200);
	

	world = vector<vector<float>>(SIZE, vector<float>(SIZE, 0.0f));
	block = vector<vector<bool>>(world.size(), vector<bool>(world[0].size(), false));
	blocks_n = vector<vector<int>>(world.size(), vector<int>(world[0].size(), 0));
	orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(8, 0.0f)));

	/*
	for (size_t i = 0; i < (int)block.size(); i++)
	{
		block[i][0] = true;
		block[i][block[0].size() - 1] = true;
	}
	for (size_t j = 0; j < (int)block[0].size() - 1; j++)
	{
		block[0][j] = true;
		block[world.size() - 1][j] = true;
	}*/

	/*
	for (size_t i = 0; i < (int)block.size(); i++)
	{
		if (ofRandomf() > -0.5f)
		{
			for (size_t j = 0; j < (int)block[0].size(); j++)
			{
				block[i][j] = true;
			}
		}
	}
	for (size_t j = 1; j < (int)block[0].size() - 1; j++)
	{
		if (ofRandomf() > 0.5f)
		{
			for (size_t i = 1; i < (int)block.size() - 1; i++)
			{
				block[i][j] = false;
			}
		}
	}*/

	n_w = world;
	n_b = block;

	//vector<vector<float>> pre1 = { {1.0f} };
	//vector<vector<bool>> sample1(7, vector<bool>(7, true));
	//addVecter(pre1);

	start();

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {
	counter++;
	if (counter > 1000)counter = 0;
	//if (start && (world != pre_w))
	if (isRunning)
	{
		//if (counter % 2 == 0)
		geneChange();
		gene++;
		/*
		if (pic < 140)
		{
			//img.grabScreen(0, 0, 2*box[0]+box[2], 2*box[1] + box[3]);
			//img.save("002/"+ofToString(pic)+".png");
			//pic++;
		}*/
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(200, 200, 200);
	//ofDrawRectangle(box[0] - 5, box[1] - 5, box[2] + 10, box[3] + 10);
	ofSetColor(0, 0, 0);
	int width = (int)(box[2] * 1.0f / world[0].size());
	int height = (int)(box[3] * 1.0f / world.size());

	int mX = (int)((mouseX - box[0]) *1.0f / width);
	int mY = (int)((mouseY - box[1]) *1.0f / height);
	if (mX < 0 || mX >= world[0].size())mX = 0;
	if (mY < 0 || mY >= world.size())mY = 0;

	{
		for (size_t i = 0; i < (int)world.size(); i++)
		{
			int py = box[1] + i * box[3] / (int)world.size();                       //行

			for (size_t j = 0; j < (int)world[0].size(); j++)
			{
				int px = box[0] + j * box[2] / (int)world[0].size();               //列

				ofSetColor(FlotoCol(world[i][j]).x, FlotoCol(world[i][j]).y, FlotoCol(world[i][j]).z);
				//ofSetColor(world[i][j] * 255, world[i][j] * 255, world[i][j] * 255);
				if (j==mX&&i==mY)ofSetColor(255,0,0);
				ofDrawRectangle(px, py, box[2] / (int)world[0].size(), box[3] / (int)world.size());
			}
		}/**/
	}
	ofSetColor(0, 0, 0);

	for (size_t i = 0; i < 256; i++)
	{
		ofSetColor(FlotoCol((256 - i) / 256.0f).x, FlotoCol((256 - i) / 256.0f).y, FlotoCol((256 - i) / 256.0f).z);
		ofDrawRectangle(box[0] - 8, box[1] + 2 * i, 2, 2);
	}

	ofDrawBitmapString(
		(string)""
		+ "isRunning: " + ofToString(isRunning) + "\r\n"
		+ "g:" + ofToString(gene) + "\r\n"
		+ "\r\n"
		+ "m:" + ofToString(world[mY][mX]) + "\r\n"
		+ "V_M:" + ofToString(d_c*(d_al*1.0f/d_bt)) + "\r\n"
		+ "v_m:" + ofToString(d_c * (d_bt * 1.0f / d_al)) + "\r\n",
		box[0] + box[2] + 50, box[1] + 60);
	ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", box[0] + box[2] + 50, box[1] + 15);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		ofApp::start();
	};

	if (key == 'x') {
		videc = true;
	}
	if (key == 'z') {
		isRunning = !isRunning;
	}
	if (key == 'c') {
		block = n_b;
	}
	if (key == 'v') {
		isRunning = true;
		ofApp::update();
		isRunning = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (button == 0) {
		int width = (int)(box[2] * 1.0f / world[0].size());
		int height = (int)(box[3] * 1.0f / world.size());
		int mX = (int)((x - box[0]) *1.0f / width);
		int mY = (int)((y - box[1]) *1.0f / height);
		if (mX < 0 || mX >= world[0].size())mX = 0;
		if (mY < 0 || mY >= world.size())mY = 0;
		block[mY][mX] = true;
	}
	if (button == 2) {
		int width = (int)(box[2] * 1.0f / world[0].size());
		int height = (int)(box[3] * 1.0f / world.size());
		int mX = (int)((x - box[0]) *1.0f / width);
		int mY = (int)((y - box[1]) *1.0f / height);
		if (mX < 0 || mX >= world[0].size())mX = 0;
		if (mY < 0 || mY >= world.size())mY = 0;

		block[mY][mX] = false;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseClicked(int x, int y, int button)
{
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

void ofApp::geneChange()
{
	pre_w = world;
	world = n_w;

	int ie = (int)pre_w.size();
	int je = (int)pre_w[0].size();

	for (size_t i = 0; i < ie; i++)
	{
		for (size_t j = 0; j < je; j++)
		{
			if (true) {
				float alpha;
				float pw = pre_w[i][j];

				if (pw > d_c)
				{
					alpha = d_bt;
				}
				else alpha = d_al;
				
				world[i][(j + 1) % je] += pw * (1 - alpha) / 4.0f;
				world[i][(j - 1 + je) % je] += pw * (1 - alpha) / 4.0f;
				world[(i + 1) % ie][j] += pw * (1 - alpha) / 4.0f;
				world[(i - 1 + ie) % ie][j] += pw * (1 - alpha) / 4.0f;
				world[i][j] += pw * alpha;
			}
		}
	}
}

void ofApp::addVecter(vector<vector<float>> vv1, int x, int y)
{
	if (x < 0 || y < 0 || y + (int)vv1.size() > world.size() || x + (int)vv1.size() > world[0].size())
	{
		return;
	}
	for (size_t i = y; i < y + (int)vv1.size(); i++)
	{
		for (size_t j = x; j < x + (int)vv1[0].size(); j++)
		{
			world[i][j] += vv1[i - y][j - x];
		}
	}
}

void ofApp::addVecter(vector<vector<float>> vv1)
{
	int y = ((int)world.size() - vv1.size()) / 2;
	int x = ((int)world[0].size() - vv1[0].size()) / 2;

	ofApp::addVecter(vv1, x, y);
}

void ofApp::start()
{
	world = n_w;
	float min = d_al;// d_c* d_bt* 1.0f / d_al;
	float max = d_bt;// d_c* d_al* 1.0f / d_bt;
	for (size_t i = 0; i < (int)world.size(); i++)
	{
		for (size_t j = 0; j < (int)world[0].size(); j++)
		{
			world[i][j] = abs(ofRandomf()) * (max - min) + min;
			//world[i][j] = (i + j) % 2 == 0 ? min : max;			
		}
	}
	orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(100, 0.0f)));
	gene = 0;
	isRunning = false;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

ofVec3f ofApp::FlotoCol(float p)
{
	//p = -(d_bt * (d_al * p - d_bt * d_c)) / ((d_bt - d_al) * (d_bt + d_al) * d_c);//(p - d_c * (d_bt * 1.0f / d_al)) * 1.0 / (d_c * (d_al * 1.0f / d_bt - d_bt * 1.0f / d_al));
	
	float min = d_bt;// d_c* d_bt* 1.0f / d_al;
	float max = d_al;// d_c* d_al* 1.0f / d_bt;
	p = (p - min) * 1.0f / (max - min);
	if (p <= 1 && p >= 0)
	{
		//return ofVec3f(p * 255, p * 255, p * 255);
		/**/
		int r, g, b;/*
		r = 128 + 127 * sin(2.0f* p*PI / 2.0f - PI / 2.0f);
		g = 102 + 102 * sin(2.0f* p*PI - PI / 2.0f);
		b = 128 + 64 * sin(2.0f* p*PI - PI / 4.0f);*/

		/**/
		if (p >= 2 / 3.0f)
		{
			r = 255;
			g = 255 - 255 * (3 * p - 2);
			b = 0;
		}
		else if (p >= 1 / 3.0f)
		{
			r = 255 * (3 * p - 1);
			g = 255;
			b = 255 - 255 * (3 * p - 1);
		}
		else
		{
			r = 0;
			g = 255 * (3 * p);
			b = 255;
		}
		

		return ofVec3f(r, g, b);
	}
	else if (p <= 0)
	{
		return ofVec3f(0, 0, 0);
	}
	else
	{
		return ofVec3f(255, 255, 255);
	}
}