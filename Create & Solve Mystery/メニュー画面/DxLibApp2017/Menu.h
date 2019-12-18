#pragma once

//メニュー画面のサイズ
#define MENU_WIDTH 640
#define MENU_HIEGHT 480
#define MENU_DEPTH 16

//選択ボタンの位置
#define MENU_BUTTON_X 0
#define MENU_BUTTON_Y 0

//ボタン要素
struct ButtonElement
{
	int x, y;
	char name[256];
	int color;
};

void Menu_Initialize();	//初期化
void Menu_Finalize();	//終了
void Menu_Update();		//更新
void Menu_Draw();		//描画