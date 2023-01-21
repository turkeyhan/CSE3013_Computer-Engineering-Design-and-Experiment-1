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
		void freeMemory();//���� �Ҵ��� �޸� ����
		void StartGame();//���� ���� �Լ�
		void get_p1();//Player 1�� ��ǥ �ޱ�
		void get_p2();//Player 2�� ��ǥ �ޱ�
		bool in_board(int x, int y); // ������ ������ Ȯ��
		bool Gameover(int p_num); // ������ �������� Ȯ��
		void clear(); //������ �ʱ�ȭ
		int turn; // � �÷��̾��� ������
		int HEIGHT;//�������� ����
		int WIDTH;//�������� �ʺ�
		int m_x, m_y;//�Է¹޴� ���� ��ǥ ����
		bool game;//������ ����������
		int cnt;//������ �� ī��Ʈ
		vector <vector<int>> visited;//������ ���������� Ȯ��
		vector <pair <int, int>> cord;//������ ���� ���� ��ǥ
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
