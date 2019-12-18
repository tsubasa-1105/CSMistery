#pragma once

//ゲーム画面のサイズ
#define GAME_WIDTH 640
#define GAME_HIEGHT 480
#define GAME_DEPTH 16

void Game_Initialize();	//初期化
void Game_Finalize();	//終了
void Game_Update();		//更新
void Game_Draw();		//描画