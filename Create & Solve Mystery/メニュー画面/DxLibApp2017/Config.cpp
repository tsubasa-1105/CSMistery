#include "Config.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//初期化
void Config_Initialize()
{
	SetGraphMode(CONFIG_WIDTH, CONFIG_HIEGHT, CONFIG_DEPTH);
}

//終了
void Config_Finalize()
{

}

//処理
void Config_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//描画
void Config_Draw()
{
	DrawString(10, 10, "ここはコンフィグ画面です", GetColor(255, 255, 255));
	DrawString(10, 40, "ESCキーでメニューに戻ります。", GetColor(255, 255, 255));
}