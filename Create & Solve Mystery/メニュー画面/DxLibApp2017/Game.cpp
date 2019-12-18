#include "Game.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//初期化
void Game_Initialize()
{
	SetGraphMode(GAME_WIDTH, GAME_HIEGHT, GAME_DEPTH);
}

//終了
void Game_Finalize()
{

}

//処理
void Game_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//描画
void Game_Draw()
{
	DrawString(10, 10, "ここはゲーム画面です", GetColor(255, 255, 255));
	DrawString(10, 40, "ESCキーでメニューに戻ります。", GetColor(255, 255, 255));
}