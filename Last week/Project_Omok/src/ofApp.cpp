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
	//Player 1부터 시작
	HEIGHT = 19;
	//세로 19
	WIDTH = 19;
	//가로 19
	cnt = 0;
	//오목돌의 수 0부터 시작
	game = false;
	//게임은 아직 시작 안함
	visited.assign(HEIGHT + 1, vector <int>(WIDTH + 1));
	//오목돌 방문 체크 벡터에 메모리 할당
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

	// 오목 게임 시작
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
		//게임 시작
		game = true;
	}
	if(title == "Exit") {
		//동적 할당 메모리 해제
		freeMemory();
		//프로그램 종료
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


	//색 설정
	ofSetColor(100);
	ofSetLineWidth(5);
	
	// TO DO : DRAW OMOK; 
	// 자료구조를 이용해 오목판을 그린다.
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

	//게임이 진행중일시
	if (game)
	{
		//게임 진행 함수 호출
		StartGame();
		//오목돌 그리기
		for (int i = 0; i < cord.size(); i++)
		{
			//Player 1의 오목돌일 시
			if (visited[cord[i].second][cord[i].first] == 1)
			{
				//색 설정
				ofSetColor(0);
				//오목돌 그리기
				ofDrawCircle(cord[i].first * 50, cord[i].second * 50, 20);
			}
			//Player 2의 오목돌일 시
			else
			{
				//색 설정
				ofSetColor(200);
				//오목돌 그리기
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
	// 동적할당한 메모리를 해제해주는 함수
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
	// 오목 게임을 진행하는 함수
	string str; // 리겜할건지 받기 위한 변수
	bool real_game = true; //게임이 끝났는지 확인하는 변수
	//Player 1의 턴이면
	if (turn == 1)
	{
		//좌표받고 턴 넘기고 오목돌 세기
		get_p1();
		turn = 2;
		cnt++;
	}
	//Player 2의 턴이면
	else if (turn == 2)
	{
		//좌표받고 턴 넘기고 오목돌 세기
		get_p2();
		turn = 1;
		cnt++;
	}
	//Player 1이 이겼는지 확인
	real_game = Gameover(1);
	//이겼다면
	if (!real_game)
	{
		cout << "Player1 Win!!\n";
		//리겜할지 받고
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//리겜 한다면
		if (str == "YES")
		{
			//오목판 초기화
			clear();
			//게임 진행중 체크
			game = true;
			//함수 종료
			return;
		}
		//리겜 안한다면
		else
		{
			//오목판 초기화
			clear();
			//게임 진행하지 않음 체크
			game = false;
			//함수 종료
			return;
		}
	}
	//Player 2이 이겼는지 확인
	real_game = Gameover(2);
	//이겼다면
	if (!real_game)
	{
		cout << "Player2 Win!!\n";
		//리겜할지 받고
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//리겜 한다면
		if (str == "YES")
		{
			clear();
			//오목판 초기화
			game = true;
			//게임 진행중 체크
			return;
			//함수 종료
		}
		else
		{
			clear();
			//오목판 초기화
			game = false;
			//게임 진행하지 않음 체크
			return;
			//함수 종료
		}
	}
	//오목돌이 오목판에 꽉찼다면
	if (cnt == HEIGHT * WIDTH)
	{
		//무승부
		cout << "The Game result is Draw\n";
		//리겜할지 받고
		cout << "Retry?(YES/Any word) : ";
		cin >> str;
		//리겜 한다면
		if (str == "YES")
		{
			clear();
			//오목판 초기화
			game = true;
			//게임 진행중 체크
			return;
			//함수 종료
		}
		else
		{
			clear();
			//오목판 초기화
			game = false;
			//게임 진행하지 않음 체크
			return;
			//함수 종료
		}
	}
}
bool ofApp::in_board(int x, int y)
{
	//좌표가 오목판 안인지 확인하는 함수
	return (x >= 1 && x <= WIDTH && y >= 1 && y <= HEIGHT);
}
void ofApp::get_p1()
{
	//Player 1의 좌표 받는 함수
	cout << "Player1 wants to place(ex. 1 1 / first value is x, second value is y) : ";
	cin >> m_x >> m_y;
	//오목판 안이고 방문하지 않았다면
	if (in_board(m_x, m_y) && !visited[m_y][m_x])
	{
		//방문 체크 및 좌표 넣기
		visited[m_y][m_x] = 1; 
		cord.push_back({ m_x, m_y });
	}
	//이외는 오류메세지 출력 후 재귀호출
	else
	{
		cout << "Warning!! Wrong Place!! Retry!!\n";
		get_p1();
	}
}
void ofApp::get_p2()
{
	//Player 2의 좌표 받는 함수
	cout << "Player2 wants to place(ex. 1 1 / first value is x, second value is y) : ";
	cin >> m_x >> m_y;
	//오목판 안이고 방문하지 않았다면
	if (in_board(m_x, m_y) && !visited[m_y][m_x])
	{
		//방문 체크 및 좌표 넣기
		visited[m_y][m_x] = 2;
		cord.push_back({ m_x, m_y });
	}
	//이외는 오류메세지 출력 후 재귀호출
	else
	{
		cout << "Warning!! Wrong Place!! Retry!!\n";
		get_p2();
	}
}
bool ofApp::Gameover(int p_num)
{
	//오목 게임이 끝났는지 확인하는 함수, 인자로는 플레이어의 번호 받음
	//오목판 전체를 돌면서
	for (int i = 1; i <= HEIGHT; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			//세로의 5번째 돌이 오목판 안이면
			if (in_board(j, i + 4))
			{
				//가로의 5번째 돌이 오목판 안이면
				if (in_board(j + 4, i))
				{
					//대각선 확인
					if (visited[i][j] == p_num && visited[i + 1][j + 1] == p_num && visited[i + 2][j + 2] == p_num && visited[i + 3][j + 3] == p_num && visited[i + 4][j + 4] == p_num)
					{
						return false;
					}
				}
				//세로 확인
				if (visited[i][j] == p_num && visited[i + 1][j] == p_num && visited[i + 2][j] == p_num && visited[i + 3][j] == p_num && visited[i + 4][j] == p_num)
				{
					return false;
				}
			}
			//가로의 5번째 돌이 오목판 안이면
			if (in_board(j + 4, i))
			{
				//가로 확인
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
	//오목판 초기화 함수
	//오목판 전체를 돌며 방문 체크한거 초기화
	for (int i = 1; i <= HEIGHT; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			visited[i][j] = 0;
		}
	}
	//오목돌 그리기 위한 좌표 벡터 초기화
	vector <pair<int, int>>().swap(cord);
	vector <pair<int, int>>(cord).swap(cord);
	//오목돌 개수 초기화
	cnt = 0;
}