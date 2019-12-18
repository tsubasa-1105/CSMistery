#include "SceneMgr.h"
#include "Menu.h"
#include "Game.h"
#include "MapEditor.h"
#include "Config.h"
#include "Help.h"
#include "DxLib.h"

static void SceneMgr_InitializeModule();	//初期化モジュール
static void SceneMgr_FinalizeModule();		//終了モジュール
static int Select_Scene = Scene_Menu;		//現在のシーン
static int Next_Scene = Scene_Nun;			//予約のシーン

//初期化
void SceneMgr_Initialize()
{
	SceneMgr_InitializeModule();
}

//終了
void SceneMgr_Finalize()
{
	SceneMgr_FinalizeModule();
}

//更新
void SceneMgr_Update()
{
	//シーンの変更処理
	if (Next_Scene != Scene_Nun)
	{
		SceneMgr_Finalize();
		Select_Scene = Next_Scene;
		Next_Scene = Scene_Nun;
		SceneMgr_Initialize();
	}

	switch (Select_Scene)
	{
		case Scene_Menu:
			Menu_Update();
			break;
		case Scene_Game:
			Game_Update();
			break;
		case Scene_MapEditor:
			MapEditor_Update();
			break;
		case Scene_Config:
			Config_Update();
			break;
		case Scene_Help:
			Help_Update();
			break;
	}
}

//描画
void SceneMgr_Draw()
{
	switch (Select_Scene)
	{
		case Scene_Menu:
			Menu_Draw();
			break;
		case Scene_Game:
			Game_Draw();
			break;
		case Scene_MapEditor:
			MapEditor_Draw();
			break;
		case Scene_Config:
			Config_Draw();
			break;
		case Scene_Help:
			Help_Draw();
			break;
	}
}

//シーン変更予約
void SceneMgr_SceneChange(int scene)
{
	Next_Scene = scene;
}

//初期化モジュール
static void SceneMgr_InitializeModule()
{
	switch (Select_Scene)
	{
		case Scene_Menu:
			Menu_Initialize();
			break;
		case Scene_Game:
			Game_Initialize();
			break;
		case Scene_MapEditor:
			MapEditor_Initialize();
			break;
		case Scene_Config:
			Config_Initialize();
			break;
		case Scene_Help:
			Help_Initialize();
			break;
	}
}

//終了モジュール
static void SceneMgr_FinalizeModule()
{
	switch (Select_Scene)
	{
		case Scene_Menu:
			Menu_Finalize();
			break;
		case Scene_Game:
			Game_Finalize();
			break;
		case Scene_MapEditor:
			MapEditor_Finalize();
			break;
		case Scene_Config:
			Config_Finalize();
			break;
		case Scene_Help:
			Help_Finalize();
			break;
	}
}