#include "Menu.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int white = GetColor(255, 255, 255);		//���F
static struct ButtonElement button[5] =			//�{�^���쐬
{
	{ 10 + MENU_BUTTON_X,  40 + MENU_BUTTON_Y, "1 �Q�[��",white },
	{ 10 + MENU_BUTTON_X,  70 + MENU_BUTTON_Y, "2 �}�b�v�G�f�B�^�[",white },
	{ 10 + MENU_BUTTON_X, 100 + MENU_BUTTON_Y, "3 �w���v", white },
	{ 10 + MENU_BUTTON_X, 130 + MENU_BUTTON_Y, "4 �R���t�B�O",white },
	{ 10 + MENU_BUTTON_X, 160 + MENU_BUTTON_Y, "5 �I��",white },
};

//������
void Menu_Initialize()
{
	SetGraphMode(MENU_WIDTH, MENU_HIEGHT, MENU_DEPTH);
}

//�I��
void Menu_Finalize()
{

}

//����
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

//�`��
void Menu_Draw()
{
	DrawString(10, 10, "�����̓��j���[��ʂł�", white);

	//���j���[���ڂ̕\��
	for (int i = 0; i < 5; i++)
	{
		DrawString(button[i].x, button[i].y, button[i].name, button[i].color);
	}
}