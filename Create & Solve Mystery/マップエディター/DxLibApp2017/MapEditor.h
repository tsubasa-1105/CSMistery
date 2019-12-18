#pragma once
#pragma warning (disable : 4996)
#pragma warning (disable : 4838)

//�}�b�v�f�B�^�[��ʂ̃T�C�Y
#define EDITOR_WIDTH 1600
#define EDITOR_HEIGHT 960
#define EDITOR_DEPTH 16

//�}�b�v�̃T�C�Y
#define MAP_WIDTH 1280
#define MAP_HEIGHT 960
#define MAP_SIZE 32

//���[�h���Ԃ̗]��
#define LOADING_MARGIN 2

//�{�^���̗v�f
struct ButtonElement
{
	int x,y;
	char name[256];
	int flag;
	int color;
};

//�����蔻��`�b�v
struct HitElement
{
	int x, y;
	char name[256];
	int color;
};

//���[�h�̒�`
typedef enum
{
	Back_Edit,
	Object_Edit,
	Hit_Edit,
	Non_Edit,
	Config_Edit,
	Loading,
}Edito_Mode;

//�{�^����Ԃ̒�`
typedef enum
{
	ON,
	OFF,
}State_Button;

void MapEditor_Initialize();	//������
void MapEditor_Finalize();		//�I��
void MapEditor_Update();		//�X�V
void MapEditor_Draw();			//�`��