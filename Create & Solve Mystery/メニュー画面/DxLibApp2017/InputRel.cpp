#include "InputRel.h"
#include "DxLib.h"

static int key[256];
static int mouse[2];
static int mouseX, mouseY;

//初期化
void InputRel_Initialize()
{
	key[256] = { 0 };
	mouse[2] = { 0 };
}

//入力状態の更新
int UpdateKey()
{
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);

	//キーボード更新
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

	//マウス更新
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

	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);

	return 0;
}

//キーボードの入力状態を返す
int KeyState(int code)
{
	return key[code];
}

//マウスの入力状態を返す
int MouseState(int code)
{
	if (code == MOUSE_INPUT_RIGHT) return mouse[0];
	if (code == MOUSE_INPUT_LEFT) return mouse[1];
	
	return -1;
}

//マウスの座標をポインタに渡す
void MousePoint(int *x, int *y)
{
	*x = mouseX;
	*y = mouseY;
}