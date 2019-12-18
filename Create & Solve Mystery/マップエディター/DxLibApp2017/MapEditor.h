#pragma once
#pragma warning (disable : 4996)
#pragma warning (disable : 4838)

//マップディター画面のサイズ
#define EDITOR_WIDTH 1600
#define EDITOR_HEIGHT 960
#define EDITOR_DEPTH 16

//マップのサイズ
#define MAP_WIDTH 1280
#define MAP_HEIGHT 960
#define MAP_SIZE 32

//ロード時間の余白
#define LOADING_MARGIN 2

//ボタンの要素
struct ButtonElement
{
	int x,y;
	char name[256];
	int flag;
	int color;
};

//当たり判定チップ
struct HitElement
{
	int x, y;
	char name[256];
	int color;
};

//モードの定義
typedef enum
{
	Back_Edit,
	Object_Edit,
	Hit_Edit,
	Non_Edit,
	Config_Edit,
	Loading,
}Edito_Mode;

//ボタン状態の定義
typedef enum
{
	ON,
	OFF,
}State_Button;

void MapEditor_Initialize();	//初期化
void MapEditor_Finalize();		//終了
void MapEditor_Update();		//更新
void MapEditor_Draw();			//描画