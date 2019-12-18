#include "Config.h"
#include "InputRel.h"
#include "SceneMgr.h"
#include "DxLib.h"

//������
void Config_Initialize()
{
	SetGraphMode(CONFIG_WIDTH, CONFIG_HIEGHT, CONFIG_DEPTH);
}

//�I��
void Config_Finalize()
{

}

//����
void Config_Update()
{
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_SceneChange(Scene_Menu);
	}
}

//�`��
void Config_Draw()
{
	DrawString(10, 10, "�����̓R���t�B�O��ʂł�", GetColor(255, 255, 255));
	DrawString(10, 40, "ESC�L�[�Ń��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
}