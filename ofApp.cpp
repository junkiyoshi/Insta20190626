#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->font_size = 18;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"!", u8"#", u8"$", u8"%", u8"&",
		u8"'", u8"(", u8")", u8"*", u8"+",
		u8",", u8"-", u8".", u8"/", u8"0",
		u8"1", u8"2", u8"3", u8"4", u8"5",
		u8"6", u8"7", u8"8", u8"9", u8"0",
		u8":", u8";", u8"<", u8"=", u8">",
		u8"?", u8"@",

		u8"A", u8"B", u8"C", u8"D", u8"E",
		u8"F", u8"G", u8"H", u8"I", u8"J",
		u8"K", u8"L", u8"M", u8"N", u8"O",
		u8"P", u8"Q", u8"R", u8"S", u8"T",
		u8"U", u8"V", u8"W", u8"X", u8"Y", u8"Z",

		u8"a", u8"b", u8"c", u8"d", u8"e",
		u8"f", u8"g", u8"h", u8"i", u8"j",
		u8"k", u8"l", u8"m", u8"n", u8"o",
		u8"p", u8"q", u8"r", u8"s", u8"t",
		u8"u", u8"v", u8"w", u8"x", u8"y", u8"z",
		
		u8"ｱ", u8"ｲ", u8"ｳ", u8"ｴ", u8"ｵ",
		u8"ｶ", u8"ｷ", u8"ｸ", u8"ｹ", u8"ｺ",
		u8"ｻ", u8"ｼ", u8"ｽ", u8"ｾ", u8"ｿ",
		u8"ﾀ", u8"ﾁ", u8"ﾂ", u8"ﾃ", u8"ﾄ",
		u8"ﾅ", u8"ﾆ", u8"ﾇ", u8"ﾈ", u8"ﾉ",
		u8"ﾊ", u8"ﾋ", u8"ﾌ", u8"ﾍ", u8"ﾎ",
		u8"ﾏ", u8"ﾐ", u8"ﾑ", u8"ﾒ", u8"ﾓ",
		u8"ﾔ", u8"ﾕ", u8"ﾖ",
		u8"ﾗ", u8"ﾘ", u8"ﾙ", u8"ﾚ", u8"ﾛ",
		u8"ﾜ", u8"ｦ", u8"ﾝ",
	};

	for (int x = 0; x < ofGetWidth(); x += this->font_size) {

		vector<string> line;
		vector<int> param;
		for (int y = 0; y <= ofGetHeight(); y += this->font_size) {

			line.push_back(this->words[(int)(ofRandom(this->words.size()))]);
			param.push_back(0);
		}

		this->matrix.push_back(line);
		this->params.push_back(param);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto noise_location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum()  * 0.005), 0, 1, 60, ofGetWidth() - 60), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 60, ofGetHeight() - 60));

	for (int row = 0; row < this->matrix.size(); row++) {

		int x = row * this->font_size * 1.05;
		for (int col = 0; col < this->matrix[row].size(); col++) {

			int y = col * this->font_size * 1.05;

			auto distance = glm::distance(glm::vec2(x, y), noise_location);
			if (distance < 100) {

				if (this->params[row][col] < 100) {

					this->params[row][col] += 2;
				}
			}

			if (this->params[row][col] > 0) {

				this->matrix[row][col] = this->words[(int)(ofRandom(this->words.size()))];

				int alpha = 255;
				if (this->params[row][col] < 30) {
				
					alpha = ofMap(this->params[row][col], 0, 30, 0, 255);
				}
				ofSetColor(23, alpha);

				ofPushMatrix();
				ofTranslate(x, ofGetHeight() - y);

				this->font.drawString(this->matrix[row][col], 0, 0);

				ofPopMatrix();

				this->params[row][col]--;
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}