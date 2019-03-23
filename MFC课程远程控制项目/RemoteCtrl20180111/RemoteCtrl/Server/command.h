#pragma once
#include <Windows.h>
/////////////////////////////////
#define PEER_SCREEN_GET			0
#define PEER_SCREEN_SEND		1
//////////////////////////////////
#define PEER_MOUSE_LEFTDOWN		2
#define PEER_MOUSE_LEFTUP		3
#define PEER_MOUSE_RIGHTDOWN	4
#define PEER_MOUSE_RIGHTUP		5
#define PEER_MOUSE_MIDDLEDOWN	6
#define PEER_MOUSE_MIDDLEUP		7
#define PEER_MOUSE_LDBCLICK		8
#define PEER_MOUSE_RDBCLICK		9
#define PEER_MOUSE_MDBCLICK		10
#define PEER_MOUSE_MOVE			11
//////////////////////////////////
#define PEER_KEY_DOWN			12
#define PEER_KEY_UP				13
//////////////////////////////////
#define PEER_KEYMOUSE			32

typedef struct tagCommand
{
	/////命令ID值//////
	int CommandID;
	/////后接数据大小//
	DWORD DataSize;
}COMMAND;


typedef struct tagKeyMouse
{
	int style;
	///mouse///
	int x,y;
	int ctrl;
	///key////
	int nkey;
}KEYMOUSE;

typedef struct tagScreen
{
	///bmp////
	DWORD BmpSize;
	DWORD BmpInfoSize;
	DWORD BmpCX;
	DWORD BmpCY;
}SCREEN;