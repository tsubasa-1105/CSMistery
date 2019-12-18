#pragma once

typedef enum
{
	Scene_Menu,
	Scene_Game,
	Scene_MapEditor,
	Scene_Config,
	Scene_Help,
	Scene_Nun,

}Scene_Element;

static void SceneMgr_InitializeModule();	//初期化モジュール
static void SceneMgr_FinalizeModule();		//終了モジュール

void SceneMgr_Initialize();					//初期化
void SceneMgr_Finalize();					//終了
void SceneMgr_Update();						//処理
void SceneMgr_Draw();						//描画

void SceneMgr_SceneChange(int scene);		//シーンの変更予約
static void SceneMgr_InitializeModule();	//初期化モジュール
static void SceneMgr_FinalizeModule();		//終了モジュール