#include <stdio.h>
#include <ctype.h>
#include "MapEditor.h"
#include "InputRel.h"
#include "DxLib.h"

static ButtonElement big_button[3] =
{
	{1536, 50,"�w�i",0,GetColor(255,98,50)},
	{1536, 150,"����",0,GetColor(251,236,53)},
	{1536, 250,"����",0,GetColor(50,204,18)},
};

static ButtonElement min_button[6] =
{
	{ 1472, 704,"�ۑ�",0,GetColor(255,255,255) },
	{ 1472, 768,"�폜",0,GetColor(255,255,255) },
	{ 1472, 832,"�ݒ�",0,GetColor(255,255,255) },
	{ 1472, 896,"�I��",0,GetColor(255,255,255) },
	{ 1456, 896,"�ݒ�I��",0,GetColor(255,255,255) },
	{ 1456, 832,"�ݒ�ۑ�",0,GetColor(255,255,255) },
};

#define HC_NUM 2

static HitElement hit_chip[HC_NUM] =
{
	{ 1312, 32,"�ʂ��ꏊ",GetColor(251,231,49) },
	{ 1312, 96,"�ʂ�Ȃ��ꏊ",GetColor(178,0,8) },
	//{ 1312, 160,"�_�~�[",GetColor(39,38,114) },
};

#define CF_NUM 13
static ButtonElement config_menu[CF_NUM] =
{
	{ 120,120,"�}�b�v�G�f�B�^�[�̃}�X�ڂ�\������",OFF,GetColor(255,255,255)},
	{ 120,180,"�}�b�v�`�b�v�����̃}�X�ڂ�\������",ON,GetColor(255,255,255)},
	{ 120,240,"�}�E�X�̍��W��\������",OFF ,GetColor(255,255,255)},
	{ 120,300,"BGM�𗬂�",ON ,GetColor(255,255,255)},
	{ 120,360,"SE�𗬂�",ON ,GetColor(255,255,255) },
	{ 120,420,"�ǂݍ��݃��b�Z�[�W��\������",OFF,GetColor(255,255,255) },
	{ 120,480,"�t�@�C���̕ۑ�������������",ON ,GetColor(255,255,255) },
	{ 120,540,"�t�@�C���̍폜������������",OFF,GetColor(255,255,255) },
	{ 120,600,"�G�f�B�^�[�I��������������",ON,GetColor(255,255,255) },
	{ 120,660,"�h��Ƃ��Ɍ��ʉ�������",ON,GetColor(255,255,255) },
	{ 560,120,"�N�����Ԃ̒Z�k",OFF,GetColor(255,255,255) },
	{ 560,180,"�I�����Ƀ}�b�v�f�[�^�������ŕۑ�����",ON,GetColor(255,255,255) },
	{ 560,240,"�w�i���[�h�ɃI�u�W�F�N�g��\������",ON,GetColor(255,255,255) },
};

static int BackData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE];//�w�i�f�[�^
static int MapData[MAP_HEIGHT /MAP_SIZE][MAP_WIDTH/MAP_SIZE];	//�I�u�W�F�N�g�f�[�^
static int HitData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE];//�����蔻��f�[�^
static int back_color;			//�w�i�F�w��
static int time1, time2, t_time;//���ԊǗ�
static int time_d;				//double�^���ԊǗ��ϐ�
static int Check_Image;			//�`�F�b�N�}�[�N�̉摜�n���h��
static int Stop_Update;			//�A�b�v�f�[�g���s�������Ǘ�����ϐ�
static int b_block;				//�w�i�u���b�N
static int SelectMode;			//�G�f�B�^�[���[�h�Ǘ��ϐ�
static int SelectBlock;			//�I�����Ă���}�b�v�`�b�v
static int SelectHitBlock;		//�I�����Ă��铖���蔻��u���b�N
static int mcImage[300];		//�}�b�v�`�b�v�C���[�W
static int bImage[18];			//�w�i�摜�̃C���[�W
static int map_x, map_y;		//�}�b�v�̏c���}�X��
static int MoveY;				//�}�b�v�`�b�v�̈ړ���
static int MouseX, MouseY;		//�}�E�X�̍��W
static int tMouseX, tMouseY;	//�}�E�X�̍��W�_�~�[
static int MouseCount;			//�}�E�X���O�t���[���Ɠ������W�ɂ��邩�𒲂ׂ�
static int SelectBGM;			//�I������Ă���BGM
static int LoadImageHandle[60];	//���[�h��ʗp�̉摜�n���h��
static int HitImageHandle[3];	//�����蔻��p�̉摜�n���h��
static int LoadEnd;				//���[�h�̏I���t���O
static int BgmHandle00;			//BGM�p�n���h��
static int BgmHandle01;			//BGM�p�n���h��
static int BgmHandle02;			//BGM�p�n���h��
static int BgmHandle03;			//BGM�p�n���h��
static int BgmHandle04;			//BGM�p�n���h��
static int SeHandle01;			//SE�p�n���h��
static int SeHandle02;			//SE�p�n���h��
static int SeHandle03;			//SE�p�n���h��
static int SeHandle04;			//SE�p�n���h��
static int SeHandle05;			//SE�p�n���h��
static int SeHandle06;			//SE�p�n���h��
static int SeHandle07;			//SE�p�n���h��
static int SeHandle08;			//SE�p�n���h��
static int SeHandle09;			//SE�p�n���h��
static int SeHandle10;			//SE�p�n���h��
static int SeHandle11;			//SE�p�n���h��
static int SeHandle12;			//SE�p�n���h��
static int BgmVolume;			//���݂�BGM���ʂ��Ǘ�����
static int SeVolume;			//���݂�SE���ʂ��Ǘ�����
static int MessageFlag[2];		//���b�Z�[�W�t���O

static void Load_MapData();					//�}�b�v�f�[�^��ǂݍ���
static void Output_MapData();				//�}�b�v�f�[�^���o�͂���
static int  Load_Config();					//�R���t�B�O�t�@�C����ǂݍ���
static void Output_Config();				//�R���t�B�O�t�@�C�����o�͂���
static void Eliminate_MapData();			//�f�[�^�z������Z�b�g����
static void MousePoint_Draw(int x,int y);	//�w��̍��W�Ƀ}�E�X���W��\������
static void Button_Update();				//�{�^���֘A�̏���
static void Button_Draw();					//�{�^���֘A�̕`��
static void BackMode_Update();				//�w�i���[�h�̏���
static void BackMode_Draw();				//�w�i���[�h�̕`��
static void ObjectMode_Update();			//�I�u�W�F�N�g���[�h�̏���
static void ObjectMode_Draw();				//�I�u�W�F�N�g���[�h�̕`��
static void HitMode_Update();				//�����蔻�胂�[�h�̏���
static void HitMode_Draw();					//�����蔻�胂�[�h�̕`��
static void ConfigMode_Update();			//�R���t�B�O���[�h����
static void ConfigMode_Draw();				//�R���t�B�O���[�h�`��
static void End_Editor();					//�G�f�B�^�[�I������
static void Save_Update();					//�ۑ��̏���
static void Eliminate_Update();				//�}�b�v�f�[�^�̍폜����
static void Config_State();					//�R���t�B�O��ʂ��Ăяo��
static void Config_End();					//�R���t�B�O��ʂ��I������
static void Config_Save();					//�R���t�B�O��ʂ�ۑ�����
static void LoadMessage();					//�t�@�C����ǂݍ��񂾍ۂ̃��b�Z�[�W
static void ChangeBGM(int number);			//����Ă���BGM��ύX����
static void AdjustmentBGMVolume(int volume);//���ׂĂ�BGM�n���h���̉��ʂ𒲐߂���
static void AdjustmentSEVolume(int volume);	//���ׂĂ�SE�n���h���̉��ʂ𒲐߂���
static void Music_Initialize();				//���y�֌W�̏��������s��											
static void LoadFile_InitializeModule();	//���[�h�t�@�C���֌W�̃��W���[��
static void Reset_Initialize();				//�ϐ���������
static void LoadMaterial();					//���[�h��ʂ̑f�ނ��ɓǂݍ���
static void LoadScreen();					//���[�h��ʂ�\������

//������
void MapEditor_Initialize()
{
	SetUseASyncLoadFlag(TRUE);	//�񓯊��ǂݍ���

	SetGraphMode(EDITOR_WIDTH, EDITOR_HEIGHT, EDITOR_DEPTH);	//��ʃT�C�Y�ύX
	Reset_Initialize(); //�ϐ��̏�����
	LoadMaterial();		//���[�h��ʂ̑f�ނ�ǂݍ���

	Music_Initialize();	//���y�֌W�̃��[�h
	LoadFile_InitializeModule(); //�t�@�C���ǂݍ���

	if (BgmVolume < 80 || 230 < BgmVolume)SelectBGM = 140;	//�{�����[���̒���
	if (SeVolume < 80 || 230 < SeVolume)SelectBGM = 140;	//�{�����[���̒���
	if (SelectBGM < 0 || 4 < SelectBGM)SelectBGM = 0;		//�I��BGM�̒���

	Check_Image = LoadGraph("Data/Picture/Check.png");
	LoadDivGraph("Data/Picture/background.png", 18, 6, 3, 32, 32, bImage);
	LoadDivGraph("Data/Picture/MapChip.png",300,20,15,32,32,mcImage);
	LoadDivGraph("Data/Picture/hit_block.png", 3, 3, 1, 32, 32, HitImageHandle);
	SetUseASyncLoadFlag(FALSE);	//�����ǂݍ���
	LoadEnd = 1;
	time1 = GetNowCount();
}

//�I��
void MapEditor_Finalize()
{
	SetUseASyncLoadFlag(FALSE);
	DeleteGraph(Check_Image);
	InitSoundMem();
}

//����
void MapEditor_Update()
{
	//�}�E�X�̍��W���擾����
	MousePoint(&MouseX, &MouseY);

	//���[�h��ʂ̓ǂݍ���
	if (Stop_Update == 0)
	{
		//���[�h���Ƃ̏���
		if (SelectMode == Back_Edit) BackMode_Update();
		if (SelectMode == Object_Edit) ObjectMode_Update();
		if (SelectMode == Hit_Edit) HitMode_Update();
		if (SelectMode == Config_Edit) ConfigMode_Update();
		if (SelectMode == Loading) LoadScreen();

		//�{�^���֘A�̏���
		if(SelectMode != Config_Edit && SelectMode != Loading) Button_Update();
	}
	//�}�E�X�̍��W���擾����
	MousePoint(&tMouseX, &tMouseY);
}

//�`��
void MapEditor_Draw()
{
	if (SelectMode != Loading)
	{
		//�G�f�B�^�[�w�i�F�`��
		DrawBox(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT, back_color, TRUE);

		//���[�h���Ƃɕ`��
		if (SelectMode == Back_Edit) BackMode_Draw();
		if (SelectMode == Object_Edit) ObjectMode_Draw();
		if (SelectMode == Hit_Edit) HitMode_Draw();
		if (SelectMode == Config_Edit) ConfigMode_Draw();

		if (SelectMode != Config_Edit)
		{
			//�{�^���֘A�̕`��
			Button_Draw();
			//�}�E�X���W�̕\��
			if(Stop_Update == 0 && config_menu[2].flag == ON) MousePoint_Draw(1500, 10);
			//�{�^�����͎��̏���
			if (min_button[0].flag == 1 && Stop_Update == 1) Save_Update();
			if (min_button[1].flag == 1 && Stop_Update == 1) Eliminate_Update();
			if (min_button[2].flag == 1 && Stop_Update == 1) Config_State();
			if (min_button[3].flag == 1 && Stop_Update == 1) End_Editor();
		}
		else
		{
			if (min_button[4].flag == 1 && Stop_Update == 1) Config_End();
			if (min_button[5].flag == 1 && Stop_Update == 1) Config_Save();
		}
		if (MessageFlag[0] == 1 || MessageFlag[0] == 1) LoadMessage();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(true);//�o�b�N�O���E���h�œ���
	//SetOutApplicationLogValidFlag(FALSE);	//log.txt���쐬���Ȃ�
	SetMainWindowText("CSMistery");
	ChangeWindowMode(TRUE),DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	InputRel_Initialize();//������
	MapEditor_Initialize();//������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && UpdateKey() == 0)
	{
		MapEditor_Update();//����
		MapEditor_Draw();//�`��
	}

	MapEditor_Finalize();//�I��
	DxLib_End(); // DX���C�u�����I������
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////

//�}�b�v�f�[�^��ǂݍ���
static void Load_MapData()
{
	FILE *fp1, *fp2, *fp3;
	int i = 0, tmp;
	char data[5];
	fp1 = fopen("MapData.csv", "r");
	fp2 = fopen("MapData.txt", "w");

	while ((tmp = fgetc(fp1)) != EOF)
	{
		if (tmp == '\n' && i == 0);
		else if (isdigit(tmp))
		{
			data[i] = (char)tmp;
			i++;
		}
		else
		{
			data[i] = '\0';
			fprintf(fp2, "%d\n", atoi(data));
			i = 0;
		}
	}
	fclose(fp1);
	fclose(fp2);

	fp3 = fopen("MapData.txt", "r");

	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fscanf(fp3, "%d\n", &BackData[i][j]);
		}
	}

	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fscanf(fp3, "%d\n", &MapData[i][j]);
		}
	}

	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fscanf(fp3, "%d\n", &HitData[i][j]);
		}
	}
	fclose(fp3);
	remove("MapData.txt");
}

//�t�@�C�����o�͂���
static void Output_MapData()
{
	FILE *fp;
	fp = fopen("MapData.csv", "w");

	//�w�i�f�[�^�o��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fprintf(fp, "%d", BackData[i][j]);
			if (j != map_x - 1) fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}

	fprintf(fp, "\n");

	//�I�u�W�F�N�g�f�[�^�o��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fprintf(fp, "%d", MapData[i][j]);
			if (j != map_x-1) fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}

	fprintf(fp, "\n");

	//�����蔻��f�[�^�o��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			fprintf(fp, "%d", HitData[i][j]);
			if (j != map_x-1) fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

//�R���t�B�O�t�@�C����ǂݍ���
static int Load_Config()
{
	FILE *fp;
	fp = fopen("Config.dat", "r");

	if (fp == NULL) return -1;
	else
	{
		for (int i = 0; i < CF_NUM; i++)
		{
			fscanf(fp, "%d,",&config_menu[i].flag);
		}
		fscanf(fp, "%d,", &SelectBGM);
		fscanf(fp, "%d,", &BgmVolume);
		fscanf(fp, "%d", &SeVolume);
		fclose(fp);
	}
	return 0;
}

//�R���t�B�O���o�͂���
static void Output_Config()
{
	FILE *fp;
	fp = fopen("Config.dat", "w");

	for (int i = 0; i < CF_NUM; i++)
	{
		fprintf(fp, "%d,", config_menu[i].flag);
	}
	fprintf(fp, "%d,", SelectBGM);
	fprintf(fp, "%d,", BgmVolume);
	fprintf(fp, "%d", SeVolume);
	fclose(fp);
}

//�f�[�^�z������Z�b�g����
static void Eliminate_MapData()
{
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			BackData[i][j] = 0;
			MapData[i][j] = 0;
			HitData[i][j] = 0;
		}
	}
	SelectBlock = 0;
	b_block = 0;
}

//�}�E�X���W��\��
static void MousePoint_Draw(int x,int y)
{
	DrawFormatString(x, y, GetColor(255, 255, 255), "(%d,%d)", MouseX, MouseY);
}

//�{�^���֘A�̏���
static void Button_Update()
{
	//�I�����[�h�֘A
	switch (SelectMode)
	{
		case Back_Edit:
			big_button[0].x = 1504;
			big_button[1].x = 1536;
			big_button[2].x = 1536;
			break;
		case Object_Edit:
			big_button[0].x = 1536;
			big_button[1].x = 1504;
			big_button[2].x = 1536;
			break;
		case Hit_Edit:
			big_button[0].x = 1536;
			big_button[1].x = 1536;
			big_button[2].x = 1504;
			break;
	}

	//�}�E�X���E�N���b�N���ꂽ�u��
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//���[�h�ؑփ{�^���̏���
		for (int i = 0; i < 3; i++)
		{
			if (big_button[i].x < MouseX && MouseX < EDITOR_WIDTH && big_button[i].y < MouseY && MouseY < big_button[i].y + 60)
			{
				if (i != SelectMode && config_menu[4].flag == ON)PlaySoundMem(SeHandle10, DX_PLAYTYPE_BACK);
				switch (i) {
					case 0:
						SelectMode = Back_Edit;
						break;
					case 1:
						SelectMode = Object_Edit;
						break;
					case 2:
						SelectMode = Hit_Edit;
						break;
				}
			}
		}

		//�T�u�{�^�����͎�
		for (int i = 0; i < 4; i++)
		{
			if (min_button[i].x - 16 <= MouseX && MouseX <= min_button[i].x + 16 && min_button[i].y - 16 <= MouseY && MouseY <= min_button[i].y + 16)
			{
				if (config_menu[4].flag == ON)PlaySoundMem(SeHandle02, DX_PLAYTYPE_BACK);
				min_button[i].flag = 1;
				Stop_Update = 1;
				time1 = GetNowCount();
			}
		}
	}

	if (KeyState(KEY_INPUT_0) == 1)ChangeBGM(0);
	if (KeyState(KEY_INPUT_1) == 1)ChangeBGM(1);
	if (KeyState(KEY_INPUT_2) == 1)ChangeBGM(2);
	if (KeyState(KEY_INPUT_3) == 1)ChangeBGM(3);
	if (KeyState(KEY_INPUT_4) == 1)ChangeBGM(4);
}

//�{�^���֘A�̕`��
static void Button_Draw()
{
	//���[�h�ؑփ{�^���̕`��
	for (int i = 0; i < 3; i++)
	{
		DrawBox(big_button[i].x, big_button[i].y, 1600, big_button[i].y + 60, big_button[i].color, TRUE);
		DrawString(big_button[i].x, big_button[i].y + 70, big_button[i].name, GetColor(255, 255, 255));
	}

	//�T�u�{�^���̕`��
	for (int i = 0; i < 4; i++)
	{
		if (min_button[i].flag == 0)
		{
			DrawCircleAA((float)min_button[i].x, (float)min_button[i].y, 16, 120, min_button[i].color, TRUE);
			DrawString(min_button[i].x + 32, min_button[i].y - 8, min_button[i].name, min_button[i].color);
		}
		else
		{
			DrawCircleAA((float)min_button[i].x, (float)min_button[i].y, 16, 120, GetColor(116, 169, 214), TRUE);
			DrawString(min_button[i].x + 32, min_button[i].y - 8, min_button[i].name, GetColor(116, 169, 214));
		}
	}
}

//�w�i���[�h�̏���
static void BackMode_Update()
{
	//�}�E�X�����͂��ꂽ�u��
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//�}�b�v�`�b�v�I��
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (1312 + 62 * j < MouseX && MouseX < 1312 + 62 * j + 32 && 32 + i * 62 < MouseY && MouseY < 32 + i * 62 + 32)
				{
					if (config_menu[4].flag == ON && b_block != i*2+j) PlaySoundMem(SeHandle08, DX_PLAYTYPE_BACK);
					b_block = i * 2 + j;
				}

			}
		}
	}

	//�}�E�X�E�������Ă����
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//�}�b�v��h��Ԃ�
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if (config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			BackData[(MouseY / 32) % 30][(MouseX / 32) % 40] = b_block;
		}

	}
}

//�w�i���[�h�̕`��
static void BackMode_Draw()
{
	//�w�i�}�b�v�\��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//�w�i�`��
			DrawGraph(j * 32, i * 32, bImage[BackData[i][j]], FALSE);
			if (config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32 + 33, i * 32 + 33, GetColor(255, 255, 255), FALSE);
			//�摜
			if (config_menu[12].flag == ON)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
				DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
			//�g��
			if (config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32 + 33, i * 32 + 33, GetColor(255, 255, 255), FALSE);
		}
	}

	//�w�i�`�b�v�̕\��
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DrawGraph(1312 + 62*j, 32+i*62, bImage[i*2+j], FALSE);
			if ((i * 2 + j) == b_block)
			{
				DrawBox(1312 + 62 * j, 32 + i * 62, 1312 + 62 * j + 32, 32 + i * 62 + 32, GetColor(255, 0, 0), FALSE);
			}
			else
			{
				DrawBox(1312 + 62 * j, 32 + i * 62, 1312 + 62 * j + 32, 32 + i * 62 + 32, GetColor(0, 0, 0), FALSE);
			}
		}
	}

}

//�I�u�W�F�N�g���[�h����
static void ObjectMode_Update()
{
	//�}�b�v�`�b�v�ړ�(�L�[����)
	if (KeyState(KEY_INPUT_UP) != 0) MoveY += 30;
	if (KeyState(KEY_INPUT_DOWN) != 0) MoveY -= 30;

	//�}�b�v�`�b�v�ړ�(�}�E�X�z�C�[��)
	if (1312 < MouseX && MouseX < 1408 && 32 < MouseY && MouseY < EDITOR_HEIGHT - 32)
	{
		MoveY += 20 * GetMouseWheelRotVol();
	}
	GetMouseWheelRotVol();

	//�}�b�v�`�b�v�ړ�����
	if (MoveY >= 0) MoveY = 0;
	if (MoveY*(-1) >= 2304) MoveY = -2304;

	//�}�E�X���E�N���b�N���ꂽ�u��
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//�u���b�N�I��
		if (1312 < MouseX && MouseX < 1408 && 32 < MouseY && MouseY < EDITOR_HEIGHT - 32)
		{
			if (config_menu[4].flag == ON && SelectBlock != (((MouseY - MoveY - 32) / 32) * 3 + ((MouseX - 1312) / 32) % 3)) PlaySoundMem(SeHandle08, DX_PLAYTYPE_BACK);
			SelectBlock = ((MouseY - MoveY - 32) / 32) * 3 + ((MouseX - 1312) / 32) % 3;
		}
	}

	//�}�E�X�E�������Ă����
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//�}�b�v��h��Ԃ�
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if(config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			MapData[(MouseY / 32) % 30][(MouseX / 32) % 40] = SelectBlock;
		}

	}

}

//�I�u�W�F�N�g���[�h�`��
static void ObjectMode_Draw()
{
	//�w�i�}�b�v�\��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			DrawGraph(j * 32, i * 32, bImage[BackData[i][j]], FALSE);
		}
	}

	//�}�b�v�\��
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//�摜
			DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
			//�g��
			if(config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32+33, i * 32+33,GetColor(255,255,255), FALSE);
		}
	}

	//�}�b�v�`�b�v�w�i
	//DrawBox(1312, 32, 1408, EDITOR_HEIGHT - 32, GetColor(231,232,226), TRUE);

	//�}�b�v�`�b�v�\��
	for (int i = 0; i < map_y / 2; i++)
	{
		for (int j = 0; j < map_x / 2; j++)
		{
			//�摜
			DrawGraph(1312 + ((i * 20 + j) % 3) * 32, 32 + ((i * 20 + j) / 3) * 32 + MoveY, mcImage[i * 20 + j], TRUE);
			//�g��
			if (config_menu[1].flag == ON) DrawBox(1312 + ((i * 20 + j) % 3) * 32, 32 + ((i * 20 + j) / 3) * 32 + MoveY, 1312 + ((i * 20 + j) % 3) * 32 + 33, 32 + ((i * 20 + j) / 3) * 32 + MoveY + 33,GetColor(76,76,76), FALSE);
		}
	}

	//�}�b�v�`�b�v�O�g
	DrawBox(1312, 32, 1408, EDITOR_HEIGHT - 32, GetColor(76,76,76), FALSE);
	DrawBox(1312-1, 32-1, 1408+1, EDITOR_HEIGHT - 32+1, GetColor(76,76,76), FALSE);

	//�I���}�b�v�`�b�v�ɐԘg������
	DrawBox(1312 + (SelectBlock % 3) * 32, 32 + (SelectBlock / 3) * 32 + MoveY, 1312 + (SelectBlock % 3) * 32 + 33, 32 + (SelectBlock / 3) * 32 + 33 + MoveY, GetColor(255, 0, 0), FALSE);
	//�}�b�v�`�b�v�̖ډB�����㉺�ɍ쐬
	DrawBox(1312, 0, 1409, 32, back_color, TRUE);
	DrawBox(1312, EDITOR_HEIGHT - 31, 1409, EDITOR_HEIGHT, back_color, TRUE);
	//�I���}�b�v�`�b�v�̕\��
	DrawFormatString(1428+10, 42, GetColor(255, 255, 255), "%d", SelectBlock);
	//�}�b�v�`�b�v�ʒu�o�[�w�i�\��
	DrawBox(1418, 32, 1427, EDITOR_HEIGHT - 32, GetColor(76,76,76),TRUE);
	//�ʒu�\���o�[
	DrawCircleAA((float)1422, (float)(35 - MoveY/2.59), 3, 120, GetColor(255, 255, 255), TRUE);
}

//�����蔻�胂�[�h�̏���
static void HitMode_Update()
{
	//�}�E�X���������u��
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		for (int i = 0; i < HC_NUM; i++)
		{
			//�q�b�g�`�b�v�I��
			if (hit_chip[i].x < MouseX && MouseX < hit_chip[i].x + 32 && hit_chip[i].y < MouseY && MouseY < hit_chip[i].y + 32)
			{
				if (config_menu[4].flag == ON && SelectHitBlock != i) PlaySoundMem(SeHandle08, DX_PLAYTYPE_BACK);
				SelectHitBlock = i;
			}
		}
	}

	//�}�E�X�E�������Ă����
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//�}�b�v��h��Ԃ�
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if (config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			HitData[(MouseY / 32) % 30][(MouseX / 32) % 40] = SelectHitBlock;
		}
	}
}

//�����蔻�胂�[�h�̕`��
static void HitMode_Draw()
{
	//�w�i�F�`��
	DrawBox(0, 0, 1280, 960, GetColor(255,255,255), TRUE);

	//�}�b�v�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//�摜
			DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
			//�g��
			DrawBox(j * 32, i * 32, j * 32+33, i * 32+33,back_color, FALSE);
		}
	}

	//�����蔻��ӏ��\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//�摜
			DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32,hit_chip[HitData[i][j]].color, TRUE);
			DrawGraph(j * 32-2, i * 32, HitImageHandle[HitData[i][j]], TRUE);
		}
	}

	//�����蔻��}�b�v�`�b�v�̕`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < HC_NUM; i++)
	{
		DrawBox(hit_chip[i].x, hit_chip[i].y, hit_chip[i].x + 32, hit_chip[i].y + 32, hit_chip[i].color, TRUE);
		DrawGraph(hit_chip[i].x, hit_chip[i].y,HitImageHandle[i], TRUE);
		DrawString(hit_chip[i].x + 48, hit_chip[i].y+6,hit_chip[i].name,GetColor(255, 255, 255));
		if (SelectHitBlock == i)
		{
			DrawBox(hit_chip[i].x, hit_chip[i].y, hit_chip[i].x + 32, hit_chip[i].y + 32, GetColor(255, 255, 255), FALSE);
			DrawBox(hit_chip[i].x-1, hit_chip[i].y-1, hit_chip[i].x + 32+1, hit_chip[i].y + 32+1, GetColor(255, 255, 255), FALSE);
		}
	}
}

//�R���t�B�O���[�h�̏���()
static void ConfigMode_Update()
{
	//�}�E�X���N���b�N�����u��
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//�ݒ�I���{�^��
		if (min_button[3].x - 32 <= MouseX && MouseX <= min_button[3].x && min_button[3].y - 16 <= MouseY && MouseY <= min_button[3].y + 16)
		{
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle02, DX_PLAYTYPE_BACK);
			time1 = GetNowCount();
			min_button[4].flag = 1;
			Stop_Update = 1;
		}

		//�ݒ�ۑ��{�^��
		if (min_button[3].x - 32 <= MouseX && MouseX <= min_button[3].x && min_button[3].y - 16 -64 <= MouseY && MouseY <= min_button[3].y + 16 - 64)
		{
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle02, DX_PLAYTYPE_BACK);
			time1 = GetNowCount();
			min_button[5].flag = 1;
			Stop_Update = 1;
		}

		//�ȕύX�{�^��
		if (263 < MouseX && MouseX < 305 && 830 < MouseY && MouseY < 860 && config_menu[3].flag == ON)
		{
			if (config_menu[4].flag == ON) PlaySoundMem(SeHandle04, DX_PLAYTYPE_BACK);
			ChangeBGM((SelectBGM + 4) % 5);
		}

		if (395 < MouseX && MouseX < 436 && 830 < MouseY && MouseY < 860 && config_menu[3].flag == ON)
		{
			if (config_menu[4].flag == ON) PlaySoundMem(SeHandle04, DX_PLAYTYPE_BACK);
			ChangeBGM((SelectBGM + 1) % 5);
		}

		//�e��ݒ�{�^��
		for (int i = 0; i < CF_NUM; i++)
		{
			if (config_menu[i].x - 50 < MouseX && MouseX < config_menu[i].x - 30 && config_menu[i].y - 3 < MouseY && MouseY < config_menu[i].y + 20 - 3)
			{
				if (config_menu[i].flag == ON)
				{
					config_menu[i].flag = OFF;
				}
				else
				{
					config_menu[i].flag = ON;
					if (i == 3)ChangeBGM(SelectBGM);
				}
				if (config_menu[4].flag == ON)PlaySoundMem(SeHandle07, DX_PLAYTYPE_BACK);
			}
		}

		//BGM���ʕύX�{�^��
		if (29 < MouseX && MouseX < 49 && 820 < MouseY && MouseY < 840 && config_menu[3].flag == 0)
		{
			if(config_menu[3].flag == ON && BgmVolume < 230)PlaySoundMem(SeHandle03, DX_PLAYTYPE_BACK);
			BgmVolume += 30;
			if (BgmVolume >=230)BgmVolume = 230;
		}
		if (29 < MouseX && MouseX < 49 && 850 < MouseY && MouseY < 870 && config_menu[3].flag == 0)
		{
			if (config_menu[3].flag == ON && 80 < BgmVolume)PlaySoundMem(SeHandle03, DX_PLAYTYPE_BACK);
			BgmVolume -= 30;
			if (80 > BgmVolume)BgmVolume = 80;

		}
		AdjustmentBGMVolume(BgmVolume);

		//SE���ʕύX�{�^��
		if (129 < MouseX && MouseX < 149 && 820 < MouseY && MouseY < 840 && config_menu[4].flag == 0)
		{
			if (config_menu[4].flag == ON && SeVolume < 230)PlaySoundMem(SeHandle03, DX_PLAYTYPE_BACK);
			SeVolume += 30;
			if (SeVolume >= 230)SeVolume = 230;
		}
		if (129 < MouseX && MouseX < 149 && 850 < MouseY && MouseY < 870 && config_menu[4].flag == 0)
		{
			if (config_menu[4].flag == ON && 80 < SeVolume)PlaySoundMem(SeHandle03, DX_PLAYTYPE_BACK);
			SeVolume -= 30;
			if (80 > SeVolume)SeVolume = 80;
		}
		AdjustmentSEVolume(SeVolume);
	}

	//BGM�̍Đ����~�߂�
	if (config_menu[3].flag == OFF)
	{
		switch (SelectBGM)
		{
		case 0:
			StopSoundMem(BgmHandle00);
			break;
		case 1:
			StopSoundMem(BgmHandle01);
			break;
		case 2:
			StopSoundMem(BgmHandle02);
			break;
		case 3:
			StopSoundMem(BgmHandle03);
			break;
		case 4:
			StopSoundMem(BgmHandle04);
			break;
		}
	}
}

//�R���t�B�O���[�h�̕`��
static void ConfigMode_Draw()
{
	//���b�Z�[�W
	DrawString(20, 20, "�ݒ���", GetColor(255, 255, 255));

	//�I���{�^���̕\��
	if (min_button[4].flag == 0)
	{
		DrawCircleAA((float)min_button[4].x, (float)min_button[4].y, 16, 120, min_button[4].color, TRUE);
		DrawString(min_button[4].x + 32, min_button[4].y - 8,min_button[4].name, min_button[4].color);
	}
	else
	{
		DrawCircleAA((float)min_button[4].x, (float)min_button[4].y, 16, 120,GetColor(116,169,214), TRUE);
		DrawString(min_button[4].x + 32, min_button[4].y - 8, min_button[4].name,GetColor(116,169,214));
	}

	//�ݒ�ۑ��{�^���̕\��
	if (min_button[5].flag == 0)
	{
		DrawCircleAA((float)min_button[5].x, (float)min_button[5].y, 16, 120, min_button[5].color, TRUE);
		DrawString(min_button[5].x + 32, min_button[5].y - 8, min_button[5].name, min_button[5].color);
	}
	else
	{
		DrawCircleAA((float)min_button[5].x, (float)min_button[5].y, 16, 120, GetColor(116, 169, 214), TRUE);
		DrawString(min_button[5].x + 32, min_button[5].y - 8, min_button[5].name, GetColor(116, 169, 214));
	}


	//�R���t�B�O���j���[�̕\��
	for (int i = 0; i < CF_NUM; i++)
	{
		DrawBox(config_menu[i].x-50, config_menu[i].y-3, config_menu[i].x-30, config_menu[i].y + 20-3, config_menu[i].color, FALSE);
		DrawString(config_menu[i].x, config_menu[i].y, config_menu[i].name, config_menu[i].color);
		if (config_menu[i].flag == ON)DrawGraph(config_menu[i].x - 53, config_menu[i].y - 15, Check_Image, TRUE);
	}

	//�}�E�X���W�̕\��
	if(config_menu[2].flag == ON) MousePoint_Draw(100, 20);

	//BGM�ύX�{�^���̕\��
	DrawCircleAA(350.0, 845.0, 25.0, 124, GetColor(255, 255, 255), TRUE);
	DrawString(286, 900, "�I�����Ă���BGM", GetColor(255, 255, 255));
	DrawString(45, 900, "BGM����", GetColor(255, 255, 255));
	DrawString(45+100, 900, "SE����", GetColor(255, 255, 255));
	DrawFormatString(347, 838, back_color, "%d", SelectBGM+1);
	if (config_menu[3].flag == ON)
	{
		DrawTriangleAA(263.75, 845.0, 305, 860.0, 305, 830.0, GetColor(255, 255, 255), TRUE);
		DrawTriangleAA(436.25, 845.0, 395, 860.0, 395, 830.0, GetColor(255, 255, 255), TRUE);
	}

	//BGM���ʕύX�{�^��
	for (int i = 0; i < 5; i++)
	{
		if (BgmVolume < 100+(4-i)*30)
		{
			DrawBox(62, 785 + i * 20, 82, 795 + i * 20, GetColor(255, 255, 255), FALSE);
		}
		else
		{
			DrawBox(62, 785 + i * 20, 82, 795 + i * 20, GetColor(255, 255, 255), TRUE);
		}
	}

	//SE���ʕύX�{�^��
	for (int i = 0; i < 5; i++)
	{
		if (SeVolume < 100 + (4 - i) * 30)
		{
			DrawBox(162, 785 + i * 20, 182, 795 + i * 20, GetColor(255, 255, 255), FALSE);
		}
		else
		{
			DrawBox(162, 785 + i * 20, 182, 795 + i * 20, GetColor(255, 255, 255), TRUE);
		}
	}

	//BGM��OFF�̎��Ɂ~�}�[�N��`�ʁA����ȊO�͉��ʂ̏㉺�L�[��`��
	if (config_menu[3].flag == OFF)
	{
		DrawLineAA(42.0, 787.0, 101.0, 878.0, GetColor(255, 0, 0), 10);
		DrawLineAA(101.0, 787.0, 42.0, 878.0, GetColor(255, 0, 0), 10);
	}
	else
	{
		DrawString(29, 820, "��", GetColor(255, 255, 255));
		DrawString(29, 850, "��", GetColor(255, 255, 255));
	}

	//SE��OFF�̎��Ɂ~�}�[�N��`�ʁA����ȊO�͉��ʂ̏㉺�L�[��`��
	if (config_menu[4].flag == OFF)
	{
		DrawLineAA(142.0, 787.0, 201.0, 878.0, GetColor(255, 0, 0), 10);
		DrawLineAA(201.0, 787.0, 142.0, 878.0, GetColor(255, 0, 0), 10);
	}
	else
	{
		DrawString(129, 820, "��", GetColor(255, 255, 255));
		DrawString(129, 850, "��", GetColor(255, 255, 255));
	}
}

//�G�f�B�^�[�I������
static void End_Editor()
{
	//�I���j�~�L�[
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		min_button[3].flag = 0;
		Stop_Update = 0;
		if(config_menu[4].flag == ON)PlaySoundMem(SeHandle06, DX_PLAYTYPE_BACK);
	}

	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (config_menu[8].flag == OFF)
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�I���{�^�������͂���܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Esc�L�[�ŏI���𒆎~���邱�Ƃ��ł��܂��B", GetColor(255, 255, 0));
		}

		if (t_time >= 2)
		{
			DrawString(10, 70, "�G�f�B�^�[���I�����Ă��܂�...", GetColor(255, 255, 255));
		}

		if (t_time >= 4)
		{
			DrawFormatString(10, 100, GetColor(255, 255, 255), "%d�b��Ƀ��j���[��ʂɖ߂�܂��B", 8 - t_time);
		}

		if (t_time >= 8)
		{
			if (config_menu[11].flag == ON)Output_MapData();
			MapEditor_Finalize();
			DxLib_End();
		}
	}
	else
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�I���{�^�������͂���܂����B", GetColor(255, 255, 255));
		}
		if (t_time >= 1)
		{
			DrawString(10, 40, "�G�f�B�^���I�����܂��B", GetColor(255, 255, 255));
		}
		if (t_time >= 3)
		{
			if(config_menu[11].flag == ON)Output_MapData();
			MapEditor_Finalize();
			DxLib_End();
		}
	}
}

//�ۑ��̏���
static void Save_Update()
{
	//�ۑ��j�~�L�[
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		min_button[0].flag = 0;
		Stop_Update = 0;
		if (config_menu[4].flag == ON)PlaySoundMem(SeHandle06, DX_PLAYTYPE_BACK);
	}

	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (config_menu[6].flag == OFF)
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�ۑ��{�^�������͂���܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Esc�L�[�ŕۑ��𒆎~���邱�Ƃ��ł��܂��B", GetColor(255, 255, 0));
		}

		if (t_time >= 2)
		{
			DrawString(10, 70, "�}�b�v�f�[�^��ۑ����Ă��܂�...", GetColor(255, 255, 255));
			Output_MapData();
		}

		if (t_time >= 4 && 8 > t_time)
		{
			DrawFormatString(10, 100, GetColor(255, 255, 255), "����%d�b���҂���������", 8 - t_time);
		}

		if (t_time >= 8)
		{
			DrawString(10, 130, "�ۑ����������܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 10)
		{
			if (config_menu[4].flag == ON) PlaySoundMem(SeHandle05, DX_PLAYTYPE_BACK);
			min_button[0].flag = 0;
			Stop_Update = 0;
		}
	}
	else
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�ۑ��{�^�������͂���܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			Output_MapData();
			DrawString(10, 40, "�ۑ����������܂����B", GetColor(255, 255, 255));
		}
		if (t_time >= 2)
		{
			if (config_menu[4].flag == ON) PlaySoundMem(SeHandle05, DX_PLAYTYPE_BACK);
			min_button[0].flag = 0;
			Stop_Update = 0;
		}
	}
}

//�}�b�v�f�[�^�̍폜����
static void Eliminate_Update()
{
	//�폜�j�~�L�[
	if (KeyState(KEY_INPUT_ESCAPE) == 1)
	{
		min_button[1].flag = 0;
		Stop_Update = 0;
		if (config_menu[4].flag == ON)PlaySoundMem(SeHandle06, DX_PLAYTYPE_BACK);
	}

	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (config_menu[7].flag == OFF)
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�폜�{�^�������͂���܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Esc�L�[�ō폜�𒆎~���邱�Ƃ��ł��܂��B", GetColor(255,255,0));
		}

		if (t_time >= 4 && 8 > t_time)
		{
			DrawFormatString(10, 70, GetColor(255, 255, 255), "����%d�b���҂���������", 8 - t_time);
		}

		if (t_time >= 8)
		{
			DrawString(10, 70, "�}�b�v�f�[�^���폜���Ă��܂�...", GetColor(255, 255, 255));
		}

		if (t_time >= 9)
		{
			DrawString(10, 100, "�폜���������܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 10)
		{
			Eliminate_MapData();
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle01, DX_PLAYTYPE_BACK);
			min_button[1].flag = 0;
			Stop_Update = 0;
		}
	}

	else
	{
		if (t_time >= 0)
		{
			DrawString(10, 10, "�폜�{�^�������͂���܂����B", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "�폜���������܂����B", GetColor(255, 255, 255));
		}
		if (t_time >= 2)
		{
			Eliminate_MapData();
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle01, DX_PLAYTYPE_BACK);
			min_button[1].flag = 0;
			Stop_Update = 0;
		}
	}
}

//�R���t�B�O�ݒ���Ăяo��
static void Config_State()
{
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (t_time >= 1)
	{
		if (config_menu[4].flag == ON) PlaySoundMem(SeHandle11, DX_PLAYTYPE_BACK);
		min_button[2].flag = 0;
		Stop_Update = 0;
		SelectMode = Config_Edit;
	}
}

//�R���t�B�O�ݒ���I���
static void Config_End()
{
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (t_time >= 1)
	{
		if (config_menu[4].flag == ON) PlaySoundMem(SeHandle12, DX_PLAYTYPE_BACK);
		Stop_Update = 0;
		SelectMode = Object_Edit;
		min_button[4].flag = 0;
	}
}

//�R���t�B�O�ݒ��ۑ�����
static void Config_Save()
{
	Output_Config();
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (t_time >= 1)
	{
		DrawString(32,68,"�ۑ����������܂����B",GetColor(255,255,255));
	}
	if (t_time >= 2)
	{
		min_button[5].flag = 0;
		Stop_Update = 0;
	}
}

//�t�@�C����ǂݍ��񂾍ۂ̃��b�Z�[�W
static void LoadMessage()
{
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (config_menu[5].flag == ON && MessageFlag[0] == 1 && t_time >= 0 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 10, "�}�b�v�f�[�^�̓ǂݍ��݂��������܂����B", GetColor(255, 255, 255));
	}

	if (config_menu[5].flag == ON && MessageFlag[1] == 1 && t_time >= 1 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 40, "�R���t�B�O�f�[�^�̓ǂݍ��݂��������܂����B", GetColor(255, 255, 255));
	}

	if (config_menu[5].flag == ON && t_time >= 2 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 70, "�f�[�^�͐���ɓǂݍ��܂�܂����B", GetColor(255, 255, 255));
	}

	if (t_time >= 8)
	{
		MessageFlag[0] = 0;
	}
}

//����Ă���BGM��ύX���鏈��
static void ChangeBGM(int number)
{
	if (config_menu[3].flag == ON)
	{
		switch (SelectBGM)
		{
		case 0:
			StopSoundMem(BgmHandle00);
			break;
		case 1:
			StopSoundMem(BgmHandle01);
			break;
		case 2:
			StopSoundMem(BgmHandle02);
			break;
		case 3:
			StopSoundMem(BgmHandle03);
			break;
		case 4:
			StopSoundMem(BgmHandle04);
			break;
		}
	}
	SelectBGM = number;
	if (config_menu[3].flag == ON)
	{
		switch (SelectBGM)
		{
		case 0:
			PlaySoundMem(BgmHandle00, DX_PLAYTYPE_LOOP, TRUE);
			break;
		case 1:
			PlaySoundMem(BgmHandle01, DX_PLAYTYPE_LOOP, TRUE);
			break;
		case 2:
			PlaySoundMem(BgmHandle02, DX_PLAYTYPE_LOOP, TRUE);
			break;
		case 3:
			PlaySoundMem(BgmHandle03, DX_PLAYTYPE_LOOP, TRUE);
			break;
		case 4:
			PlaySoundMem(BgmHandle04, DX_PLAYTYPE_LOOP, TRUE);
			break;
		}
	}
}

//���ׂĂ�BGM�n���h���̉��ʂ𒲐߂���
static void AdjustmentBGMVolume(int volume)
{
	ChangeVolumeSoundMem(volume, BgmHandle00);
	ChangeVolumeSoundMem(volume, BgmHandle01);
	ChangeVolumeSoundMem(volume, BgmHandle02);
	ChangeVolumeSoundMem(volume, BgmHandle03);
	ChangeVolumeSoundMem(volume, BgmHandle04);
}

//���ׂĂ�SE�n���h���̉��ʂ𒲐߂���
static void AdjustmentSEVolume(int volume)
{
	ChangeVolumeSoundMem(50 + volume, SeHandle01);
	ChangeVolumeSoundMem(0 + volume, SeHandle02);
	ChangeVolumeSoundMem(0 + volume, SeHandle03);
	ChangeVolumeSoundMem(-40 + volume, SeHandle04);
	ChangeVolumeSoundMem(0 + volume, SeHandle05);
	ChangeVolumeSoundMem(20 + volume, SeHandle06);
	ChangeVolumeSoundMem(60 + volume, SeHandle07);
	ChangeVolumeSoundMem(10 + volume, SeHandle08);
	ChangeVolumeSoundMem(-40 + volume, SeHandle09);
	ChangeVolumeSoundMem(30 + volume, SeHandle10);
	ChangeVolumeSoundMem(-20 + volume, SeHandle11);
	ChangeVolumeSoundMem(-20 + volume, SeHandle12);
}

//���y�֌W�̏�����
static void Music_Initialize()
{
	BgmHandle00 = LoadSoundMem("Data/Music/bgm00.ogg");
	BgmHandle01 = LoadSoundMem("Data/Music/bgm01.ogg");
	BgmHandle02 = LoadSoundMem("Data/Music/bgm02.ogg");
	BgmHandle03 = LoadSoundMem("Data/Music/bgm03.ogg");
	BgmHandle04 = LoadSoundMem("Data/Music/bgm04.ogg");
	SeHandle01 = LoadSoundMem("Data/Music/se01.ogg");
	SeHandle02 = LoadSoundMem("Data/Music/se02.ogg");
	SeHandle03 = LoadSoundMem("Data/Music/se03.ogg");
	SeHandle04 = LoadSoundMem("Data/Music/se04.ogg");
	SeHandle05 = LoadSoundMem("Data/Music/se05.ogg");
	SeHandle06 = LoadSoundMem("Data/Music/se06.ogg");
	SeHandle07 = LoadSoundMem("Data/Music/se07.ogg");
	SeHandle08 = LoadSoundMem("Data/Music/se08.ogg");
	SeHandle09 = LoadSoundMem("Data/Music/se09.ogg");
	SeHandle10 = LoadSoundMem("Data/Music/se10.ogg");
	SeHandle11 = LoadSoundMem("Data/Music/se11.ogg");
	SeHandle12 = LoadSoundMem("Data/Music/se12.ogg");
}

//�t�@�C���̏������֘A�̃��W���[��
static void LoadFile_InitializeModule()
{
	if (fopen("MapData.csv", "r") != NULL)
	{
		Load_MapData();
		time1 = GetNowCount();
		MessageFlag[0] = 1;
	}

	if (Load_Config() == 0) MessageFlag[1] = 1;
}

//�ϐ���������
static void Reset_Initialize()
{
	SelectBGM = 0;
	MessageFlag[0] = 0;
	MessageFlag[1] = 0;
	BgmVolume = 140;
	SeVolume = 140;
	b_block = 0;
	back_color = GetColor(51, 51, 51);
	MapData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE] = { 0 };
	HitData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE] = { 0 };
	BackData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE] = { 0 };
	SelectMode = Loading;
	SelectBlock = 0;
	SelectBGM = 0;
	SelectHitBlock = 0;
	Stop_Update = 0;
	MoveY = 0;
	MouseCount = 0;
	map_x = MAP_WIDTH / MAP_SIZE;
	map_y = MAP_HEIGHT / MAP_SIZE;
}

//���[�f�B���O��ʂ̑f�ނ�ǂݍ���
static void LoadMaterial()
{
	t_time = 0;
	MouseCount = 0;
	LoadEnd = 0;
	LoadDivGraph("Data/Picture/LoadingImg.png", 60, 10, 6, 128, 128, LoadImageHandle, TRUE);
}

//���[�h��ʂ̕\��
static void LoadScreen()
{
	time2 = GetNowCount();

	if (LoadEnd == 1)
	{
		t_time = (time2 - time1) / 1000;
	}

	DrawBox(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT, GetColor(255, 255, 255), TRUE);
	DrawGraph(EDITOR_WIDTH - 188, EDITOR_HEIGHT - 180, LoadImageHandle[MouseCount % 60], TRUE);
	DrawString(EDITOR_WIDTH - 188 - 50, EDITOR_HEIGHT - 190 + 148, "�f�[�^��ǂݍ���ł��܂�", GetColor(222, 184, 135));
	MouseCount++;

	if (LoadEnd == 1 && t_time > LOADING_MARGIN - (1 - config_menu[10].flag)*2)
	{
		SelectMode = Object_Edit;
		MouseCount = 0;
		LoadEnd = 0;
		for (int i = 0; i < 60; i++)
		{
			DeleteGraph(LoadImageHandle[i]);
		}

		AdjustmentSEVolume(SeVolume);
		AdjustmentBGMVolume(BgmVolume);

		if (config_menu[3].flag == ON)
		{
			switch (SelectBGM)
			{
			case 0:
				AdjustmentBGMVolume(BgmVolume);
				PlaySoundMem(BgmHandle00, DX_PLAYTYPE_LOOP, TRUE);
				break;
			case 1:
				AdjustmentBGMVolume(BgmVolume);
				PlaySoundMem(BgmHandle01, DX_PLAYTYPE_LOOP, TRUE);
				break;
			case 2:
				AdjustmentBGMVolume(BgmVolume);
				PlaySoundMem(BgmHandle02, DX_PLAYTYPE_LOOP, TRUE);
				break;
			case 3:
				AdjustmentBGMVolume(BgmVolume);
				PlaySoundMem(BgmHandle03, DX_PLAYTYPE_LOOP, TRUE);
				break;
			case 4:
				AdjustmentBGMVolume(BgmVolume);
				PlaySoundMem(BgmHandle04, DX_PLAYTYPE_LOOP, TRUE);
				break;
			}
		}
	}
}