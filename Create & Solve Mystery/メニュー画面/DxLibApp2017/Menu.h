#pragma once

//���j���[��ʂ̃T�C�Y
#define MENU_WIDTH 640
#define MENU_HIEGHT 480
#define MENU_DEPTH 16

//�I���{�^���̈ʒu
#define MENU_BUTTON_X 0
#define MENU_BUTTON_Y 0

//�{�^���v�f
struct ButtonElement
{
	int x, y;
	char name[256];
	int color;
};

void Menu_Initialize();	//������
void Menu_Finalize();	//�I��
void Menu_Update();		//�X�V
void Menu_Draw();		//�`��