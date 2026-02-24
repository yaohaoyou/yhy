#include<set>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<windows.h>
#include"conio.h"
using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
namespace mouse {
	int mousex() { //??o????????ox?????????o
		POINT mouse;
		GetCursorPos(&mouse);
		return mouse.x;
	}
	int mousey() { //??o????????oy?????????o
		POINT mouse;
		GetCursorPos(&mouse);
		return mouse.y;
	}
	void move(int x,int y) { //3???2000 ???a1200
		SetCursorPos(x,y);
	}
	void leftdown() { //???????????????1
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	}
	void leftup() { //???|?a?????????1
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	void rightdown() { //????????????????1
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	}
	void rightup() { //???|?a??????????1
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	bool clickL() { //?D????o????????o??o????????????????????1
		return (KEY_DOWN(MOUSE_MOVED));
	}
	bool clickR() { //?D????o????????o??o?????????????????????1
		return (KEY_DOWN(MOUSE_EVENT));
	}
	bool clickM() { //?D????o????????o??o???????????1???
		return (KEY_DOWN(MOUSE_WHEELED));
	}
}
namespace cursor {
	void hide() { /*????t2?1a?????o*/
		CONSOLE_CURSOR_INFO cursor_info= {1,0};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
	}
	void show() {
		CONSOLE_CURSOR_INFO cursor_info= {1,1};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
	}
	void gotoxy(int y,int x) { //1a?????o|??????xDDy????D
		COORD position;
		position.X=x;
		position.Y=y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	}
}
namespace rect {
	RECT GetWindowRect2(HWND hwnd) {
		RECT rt;
		GetWindowRect(hwnd,&rt);
		return rt;
	}
	LONG GetWindowWidth(HWND hwnd) {
		RECT rect=GetWindowRect2(hwnd);
		return (rect.right - rect.left);
	}
	LONG GetWindowHeight(HWND hwnd) {
		RECT rect=GetWindowRect2(hwnd);
		return (rect.bottom - rect.top);
	}
	WINBOOL MoveWindow2(HWND hwnd,int X,int Y,bool bRepaint) {
		LONG w,h;
		w=GetWindowWidth(hwnd);
		h=GetWindowHeight(hwnd);
		MoveWindow(hwnd,X,Y,w,h,bRepaint);
	}
	void move(int x,int y) { //????????????????????x,y(????????|???0,0  ???????????2000,1200)
		MoveWindow2(GetConsoleWindow(),x,y,TRUE);
	}
	void turn_size(int x,int y) { //???????????????a3???x???ay(?y3???3???120???a30)
		char s[50];
		sprintf(s,"mode con cols=%d lines=%d",x,y);
		const char *ss=s;
		system(ss);
	}
	string title() {
		char c[255];
		GetConsoleTitle(c,255);
		string s=c;
		return s;
	}
	void turn_title(string s) {
		char c[255]="";
		for(int i=0; i<s.size(); i++) {
			c[i]=s[i];
		}
		SetConsoleTitle(c);
	}
}
namespace keyboard {
	void keydown(char c) { //?????????????1c    (??3|?? 0x0d)
		keybd_event(c, 0, 0, 0);
	}
	void keyup(char c) { //???|?a???????1c
		keybd_event(c, 0, 2, 0);
	}
}
namespace color {
	void color(int x) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
}
char hit;
void *KBhit(void *arg) {
	while(1) {
		mouse::move(1600,250);
		Sleep(100);
	}
	return 0;
}
void key(char c) {
	keyboard::keydown(c);
	keyboard::keyup(c);
	Sleep(50);
}
void Ks(string s) {
	for(int i=0; i<s.size(); i++) {
		if(s[i]=='.') {
			key(110);
		} else if(s[i]>='a'&&s[i]<='z') {
			key(s[i]-'a'+'A');
		} else {
			key(s[i]);
		}
	}
}
void printtime(){
	time_t cur_time;
    time(&cur_time);
	printf("%s",ctime(&cur_time));
}
int main(){
	time_t cur_time;
    time(&cur_time);
	// while(1){
		// if(!(GetAsyncKeyState(120)&(0x8000)))	continue;
		// Sleep(1000);
		// key(VK_LWIN);

		// Sleep(500);

		// key(VK_LWIN);
		// printtime();
		// puts("防机惨已开启");
		
		// int x=mouse::mousex(),y=mouse::mousey();
		bool flag=0;
		while(1){
			flag=0;
			if(mouse::clickL()||mouse::clickR()||mouse::clickM()){
				printtime();
				puts("你被机惨了1");
				puts("");
				LockWorkStation();
				flag=1;
			}
			for(int i=1;i<=300;i++){
				if(i==13)	continue;
				if(GetAsyncKeyState(34)&(0x8000)){
					printtime();
					puts("防机惨已关闭");
					puts("");
					return 0;
				}
				if(GetAsyncKeyState(i)&(0x8000)){
					printtime();
					puts("你被机惨了2");
					puts("");
					LockWorkStation();
					flag=1;
					break;
				}
			}
		}
	// }
}
