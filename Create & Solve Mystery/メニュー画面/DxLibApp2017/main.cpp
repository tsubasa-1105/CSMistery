#include "SceneMgr.h"
#include "InputRel.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(true);//�o�b�N�O���E���h�œ���
	SetOutApplicationLogValidFlag(FALSE);	//log.txt���쐬���Ȃ�
	SetMainWindowText("CSMistery");
	ChangeWindowMode(TRUE),DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	InputRel_Initialize();//������
	SceneMgr_Initialize();//������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && UpdateKey() == 0)
	{
		SceneMgr_Update();//����
		SceneMgr_Draw();//�`��
	}

	SceneMgr_Finalize();//�I��
	DxLib_End(); // DX���C�u�����I������
	return 0;
}