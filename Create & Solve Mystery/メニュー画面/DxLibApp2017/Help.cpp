#include "Help.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//������
void Help_Initialize()
{
	SetGraphMode(HELP_WIDTH, HELP_HIEGHT, HELP_DEPTH);
}

//�I��
void Help_Finalize()
{

}

//����
void Help_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//�`��
void Help_Draw()
{
	DrawString(10, 10, "�����̓w���v��ʂł�", GetColor(255, 255, 255));
	DrawString(10, 40, "ESC�L�[�Ń��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
}