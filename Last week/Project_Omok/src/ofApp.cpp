/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Omok"); // Set the app name on the title bar
	ofSetFrameRate(50);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	turn = 1;
	//Player 1���� ����
	HEIGHT = 19;
	//���� 19
	WIDTH = 19;
	//���� 19
	cnt = 0;
	//������ �� 0���� ����
	game = false;
	//������ ���� ���� ����
	visited.assign(HEIGHT + 1, vector <int>(WIDTH + 1));
	//���� �湮 üũ ���Ϳ� �޸� �Ҵ�
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// ���� ���� ����
	menu->AddPopupItem(hPopup, "Start Game", false, false); // Not checked and not auto-checked

	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);


	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Start Game") 
	{
		//���� ����
		game = true;
	}
	if(title == "Exit") {
		//���� �Ҵ� �޸� ����
		freeMemory();
		//���α׷� ����
		ofExit(); 
	}

	
	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nOmok example\nif you make 5 stones in a row first, you will win!!\n");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {


	//�� ����
	ofSetColor(100);
	ofSetLineWidth(5);
	
	// TO DO : DRAW OMOK; 
	// �ڷᱸ���� �̿��� �������� �׸���.
	// add code here
	
	for (int i = 1; i <= HEIGHT; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			if (HEIGHT == i && WIDTH == j)
			{
				continue;
			}
			else if (WIDTH == j)
			{
				ofDrawLine(j * 50, i * 50, j * 50, (i + 1) * 50);
				continue;
			}
			else if (HEIGHT == i)
			{
				ofDrawLine(j * 50, i * 50, (j+1) * 50, i * 50);
				continue;
			}
			else
			{
				ofDrawLine(j * 50, i * 50, j * 50, (i + 1) * 50);
				ofDrawLine(j * 50, i * 50, (j + 1) * 50, i * 50);
			}
		}
	}

	//������ �������Ͻ�
	if (game)
	{
		//���� ���� �Լ� ȣ��
		StartGame();
		//���� �׸���
		for (int i = 0; i < cord.size(); i++)
		{
			//Player 1�� ������ ��
			if (visited[cord[i].second][cord[i].first] == 1)
			{
				//�� ����
				ofSetColor(0);
				//���� �׸���
				ofDrawCircle(cord[i].first * 50, cord[i].second * 50, 20);
			}
			//Player 2�� ������ ��
			else
			{
				//�� ����
				ofSetColor(200);
				//���� �׸���
				ofDrawCircle(cord[i].first * 50, cord[i].second * 50, 20);
			}
		}
	}
	
	

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

void ofApp::freeMemory() {

	//TO DO
	// �����Ҵ��� �޸𸮸� �������ִ� �Լ�
	for (int i = 0; i <HEIGHT + 1; i++)
	{
		vector <int>().swap(visited[i]);
		vector <int>(visited[i]).swap(visited[i]);
	}
	vector <vector <int>>().swap(visited);
	vector <vector <int>>(visited).swap(visited);
	vector <pair<int, int>>().swap(cord);
	vector <pair<int, int>>(cord).swap(cord);
}

void ofApp::StartGame()
{
	// ���� ������ �����ϴ� �Լ�
	string str; // �����Ұ��� �ޱ� ���� ����
	bool real_game = true; //������ �������� Ȯ���ϴ� ����
	//Player 1�� ���̸�
	if (turn == 1)
	{
		//��ǥ�ް� �� �ѱ�� ���� ����
		get_p1();
		turn = 2;
		cnt++;
	}
	//Player 2�� ���̸�
	else if (turn == 2)
	{
		//��ǥ�ް� �� �ѱ�� ���� ����
		get_p2();
		turn = 1;
		cnt++;
	}
	//Player 1�� �̰���� Ȯ��
	real_game = Gameover(1);
	//�̰�ٸ�
	if (!real_game)
	{
		cout << "Player1 Win!!\n";
		//�������� �ް�
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//���� �Ѵٸ�
		if (str == "YES")
		{
			//������ �ʱ�ȭ
			clear();
			//���� ������ üũ
			game = true;
			//�Լ� ����
			return;
		}
		//���� ���Ѵٸ�
		else
		{
			//������ �ʱ�ȭ
			clear();
			//���� �������� ���� üũ
			game = false;
			//�Լ� ����
			return;
		}
	}
	//Player 2�� �̰���� Ȯ��
	real_game = Gameover(2);
	//�̰�ٸ�
	if (!real_game)
	{
		cout << "Player2 Win!!\n";
		//�������� �ް�
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//���� �Ѵٸ�
		if (str == "YES")
		{
			clear();
			//������ �ʱ�ȭ
			game = true;
			//���� ������ üũ
			return;
			//�Լ� ����
		}
		else
		{
			clear();
			//������ �ʱ�ȭ
			game = false;
			//���� �������� ���� üũ
			return;
			//�Լ� ����
		}
	}
	//������ �����ǿ� ��á�ٸ�
	if (cnt == HEIGHT * WIDTH)
	{
		//���º�
		cout << "The Game result is Draw\n";
		//�������� �ް�
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//���� �Ѵٸ�
		if (str == "YES")
		{
			clear();
			//������ �ʱ�ȭ
			game = true;
			//���� ������ üũ
			return;
			//�Լ� ����
		}
		else
		{
			clear();
			//������ �ʱ�ȭ
			game = false;
			//���� �������� ���� üũ
			return;
			//�Լ� ����
		}
	}
}
bool ofApp::in_board(int x, int y)
{
	//��ǥ�� ������ ������ Ȯ���ϴ� �Լ�
	return (x >= 1 && x <= WIDTH && y >= 1 && y <= HEIGHT);
}
void ofApp::get_p1()
{
	//Player 1�� ��ǥ �޴� �Լ�
	cout << "Player1 wants to place(ex. 1 1 / first value is x, second value is y) : ";
	cin >> m_x >> m_y;
	//������ ���̰� �湮���� �ʾҴٸ�
	if (in_board(m_x, m_y) && !visited[m_y][m_x])
	{
		//�湮 üũ �� ��ǥ �ֱ�
		visited[m_y][m_x] = 1; 
		cord.push_back({ m_x, m_y });
	}
	//�ܴ̿� �����޼��� ��� �� ���ȣ��
	else
	{
		cout << "Warning!! Wrong Place!! Retry!!\n";
		get_p1();
	}
}
void ofApp::get_p2()
{
	//Player 2�� ��ǥ �޴� �Լ�
	cout << "Player2 wants to place(ex. 1 1 / first value is x, second value is y) : ";
	cin >> m_x >> m_y;
	//������ ���̰� �湮���� �ʾҴٸ�
	if (in_board(m_x, m_y) && !visited[m_y][m_x])
	{
		//�湮 üũ �� ��ǥ �ֱ�
		visited[m_y][m_x] = 2;
		cord.push_back({ m_x, m_y });
	}
	//�ܴ̿� �����޼��� ��� �� ���ȣ��
	else
	{
		cout << "Warning!! Wrong Place!! Retry!!\n";
		get_p2();
	}
}
bool ofApp::Gameover(int p_num)
{
	//���� ������ �������� Ȯ���ϴ� �Լ�, ���ڷδ� �÷��̾��� ��ȣ ����
	//������ ��ü�� ���鼭
	for (int i = 1; i <= HEIGHT; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			//������ 5��° ���� ������ ���̸�
			if (in_board(j, i + 4))
			{
				//������ 5��° ���� ������ ���̸�
				if (in_board(j + 4, i))
				{
					//�밢�� Ȯ��
					if (visited[i][j] == p_num && visited[i + 1][j + 1] == p_num && visited[i + 2][j + 2] == p_num && visited[i + 3][j + 3] == p_num && visited[i + 4][j + 4] == p_num)
					{
						return false;
					}
				}
				//���� Ȯ��
				if (visited[i][j] == p_num && visited[i + 1][j] == p_num && visited[i + 2][j] == p_num && visited[i + 3][j] == p_num && visited[i + 4][j] == p_num)
				{
					return false;
				}
			}
			//������ 5��° ���� ������ ���̸�
			if (in_board(j + 4, i))
			{
				//���� Ȯ��
				if (visited[i][j] == p_num && visited[i][j + 1] == p_num && visited[i][j + 2] == p_num && visited[i][j + 3] == p_num && visited[i][j + 4] == p_num)
				{
					return false;
				}
			}
		}
	}
	return true;
}
void ofApp::clear()
{
	//������ �ʱ�ȭ �Լ�
	//������ ��ü�� ���� �湮 üũ�Ѱ� �ʱ�ȭ
	for (int i = 1; i <= HEIGHT; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			visited[i][j] = 0;
		}
	}
	//���� �׸��� ���� ��ǥ ���� �ʱ�ȭ
	vector <pair<int, int>>().swap(cord);
	vector <pair<int, int>>(cord).swap(cord);
	//���� ���� �ʱ�ȭ
	cnt = 0;
}