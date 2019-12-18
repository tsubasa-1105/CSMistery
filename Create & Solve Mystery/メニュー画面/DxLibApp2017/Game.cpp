#include "Game.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//������
void Game_Initialize()
{
	SetGraphMode(GAME_WIDTH, GAME_HIEGHT, GAME_DEPTH);
}

//�I��
void Game_Finalize()
{

}

//����
void Game_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//�`��
void Game_Draw()
{
	DrawString(10, 10, "�����̓Q�[����ʂł�", GetColor(255, 255, 255));
	DrawString(10, 40, "ESC�L�[�Ń��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
}