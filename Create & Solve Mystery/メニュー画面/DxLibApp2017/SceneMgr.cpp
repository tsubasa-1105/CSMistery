#include "SceneMgr.h"
#include "Menu.h"
#include "Game.h"
#include "MapEditor.h"
#include "Config.h"
#include "Help.h"
#include "DxLib.h"

static void SceneMgr_InitializeModule();	//���������W���[��
static void SceneMgr_FinalizeModule();		//�I�����W���[��
static int Select_Scene = Scene_Menu;		//���݂̃V�[��
static int Next_Scene = Scene_Nun;			//�\��̃V�[��

//������
void SceneMgr_Initialize()
{
	SceneMgr_InitializeModule();
}

//�I��
void SceneMgr_Finalize()
{
	SceneMgr_FinalizeModule();
}

//�X�V
void SceneMgr_Update()
{
	//�V�[���̕ύX����
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

//�`��
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

//�V�[���ύX�\��
void SceneMgr_SceneChange(int scene)
{
	Next_Scene = scene;
}

//���������W���[��
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

//�I�����W���[��
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