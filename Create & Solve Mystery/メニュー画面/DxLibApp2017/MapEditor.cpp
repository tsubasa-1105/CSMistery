#include "MapEditor.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//������
void MapEditor_Initialize()
{
	SetGraphMode(EDITOR_WIDTH, EDITOR_HIEGHT, EDITOR_DEPTH);
}

//�I��
void MapEditor_Finalize()
{

}

//����
void MapEditor_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) != 0)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//�`��
void MapEditor_Draw()
{
	DrawString(10, 10, "�����̓}�b�v�f�B�^�[��ʂł�", GetColor(255, 255, 255));
	DrawString(10, 40, "ESC�L�[�Ń��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
}