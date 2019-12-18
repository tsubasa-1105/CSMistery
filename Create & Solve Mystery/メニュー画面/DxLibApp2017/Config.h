#pragma once

//コンフィグ画面のサイズ
#define CONFIG_WIDTH 640
#define CONFIG_HIEGHT 480
#define CONFIG_DEPTH 16

void Config_Initialize();	//初期化
void Config_Finalize();		//終了
void Config_Update();		//更新
void Config_Draw();			//描画