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

static void SceneMgr_InitializeModule();	//���������W���[��
static void SceneMgr_FinalizeModule();		//�I�����W���[��

void SceneMgr_Initialize();					//������
void SceneMgr_Finalize();					//�I��
void SceneMgr_Update();						//����
void SceneMgr_Draw();						//�`��

void SceneMgr_SceneChange(int scene);		//�V�[���̕ύX�\��
static void SceneMgr_InitializeModule();	//���������W���[��
static void SceneMgr_FinalizeModule();		//�I�����W���[��