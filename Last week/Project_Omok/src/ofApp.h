/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void freeMemory();//동적 할당한 메모리 해제
		void StartGame();//게임 진행 함수
		void get_p1();//Player 1의 좌표 받기
		void get_p2();//Player 2의 좌표 받기
		bool in_board(int x, int y); // 오목판 안인지 확인
		bool Gameover(int p_num); // 게임이 끝났는지 확인
		void clear(); //오목판 초기화
		int turn; // 어떤 플레이어의 턴인지
		int HEIGHT;//오목판의 높이
		int WIDTH;//오목판의 너비
		int m_x, m_y;//입력받는 오목돌 좌표 변수
		bool game;//게임이 진행중인지
		int cnt;//오목돌의 수 카운트
		vector <vector<int>> visited;//오목돌이 놓여졌는지 확인
		vector <pair <int, int>> cord;//놓여진 오목돌 저장 좌표
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
