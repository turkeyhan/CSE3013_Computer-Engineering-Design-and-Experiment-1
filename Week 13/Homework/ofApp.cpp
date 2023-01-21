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
#include <cstdio>
#include <Windows.h>
#define WALL_H 4
#define WALL_W 5 
#define EMPTY 6
#define DOT 7
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

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

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
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
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			dfs_object = false;
			DFS(1, 1);
			isdfs = true;
			isbfs = false;
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly
		if (isOpen)
		{
			bfs_object = false;
			BFS(1, 1);
			isdfs = false;
			isbfs = true;
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}

bool ofApp::InMap(int y, int x)
{
	return (y >= 0 && y <= 2 * HEIGHT) && (x >= 0 && x <= 2 * WIDTH);
}

//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(0, 0, 255);
	ofSetLineWidth(5);
	
	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	int xx[2] = { 0, 1};
	int yy[2] = { 1, 0};
	int nx, ny;
	for (int i = 0; i < 2 * HEIGHT + 1; i+=2)
	{
		for (int j = 0; j < 2 * WIDTH + 1; j+=2)
		{
			for (int k = 0; k < 2; k++)
			{	
				nx = j + xx[k];
				ny = i + yy[k];
				if (InMap(ny, nx))
				{
					if (maz[ny][nx] == WALL_H)
					{
						ofDrawLine(j*10, i*10, nx*10, (ny + 1)*10);
					}
					else if (maz[ny][nx] == WALL_W)
					{
						ofDrawLine(j*10, i*10, (nx + 1)*10, ny*10);
					}
				}
			}
		}
	}

	if (isdfs)
	{
		ofSetColor(0, 255, 0);
		ofSetLineWidth(5);
		if (isOpen)
		{
			dfsdraw();
		}
		else
			cout << "You must open file first" << endl;
	}

	if (isbfs)
	{
		ofSetColor(0, 255, 0);
		ofSetLineWidth(5);
		if (isOpen)
		{
			bfsdraw();
		}
		else
			cout << "You must open file first" << endl;
	}
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
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
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is ");
		cout << fileName << '\n';
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;
			
			
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			string str;
			for (ofBuffer::Line iter = buffer.getLines().begin(), end = buffer.getLines().end(); iter != end; iter++)
			{
				str = *iter;
				if (!idx)
				{
					idx = str.size();
				}
				cnt++;
			}
			WIDTH = idx / 2;
			HEIGHT = cnt / 2;
			maz.assign(2*HEIGHT + 3, vector<int>(2*WIDTH+3));
			
			int y = 0;
			for (ofBuffer::Line iter = buffer.getLines().begin(), end = buffer.getLines().end(); iter != end; iter++)
			{
				str = *iter;
				for (int i = 0; i < idx; i++)
				{
					if (str[i] == '+')
					{
						maz[y][i] = DOT;
					}
					else if (str[i] == '-')
					{
						maz[y][i] = WALL_W;
					}
					else if (str[i] == '|')
					{
						maz[y][i] = WALL_H;
					}
					else if (str[i] == ' ')
					{
						maz[y][i] = EMPTY;
					}
				}
				y++;
			}
			visited.assign(2 * HEIGHT + 1, vector<int>(2 * WIDTH + 1));
			prev.assign(2 * HEIGHT + 1, vector<pair<int, int>>(2 * WIDTH + 1));
			visit.assign(2 * HEIGHT + 1, vector<int>(2 * WIDTH + 1));
			pre.assign(2 * HEIGHT + 1, vector<pair<int, int>>(2 * WIDTH + 1));
			vector<pair<int, int>>(graph).swap(graph);
			vector < pair<int, int>>().swap(graph);
			vector<pair<int, int>>(grap).swap(grap);
			vector < pair<int, int>>().swap(grap);
			dfs_object = false;
			isdfs = false;
			bfs_object = false;
			isbfs = false;
			bShowInfo = true;
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {

	//TO DO
	// malloc한 memory를 free해주는 함수
	for (int i = 0; i < 2 * HEIGHT + 3; i++)
	{
		vector<int>(maz[i]).swap(maz[i]);
		vector<int>().swap(maz[i]);
	}
	vector<vector<int>>(maz).swap(maz);
	vector<vector<int>>().swap(maz);
	for (int i = 0; i < 2 * HEIGHT + 1; i++)
	{
		vector<int>(visited[i]).swap(visited[i]);
		vector<int>().swap(visited[i]);
	}
	vector<vector<int>>(visited).swap(visited);
	vector<vector<int>>().swap(visited);
	for (int i = 0; i < 2 * HEIGHT + 1; i++)
	{
		vector<pair<int, int>>(prev[i]).swap(prev[i]);
		vector<pair<int, int>>().swap(prev[i]);
	}
	vector<vector<pair<int, int>>>(prev).swap(prev);
	vector<vector<pair<int, int>>>().swap(prev);
	for (int i = 0; i < 2 * HEIGHT + 1; i++)
	{
		vector<int>(visit[i]).swap(visit[i]);
		vector<int>().swap(visit[i]);
	}
	vector<vector<int>>(visit).swap(visit);
	vector<vector<int>>().swap(visit);
	for (int i = 0; i < 2 * HEIGHT + 1; i++)
	{
		vector<pair<int, int>>(pre[i]).swap(pre[i]);
		vector<pair<int, int>>().swap(pre[i]);
	}
	vector<vector<pair<int, int>>>(pre).swap(pre);
	vector<vector<pair<int, int>>>().swap(pre);
}

bool ofApp::DFS(int y, int x)//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	int xx[4] = { 0, 0, -2, 2 };
	int yy[4] = { 2, -2, 0, 0 };
	int nx, ny;
	for (int k = 0; k < 4; k++)
	{
		if (dfs_object)
		{
			return true;
		}
		nx = x + xx[k];
		ny = y + yy[k];
		if (InMap(ny, nx) && !visited[ny][nx])
		{
			if (nx == x)
			{
				if (ny > y)
				{
					if (maz[y + 1][x] == EMPTY)
					{
						visited[ny][nx] = 1;
						graph.push_back({ y, x });
						graph.push_back({ ny, nx });
						prev[ny][nx] = { y, x };
						if (ny == 2 * HEIGHT - 1 && nx == 2 * WIDTH - 1)
						{
							dfs_object = true;
							return true;
						}
						DFS(ny, nx);
					}
				}
				else
				{
					if (maz[y - 1][x] == EMPTY)
					{
						visited[ny][nx] = 1;
						graph.push_back({ y, x });
						graph.push_back({ ny, nx });
						prev[ny][nx] = { y, x };
						if (ny == 2 * HEIGHT - 1 && nx == 2 * WIDTH - 1)
						{
							dfs_object = true;
							return true;
						}
						DFS(ny, nx);
					}
					
				}
			}
			if (ny == y)
			{
				if (nx > x)
				{
					if (maz[y][x+1] == EMPTY)
					{
						visited[ny][nx] = 1;
						graph.push_back({ y, x });
						graph.push_back({ ny, nx });
						prev[ny][nx] = { y, x };
						if (ny == 2 * HEIGHT - 1 && nx == 2 * WIDTH - 1)
						{
							dfs_object = true;
							return true;
						}
						DFS(ny, nx);
					}
				}
				else
				{
					if (maz[y][x - 1] == EMPTY)
					{
						visited[ny][nx] = 1;
						graph.push_back({ y, x });
						graph.push_back({ ny, nx });
						prev[ny][nx] = { y, x };
						if (ny == 2 * HEIGHT - 1 && nx == 2 * WIDTH - 1)
						{
							dfs_object = true;
							return true;
						}
						DFS(ny, nx);
					}
				}
			}
		}
	}
	return true;
}
void ofApp::dfsdraw()
{
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
	int Size = graph.size();
	for (int i = 0; i < Size -1; i += 2)
	{
		ofDrawLine(graph[i].second * 10, graph[i].first * 10, graph[i + 1].second * 10, graph[i + 1].first * 10);
	}

	ofSetColor(255, 0, 0);
	ofSetLineWidth(5);
	pair <int, int> coord = { 2 * HEIGHT - 1, 2 * WIDTH - 1};
	while (true)
	{
		ofDrawLine(coord.second * 10, coord.first * 10, prev[coord.first][coord.second].second * 10, prev[coord.first][coord.second].first * 10);
		coord = { prev[coord.first][coord.second] };
		if (coord.first == 1 && coord.second == 1)
		{
			break;
		}
	}
}

bool ofApp::BFS(int y, int x)
{
	queue <pair<int, int>> q;
	q.push({ y, x });
	visit[y][x] = 1;
	int xx[4] = { 0, 0, -2, 2 };
	int yy[4] = { 2, -2, 0, 0 };
	int nx, ny, kx, ky;
	while (!q.empty())
	{
		ny = q.front().first;
		nx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			ky = ny + yy[i];
			kx = nx + xx[i];

			if (InMap(ky, kx) && !visited[ky][kx])
			{
				if (kx == nx)
				{
					if (ky > ny)
					{
						if (maz[ny + 1][nx] == EMPTY)
						{
							visited[ky][kx] = 1;
							grap.push_back({ ny, nx });
							grap.push_back({ ky, kx });
							pre[ky][kx] = { ny, nx };
							if (ky == 2 * HEIGHT - 1 && kx == 2 * WIDTH - 1)
							{
								bfs_object = true;
								return bfs_object;
							}
							q.push({ ky, kx });
						}
					}
					else
					{
						if (maz[ny - 1][nx] == EMPTY)
						{
							visited[ky][kx] = 1;
							grap.push_back({ ny, nx });
							grap.push_back({ ky, kx });
							pre[ky][kx] = { ny, nx };
							if (ky == 2 * HEIGHT - 1 && kx == 2 * WIDTH - 1)
							{
								bfs_object = true;
								return bfs_object;
							}
							q.push({ ky, kx });
						}

					}
				}
				if (ky == ny)
				{
					if (kx > nx)
					{
						if (maz[ny][nx + 1] == EMPTY)
						{
							visited[ky][kx] = 1;
							grap.push_back({ ny, nx });
							grap.push_back({ ky, kx });
							pre[ky][kx] = { ny, nx };
							if (ky == 2 * HEIGHT - 1 && kx == 2 * WIDTH - 1)
							{
								bfs_object = true;
								return bfs_object;
							}
							q.push({ ky, kx });
						}
					}
					else
					{
						if (maz[ny][nx - 1] == EMPTY)
						{
							visited[ky][kx] = 1;
							grap.push_back({ ny, nx });
							grap.push_back({ ky, kx });
							pre[ky][kx] = { ny, nx };
							if (ky == 2 * HEIGHT - 1 && kx == 2 * WIDTH - 1)
							{
								bfs_object = true;
								return bfs_object;
							}
							q.push({ ky, kx });
						}
					}
				}
			}
		}
	}
	return bfs_object;
}
void ofApp::bfsdraw()
{
	int Size = grap.size();
	for (int i = 0; i < Size - 1; i += 2)
	{
		ofDrawLine(grap[i].second * 10, grap[i].first * 10, grap[i + 1].second * 10, grap[i + 1].first * 10);
	}
	ofSetColor(255, 0, 0);
	ofSetLineWidth(5);
	pair <int, int> coord = { 2 * HEIGHT - 1, 2 * WIDTH - 1 };
	while (true)
	{
		ofDrawLine(coord.second * 10, coord.first * 10, pre[coord.first][coord.second].second * 10, pre[coord.first][coord.second].first * 10);
		coord = { pre[coord.first][coord.second] };
		if (coord.first == 1 && coord.second == 1)
		{
			break;
		}
	}
}