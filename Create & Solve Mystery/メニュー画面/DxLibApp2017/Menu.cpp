#include "Menu.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int white = GetColor(255, 255, 255);		//白色
static struct ButtonElement button[5] =			//ボタン作成
{
	{ 10 + MENU_BUTTON_X,  40 + MENU_BUTTON_Y, "1 ゲーム",white },
	{ 10 + MENU_BUTTON_X,  70 + MENU_BUTTON_Y, "2 マップエディター",white },
	{ 10 + MENU_BUTTON_X, 100 + MENU_BUTTON_Y, "3 ヘルプ", white },
	{ 10 + MENU_BUTTON_X, 130 + MENU_BUTTON_Y, "4 コンフィグ",white },
	{ 10 + MENU_BUTTON_X, 160 + MENU_BUTTON_Y, "5 終了",white },
};

//初期化
void Menu_Initialize()
{
	SetGraphMode(MENU_WIDTH, MENU_HIEGHT, MENU_DEPTH);
}

//終了
void Menu_Finalize()
{

}

//処理
void Menu_Update()
{
	if (KeyState(KEY_INPUT_1) == 1)
	{
		SceneMgr_SceneChange(Scene_Game);
	}
	if (KeyState(KEY_INPUT_2) == 1)
	{
		SceneMgr_SceneChange(Scene_MapEditor);
	}
	if (KeyState(KEY_INPUT_3) == 1)
	{
		SceneMgr_SceneChange(Scene_Help);
	}
	if (KeyState(KEY_INPUT_4) == 1)
	{
		SceneMgr_SceneChange(Scene_Config);
	}
	if (KeyState(KEY_INPUT_5) == 1)
	{
		SceneMgr_Finalize();
		DxLib_End();
	}
}

//描画
void Menu_Draw()
{
	DrawString(10, 10, "ここはメニュー画面です", white);

	//メニュー項目の表示
	for (int i = 0; i < 5; i++)
	{
		DrawString(button[i].x, button[i].y, button[i].name, button[i].color);
	}
}