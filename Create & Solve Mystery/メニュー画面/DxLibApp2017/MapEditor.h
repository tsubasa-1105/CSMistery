#pragma once

//マップディター画面のサイズ
#define EDITOR_WIDTH 640
#define EDITOR_HIEGHT 480
#define EDITOR_DEPTH 16

void MapEditor_Initialize();	//初期化
void MapEditor_Finalize();		//終了
void MapEditor_Update();		//更新
void MapEditor_Draw();			//描画