#include "InputRel.h"
#include "DxLib.h"

static int key[256];
static int mouse[2];
static int mouseX, mouseY;

//������
void InputRel_Initialize()
{
	key[256] = { 0 };
	mouse[2] = { 0 };
}

//���͏�Ԃ̍X�V
int UpdateKey()
{
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);

	//�L�[�{�[�h�X�V
	for (int i = 0; i < 256; i++)
	{
		if (tmpkey[i] != 0)
		{
			key[i]++;
		}
		else
		{
			key[i] = 0;
		}
	}

	//�}�E�X�X�V
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		mouse[0]++;
	}
	else
	{
		mouse[0] = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		mouse[1]++;
	}
	else
	{
		mouse[1] = 0;
	}

	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);

	return 0;
}

//�L�[�{�[�h�̓��͏�Ԃ�Ԃ�
int KeyState(int code)
{
	return key[code];
}

//�}�E�X�̓��͏�Ԃ�Ԃ�
int MouseState(int code)
{
	if (code == MOUSE_INPUT_RIGHT) return mouse[0];
	if (code == MOUSE_INPUT_LEFT) return mouse[1];
	
	return -1;
}

//�}�E�X�̍��W���|�C���^�ɓn��
void MousePoint(int *x, int *y)
{
	*x = mouseX;
	*y = mouseY;
}