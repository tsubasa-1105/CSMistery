#include "MapEditor.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//初期化
void MapEditor_Initialize()
{
	SetGraphMode(EDITOR_WIDTH, EDITOR_HIEGHT, EDITOR_DEPTH);
}

//終了
void MapEditor_Finalize()
{

}

//処理
void MapEditor_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) != 0)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//描画
void MapEditor_Draw()
{
	DrawString(10, 10, "ここはマップディター画面です", GetColor(255, 255, 255));
	DrawString(10, 40, "ESCキーでメニューに戻ります。", GetColor(255, 255, 255));
}