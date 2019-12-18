#pragma once

void InputRel_Initialize();			//初期化
int UpdateKey();					//更新
int KeyState(int code);				//キーボードの入力情報を返す
int MouseState(int code);			//マウスの入力状態を返す
void MousePoint(int *x, int *y);	//マウスの座標をポインタに渡す

