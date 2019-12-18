#include "Help.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//初期化
void Help_Initialize()
{
	SetGraphMode(HELP_WIDTH, HELP_HIEGHT, HELP_DEPTH);
}

//終了
void Help_Finalize()
{

}

//処理
void Help_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//描画
void Help_Draw()
{
	DrawString(10, 10, "ここはヘルプ画面です", GetColor(255, 255, 255));
	DrawString(10, 40, "ESCキーでメニューに戻ります。", GetColor(255, 255, 255));
}