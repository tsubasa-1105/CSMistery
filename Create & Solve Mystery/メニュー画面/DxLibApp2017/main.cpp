#include "SceneMgr.h"
#include "InputRel.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(true);//バックグラウンドで動作
	SetOutApplicationLogValidFlag(FALSE);	//log.txtを作成しない
	SetMainWindowText("CSMistery");
	ChangeWindowMode(TRUE),DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	InputRel_Initialize();//初期化
	SceneMgr_Initialize();//初期化

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && UpdateKey() == 0)
	{
		SceneMgr_Update();//処理
		SceneMgr_Draw();//描画
	}

	SceneMgr_Finalize();//終了
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}