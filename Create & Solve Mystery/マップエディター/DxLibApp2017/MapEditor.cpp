#include <stdio.h>
#include <ctype.h>
#include "MapEditor.h"
#include "InputRel.h"
#include "DxLib.h"

static ButtonElement big_button[3] =
{
	{1536, 50,"背景",0,GetColor(255,98,50)},
	{1536, 150,"物体",0,GetColor(251,236,53)},
	{1536, 250,"判定",0,GetColor(50,204,18)},
};

static ButtonElement min_button[6] =
{
	{ 1472, 704,"保存",0,GetColor(255,255,255) },
	{ 1472, 768,"削除",0,GetColor(255,255,255) },
	{ 1472, 832,"設定",0,GetColor(255,255,255) },
	{ 1472, 896,"終了",0,GetColor(255,255,255) },
	{ 1456, 896,"設定終了",0,GetColor(255,255,255) },
	{ 1456, 832,"設定保存",0,GetColor(255,255,255) },
};

#define HC_NUM 2

static HitElement hit_chip[HC_NUM] =
{
	{ 1312, 32,"通れる場所",GetColor(251,231,49) },
	{ 1312, 96,"通れない場所",GetColor(178,0,8) },
	//{ 1312, 160,"ダミー",GetColor(39,38,114) },
};

#define CF_NUM 13
static ButtonElement config_menu[CF_NUM] =
{
	{ 120,120,"マップエディターのマス目を表示する",OFF,GetColor(255,255,255)},
	{ 120,180,"マップチップ部分のマス目を表示する",ON,GetColor(255,255,255)},
	{ 120,240,"マウスの座標を表示する",OFF ,GetColor(255,255,255)},
	{ 120,300,"BGMを流す",ON ,GetColor(255,255,255)},
	{ 120,360,"SEを流す",ON ,GetColor(255,255,255) },
	{ 120,420,"読み込みメッセージを表示する",OFF,GetColor(255,255,255) },
	{ 120,480,"ファイルの保存を高速化する",ON ,GetColor(255,255,255) },
	{ 120,540,"ファイルの削除を高速化する",OFF,GetColor(255,255,255) },
	{ 120,600,"エディター終了を高速化する",ON,GetColor(255,255,255) },
	{ 120,660,"塗るときに効果音をつける",ON,GetColor(255,255,255) },
	{ 560,120,"起動時間の短縮",OFF,GetColor(255,255,255) },
	{ 560,180,"終了時にマップデータを自動で保存する",ON,GetColor(255,255,255) },
	{ 560,240,"背景モードにオブジェクトを表示する",ON,GetColor(255,255,255) },
};

static int BackData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE];//背景データ
static int MapData[MAP_HEIGHT /MAP_SIZE][MAP_WIDTH/MAP_SIZE];	//オブジェクトデータ
static int HitData[MAP_HEIGHT / MAP_SIZE][MAP_WIDTH / MAP_SIZE];//当たり判定データ
static int back_color;			//背景色指定
static int time1, time2, t_time;//時間管理
static int time_d;				//double型時間管理変数
static int Check_Image;			//チェックマークの画像ハンドル
static int Stop_Update;			//アップデートを行うかを管理する変数
static int b_block;				//背景ブロック
static int SelectMode;			//エディターモード管理変数
static int SelectBlock;			//選択しているマップチップ
static int SelectHitBlock;		//選択している当たり判定ブロック
static int mcImage[300];		//マップチップイメージ
static int bImage[18];			//背景画像のイメージ
static int map_x, map_y;		//マップの縦横マス数
static int MoveY;				//マップチップの移動量
static int MouseX, MouseY;		//マウスの座標
static int tMouseX, tMouseY;	//マウスの座標ダミー
static int MouseCount;			//マウスが前フレームと同じ座標にあるかを調べる
static int SelectBGM;			//選択されているBGM
static int LoadImageHandle[60];	//ロード画面用の画像ハンドル
static int HitImageHandle[3];	//当たり判定用の画像ハンドル
static int LoadEnd;				//ロードの終了フラグ
static int BgmHandle00;			//BGM用ハンドル
static int BgmHandle01;			//BGM用ハンドル
static int BgmHandle02;			//BGM用ハンドル
static int BgmHandle03;			//BGM用ハンドル
static int BgmHandle04;			//BGM用ハンドル
static int SeHandle01;			//SE用ハンドル
static int SeHandle02;			//SE用ハンドル
static int SeHandle03;			//SE用ハンドル
static int SeHandle04;			//SE用ハンドル
static int SeHandle05;			//SE用ハンドル
static int SeHandle06;			//SE用ハンドル
static int SeHandle07;			//SE用ハンドル
static int SeHandle08;			//SE用ハンドル
static int SeHandle09;			//SE用ハンドル
static int SeHandle10;			//SE用ハンドル
static int SeHandle11;			//SE用ハンドル
static int SeHandle12;			//SE用ハンドル
static int BgmVolume;			//現在のBGM音量を管理する
static int SeVolume;			//現在のSE音量を管理する
static int MessageFlag[2];		//メッセージフラグ

static void Load_MapData();					//マップデータを読み込む
static void Output_MapData();				//マップデータを出力する
static int  Load_Config();					//コンフィグファイルを読み込む
static void Output_Config();				//コンフィグファイルを出力する
static void Eliminate_MapData();			//データ配列をリセットする
static void MousePoint_Draw(int x,int y);	//指定の座標にマウス座標を表示する
static void Button_Update();				//ボタン関連の処理
static void Button_Draw();					//ボタン関連の描画
static void BackMode_Update();				//背景モードの処理
static void BackMode_Draw();				//背景モードの描画
static void ObjectMode_Update();			//オブジェクトモードの処理
static void ObjectMode_Draw();				//オブジェクトモードの描画
static void HitMode_Update();				//当たり判定モードの処理
static void HitMode_Draw();					//当たり判定モードの描画
static void ConfigMode_Update();			//コンフィグモード処理
static void ConfigMode_Draw();				//コンフィグモード描画
static void End_Editor();					//エディター終了処理
static void Save_Update();					//保存の処理
static void Eliminate_Update();				//マップデータの削除処理
static void Config_State();					//コンフィグ画面を呼び出す
static void Config_End();					//コンフィグ画面を終了する
static void Config_Save();					//コンフィグ画面を保存する
static void LoadMessage();					//ファイルを読み込んだ際のメッセージ
static void ChangeBGM(int number);			//流れているBGMを変更する
static void AdjustmentBGMVolume(int volume);//すべてのBGMハンドルの音量を調節する
static void AdjustmentSEVolume(int volume);	//すべてのSEハンドルの音量を調節する
static void Music_Initialize();				//音楽関係の初期化を行う											
static void LoadFile_InitializeModule();	//ロードファイル関係のモジュール
static void Reset_Initialize();				//変数を初期化
static void LoadMaterial();					//ロード画面の素材を先に読み込む
static void LoadScreen();					//ロード画面を表示する

//初期化
void MapEditor_Initialize()
{
	SetUseASyncLoadFlag(TRUE);	//非同期読み込み

	SetGraphMode(EDITOR_WIDTH, EDITOR_HEIGHT, EDITOR_DEPTH);	//画面サイズ変更
	Reset_Initialize(); //変数の初期化
	LoadMaterial();		//ロード画面の素材を読み込む

	Music_Initialize();	//音楽関係のロード
	LoadFile_InitializeModule(); //ファイル読み込み

	if (BgmVolume < 80 || 230 < BgmVolume)SelectBGM = 140;	//ボリュームの調整
	if (SeVolume < 80 || 230 < SeVolume)SelectBGM = 140;	//ボリュームの調整
	if (SelectBGM < 0 || 4 < SelectBGM)SelectBGM = 0;		//選択BGMの調整

	Check_Image = LoadGraph("Data/Picture/Check.png");
	LoadDivGraph("Data/Picture/background.png", 18, 6, 3, 32, 32, bImage);
	LoadDivGraph("Data/Picture/MapChip.png",300,20,15,32,32,mcImage);
	LoadDivGraph("Data/Picture/hit_block.png", 3, 3, 1, 32, 32, HitImageHandle);
	SetUseASyncLoadFlag(FALSE);	//同期読み込み
	LoadEnd = 1;
	time1 = GetNowCount();
}

//終了
void MapEditor_Finalize()
{
	SetUseASyncLoadFlag(FALSE);
	DeleteGraph(Check_Image);
	InitSoundMem();
}

//処理
void MapEditor_Update()
{
	//マウスの座標を取得する
	MousePoint(&MouseX, &MouseY);

	//ロード画面の読み込み
	if (Stop_Update == 0)
	{
		//モードごとの処理
		if (SelectMode == Back_Edit) BackMode_Update();
		if (SelectMode == Object_Edit) ObjectMode_Update();
		if (SelectMode == Hit_Edit) HitMode_Update();
		if (SelectMode == Config_Edit) ConfigMode_Update();
		if (SelectMode == Loading) LoadScreen();

		//ボタン関連の処理
		if(SelectMode != Config_Edit && SelectMode != Loading) Button_Update();
	}
	//マウスの座標を取得する
	MousePoint(&tMouseX, &tMouseY);
}

//描画
void MapEditor_Draw()
{
	if (SelectMode != Loading)
	{
		//エディター背景色描写
		DrawBox(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT, back_color, TRUE);

		//モードごとに描画
		if (SelectMode == Back_Edit) BackMode_Draw();
		if (SelectMode == Object_Edit) ObjectMode_Draw();
		if (SelectMode == Hit_Edit) HitMode_Draw();
		if (SelectMode == Config_Edit) ConfigMode_Draw();

		if (SelectMode != Config_Edit)
		{
			//ボタン関連の描写
			Button_Draw();
			//マウス座標の表示
			if(Stop_Update == 0 && config_menu[2].flag == ON) MousePoint_Draw(1500, 10);
			//ボタン入力時の処理
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
	SetAlwaysRunFlag(true);//バックグラウンドで動作
	//SetOutApplicationLogValidFlag(FALSE);	//log.txtを作成しない
	SetMainWindowText("CSMistery");
	ChangeWindowMode(TRUE),DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	InputRel_Initialize();//初期化
	MapEditor_Initialize();//初期化

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && UpdateKey() == 0)
	{
		MapEditor_Update();//処理
		MapEditor_Draw();//描画
	}

	MapEditor_Finalize();//終了
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////

//マップデータを読み込む
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

//ファイルを出力する
static void Output_MapData()
{
	FILE *fp;
	fp = fopen("MapData.csv", "w");

	//背景データ出力
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

	//オブジェクトデータ出力
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

	//当たり判定データ出力
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

//コンフィグファイルを読み込む
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

//コンフィグを出力する
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

//データ配列をリセットする
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

//マウス座標を表示
static void MousePoint_Draw(int x,int y)
{
	DrawFormatString(x, y, GetColor(255, 255, 255), "(%d,%d)", MouseX, MouseY);
}

//ボタン関連の処理
static void Button_Update()
{
	//選択モード関連
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

	//マウスが右クリックされた瞬間
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//モード切替ボタンの処理
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

		//サブボタン入力時
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

//ボタン関連の描画
static void Button_Draw()
{
	//モード切替ボタンの描画
	for (int i = 0; i < 3; i++)
	{
		DrawBox(big_button[i].x, big_button[i].y, 1600, big_button[i].y + 60, big_button[i].color, TRUE);
		DrawString(big_button[i].x, big_button[i].y + 70, big_button[i].name, GetColor(255, 255, 255));
	}

	//サブボタンの描画
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

//背景モードの処理
static void BackMode_Update()
{
	//マウスが入力された瞬間
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//マップチップ選択
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

	//マウス右を押している間
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//マップを塗りつぶす
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if (config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			BackData[(MouseY / 32) % 30][(MouseX / 32) % 40] = b_block;
		}

	}
}

//背景モードの描画
static void BackMode_Draw()
{
	//背景マップ表示
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//背景描画
			DrawGraph(j * 32, i * 32, bImage[BackData[i][j]], FALSE);
			if (config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32 + 33, i * 32 + 33, GetColor(255, 255, 255), FALSE);
			//画像
			if (config_menu[12].flag == ON)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
				DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
			//枠線
			if (config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32 + 33, i * 32 + 33, GetColor(255, 255, 255), FALSE);
		}
	}

	//背景チップの表示
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

//オブジェクトモード処理
static void ObjectMode_Update()
{
	//マップチップ移動(キー入力)
	if (KeyState(KEY_INPUT_UP) != 0) MoveY += 30;
	if (KeyState(KEY_INPUT_DOWN) != 0) MoveY -= 30;

	//マップチップ移動(マウスホイール)
	if (1312 < MouseX && MouseX < 1408 && 32 < MouseY && MouseY < EDITOR_HEIGHT - 32)
	{
		MoveY += 20 * GetMouseWheelRotVol();
	}
	GetMouseWheelRotVol();

	//マップチップ移動制限
	if (MoveY >= 0) MoveY = 0;
	if (MoveY*(-1) >= 2304) MoveY = -2304;

	//マウスが右クリックされた瞬間
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//ブロック選択
		if (1312 < MouseX && MouseX < 1408 && 32 < MouseY && MouseY < EDITOR_HEIGHT - 32)
		{
			if (config_menu[4].flag == ON && SelectBlock != (((MouseY - MoveY - 32) / 32) * 3 + ((MouseX - 1312) / 32) % 3)) PlaySoundMem(SeHandle08, DX_PLAYTYPE_BACK);
			SelectBlock = ((MouseY - MoveY - 32) / 32) * 3 + ((MouseX - 1312) / 32) % 3;
		}
	}

	//マウス右を押している間
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//マップを塗りつぶす
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if(config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			MapData[(MouseY / 32) % 30][(MouseX / 32) % 40] = SelectBlock;
		}

	}

}

//オブジェクトモード描画
static void ObjectMode_Draw()
{
	//背景マップ表示
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			DrawGraph(j * 32, i * 32, bImage[BackData[i][j]], FALSE);
		}
	}

	//マップ表示
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//画像
			DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
			//枠線
			if(config_menu[0].flag == ON) DrawBox(j * 32, i * 32, j * 32+33, i * 32+33,GetColor(255,255,255), FALSE);
		}
	}

	//マップチップ背景
	//DrawBox(1312, 32, 1408, EDITOR_HEIGHT - 32, GetColor(231,232,226), TRUE);

	//マップチップ表示
	for (int i = 0; i < map_y / 2; i++)
	{
		for (int j = 0; j < map_x / 2; j++)
		{
			//画像
			DrawGraph(1312 + ((i * 20 + j) % 3) * 32, 32 + ((i * 20 + j) / 3) * 32 + MoveY, mcImage[i * 20 + j], TRUE);
			//枠線
			if (config_menu[1].flag == ON) DrawBox(1312 + ((i * 20 + j) % 3) * 32, 32 + ((i * 20 + j) / 3) * 32 + MoveY, 1312 + ((i * 20 + j) % 3) * 32 + 33, 32 + ((i * 20 + j) / 3) * 32 + MoveY + 33,GetColor(76,76,76), FALSE);
		}
	}

	//マップチップ外枠
	DrawBox(1312, 32, 1408, EDITOR_HEIGHT - 32, GetColor(76,76,76), FALSE);
	DrawBox(1312-1, 32-1, 1408+1, EDITOR_HEIGHT - 32+1, GetColor(76,76,76), FALSE);

	//選択マップチップに赤枠をつける
	DrawBox(1312 + (SelectBlock % 3) * 32, 32 + (SelectBlock / 3) * 32 + MoveY, 1312 + (SelectBlock % 3) * 32 + 33, 32 + (SelectBlock / 3) * 32 + 33 + MoveY, GetColor(255, 0, 0), FALSE);
	//マップチップの目隠しを上下に作成
	DrawBox(1312, 0, 1409, 32, back_color, TRUE);
	DrawBox(1312, EDITOR_HEIGHT - 31, 1409, EDITOR_HEIGHT, back_color, TRUE);
	//選択マップチップの表示
	DrawFormatString(1428+10, 42, GetColor(255, 255, 255), "%d", SelectBlock);
	//マップチップ位置バー背景表示
	DrawBox(1418, 32, 1427, EDITOR_HEIGHT - 32, GetColor(76,76,76),TRUE);
	//位置表示バー
	DrawCircleAA((float)1422, (float)(35 - MoveY/2.59), 3, 120, GetColor(255, 255, 255), TRUE);
}

//当たり判定モードの処理
static void HitMode_Update()
{
	//マウスを押した瞬間
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		for (int i = 0; i < HC_NUM; i++)
		{
			//ヒットチップ選択
			if (hit_chip[i].x < MouseX && MouseX < hit_chip[i].x + 32 && hit_chip[i].y < MouseY && MouseY < hit_chip[i].y + 32)
			{
				if (config_menu[4].flag == ON && SelectHitBlock != i) PlaySoundMem(SeHandle08, DX_PLAYTYPE_BACK);
				SelectHitBlock = i;
			}
		}
	}

	//マウス右を押している間
	if (MouseState(MOUSE_INPUT_LEFT) != 0)
	{
		//マップを塗りつぶす
		if (0 < MouseX && MouseX < 1280 && 0 < MouseY && MouseY < 960)
		{
			if (MouseX == tMouseX && MouseY == tMouseY) MouseCount++;
			else MouseCount = 0;
			if (config_menu[9].flag == ON && 10 > MouseCount && config_menu[4].flag == ON && (MouseState(MOUSE_INPUT_LEFT) % 10) == 1)PlaySoundMem(SeHandle09, DX_PLAYTYPE_BACK);
			HitData[(MouseY / 32) % 30][(MouseX / 32) % 40] = SelectHitBlock;
		}
	}
}

//当たり判定モードの描画
static void HitMode_Draw()
{
	//背景色描写
	DrawBox(0, 0, 1280, 960, GetColor(255,255,255), TRUE);

	//マップ表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//画像
			DrawGraph(j * 32, i * 32, mcImage[MapData[i][j]], TRUE);
			//枠線
			DrawBox(j * 32, i * 32, j * 32+33, i * 32+33,back_color, FALSE);
		}
	}

	//当たり判定箇所表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			//画像
			DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32,hit_chip[HitData[i][j]].color, TRUE);
			DrawGraph(j * 32-2, i * 32, HitImageHandle[HitData[i][j]], TRUE);
		}
	}

	//当たり判定マップチップの描画
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

//コンフィグモードの処理()
static void ConfigMode_Update()
{
	//マウスをクリックした瞬間
	if (MouseState(MOUSE_INPUT_LEFT) == 1)
	{
		//設定終了ボタン
		if (min_button[3].x - 32 <= MouseX && MouseX <= min_button[3].x && min_button[3].y - 16 <= MouseY && MouseY <= min_button[3].y + 16)
		{
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle02, DX_PLAYTYPE_BACK);
			time1 = GetNowCount();
			min_button[4].flag = 1;
			Stop_Update = 1;
		}

		//設定保存ボタン
		if (min_button[3].x - 32 <= MouseX && MouseX <= min_button[3].x && min_button[3].y - 16 -64 <= MouseY && MouseY <= min_button[3].y + 16 - 64)
		{
			if (config_menu[4].flag == ON)PlaySoundMem(SeHandle02, DX_PLAYTYPE_BACK);
			time1 = GetNowCount();
			min_button[5].flag = 1;
			Stop_Update = 1;
		}

		//曲変更ボタン
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

		//各種設定ボタン
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

		//BGM音量変更ボタン
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

		//SE音量変更ボタン
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

	//BGMの再生を止める
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

//コンフィグモードの描写
static void ConfigMode_Draw()
{
	//メッセージ
	DrawString(20, 20, "設定画面", GetColor(255, 255, 255));

	//終了ボタンの表示
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

	//設定保存ボタンの表示
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


	//コンフィグメニューの表示
	for (int i = 0; i < CF_NUM; i++)
	{
		DrawBox(config_menu[i].x-50, config_menu[i].y-3, config_menu[i].x-30, config_menu[i].y + 20-3, config_menu[i].color, FALSE);
		DrawString(config_menu[i].x, config_menu[i].y, config_menu[i].name, config_menu[i].color);
		if (config_menu[i].flag == ON)DrawGraph(config_menu[i].x - 53, config_menu[i].y - 15, Check_Image, TRUE);
	}

	//マウス座標の表示
	if(config_menu[2].flag == ON) MousePoint_Draw(100, 20);

	//BGM変更ボタンの表示
	DrawCircleAA(350.0, 845.0, 25.0, 124, GetColor(255, 255, 255), TRUE);
	DrawString(286, 900, "選択しているBGM", GetColor(255, 255, 255));
	DrawString(45, 900, "BGM音量", GetColor(255, 255, 255));
	DrawString(45+100, 900, "SE音量", GetColor(255, 255, 255));
	DrawFormatString(347, 838, back_color, "%d", SelectBGM+1);
	if (config_menu[3].flag == ON)
	{
		DrawTriangleAA(263.75, 845.0, 305, 860.0, 305, 830.0, GetColor(255, 255, 255), TRUE);
		DrawTriangleAA(436.25, 845.0, 395, 860.0, 395, 830.0, GetColor(255, 255, 255), TRUE);
	}

	//BGM音量変更ボタン
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

	//SE音量変更ボタン
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

	//BGMがOFFの時に×マークを描写、それ以外は音量の上下キーを描写
	if (config_menu[3].flag == OFF)
	{
		DrawLineAA(42.0, 787.0, 101.0, 878.0, GetColor(255, 0, 0), 10);
		DrawLineAA(101.0, 787.0, 42.0, 878.0, GetColor(255, 0, 0), 10);
	}
	else
	{
		DrawString(29, 820, "↑", GetColor(255, 255, 255));
		DrawString(29, 850, "↓", GetColor(255, 255, 255));
	}

	//SEがOFFの時に×マークを描写、それ以外は音量の上下キーを描写
	if (config_menu[4].flag == OFF)
	{
		DrawLineAA(142.0, 787.0, 201.0, 878.0, GetColor(255, 0, 0), 10);
		DrawLineAA(201.0, 787.0, 142.0, 878.0, GetColor(255, 0, 0), 10);
	}
	else
	{
		DrawString(129, 820, "↑", GetColor(255, 255, 255));
		DrawString(129, 850, "↓", GetColor(255, 255, 255));
	}
}

//エディター終了処理
static void End_Editor()
{
	//終了阻止キー
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
			DrawString(10, 10, "終了ボタンが入力されました。", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Escキーで終了を中止することができます。", GetColor(255, 255, 0));
		}

		if (t_time >= 2)
		{
			DrawString(10, 70, "エディターを終了しています...", GetColor(255, 255, 255));
		}

		if (t_time >= 4)
		{
			DrawFormatString(10, 100, GetColor(255, 255, 255), "%d秒後にメニュー画面に戻ります。", 8 - t_time);
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
			DrawString(10, 10, "終了ボタンが入力されました。", GetColor(255, 255, 255));
		}
		if (t_time >= 1)
		{
			DrawString(10, 40, "エディタを終了します。", GetColor(255, 255, 255));
		}
		if (t_time >= 3)
		{
			if(config_menu[11].flag == ON)Output_MapData();
			MapEditor_Finalize();
			DxLib_End();
		}
	}
}

//保存の処理
static void Save_Update()
{
	//保存阻止キー
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
			DrawString(10, 10, "保存ボタンが入力されました。", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Escキーで保存を中止することができます。", GetColor(255, 255, 0));
		}

		if (t_time >= 2)
		{
			DrawString(10, 70, "マップデータを保存しています...", GetColor(255, 255, 255));
			Output_MapData();
		}

		if (t_time >= 4 && 8 > t_time)
		{
			DrawFormatString(10, 100, GetColor(255, 255, 255), "あと%d秒お待ちください", 8 - t_time);
		}

		if (t_time >= 8)
		{
			DrawString(10, 130, "保存が完了しました。", GetColor(255, 255, 255));
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
			DrawString(10, 10, "保存ボタンが入力されました。", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			Output_MapData();
			DrawString(10, 40, "保存が完了しました。", GetColor(255, 255, 255));
		}
		if (t_time >= 2)
		{
			if (config_menu[4].flag == ON) PlaySoundMem(SeHandle05, DX_PLAYTYPE_BACK);
			min_button[0].flag = 0;
			Stop_Update = 0;
		}
	}
}

//マップデータの削除処理
static void Eliminate_Update()
{
	//削除阻止キー
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
			DrawString(10, 10, "削除ボタンが入力されました。", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "Escキーで削除を中止することができます。", GetColor(255,255,0));
		}

		if (t_time >= 4 && 8 > t_time)
		{
			DrawFormatString(10, 70, GetColor(255, 255, 255), "あと%d秒お待ちください", 8 - t_time);
		}

		if (t_time >= 8)
		{
			DrawString(10, 70, "マップデータを削除しています...", GetColor(255, 255, 255));
		}

		if (t_time >= 9)
		{
			DrawString(10, 100, "削除が完了しました。", GetColor(255, 255, 255));
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
			DrawString(10, 10, "削除ボタンが入力されました。", GetColor(255, 255, 255));
		}

		if (t_time >= 1)
		{
			DrawString(10, 40, "削除が完了しました。", GetColor(255, 255, 255));
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

//コンフィグ設定を呼び出す
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

//コンフィグ設定を終わる
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

//コンフィグ設定を保存する
static void Config_Save()
{
	Output_Config();
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (t_time >= 1)
	{
		DrawString(32,68,"保存が完了しました。",GetColor(255,255,255));
	}
	if (t_time >= 2)
	{
		min_button[5].flag = 0;
		Stop_Update = 0;
	}
}

//ファイルを読み込んだ際のメッセージ
static void LoadMessage()
{
	time2 = GetNowCount();
	t_time = (time2 - time1) / 1000;

	if (config_menu[5].flag == ON && MessageFlag[0] == 1 && t_time >= 0 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 10, "マップデータの読み込みが完了しました。", GetColor(255, 255, 255));
	}

	if (config_menu[5].flag == ON && MessageFlag[1] == 1 && t_time >= 1 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 40, "コンフィグデータの読み込みが完了しました。", GetColor(255, 255, 255));
	}

	if (config_menu[5].flag == ON && t_time >= 2 && SelectMode != Config_Edit && Stop_Update == 0)
	{
		DrawString(10, 70, "データは正常に読み込まれました。", GetColor(255, 255, 255));
	}

	if (t_time >= 8)
	{
		MessageFlag[0] = 0;
	}
}

//流れているBGMを変更する処理
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

//すべてのBGMハンドルの音量を調節する
static void AdjustmentBGMVolume(int volume)
{
	ChangeVolumeSoundMem(volume, BgmHandle00);
	ChangeVolumeSoundMem(volume, BgmHandle01);
	ChangeVolumeSoundMem(volume, BgmHandle02);
	ChangeVolumeSoundMem(volume, BgmHandle03);
	ChangeVolumeSoundMem(volume, BgmHandle04);
}

//すべてのSEハンドルの音量を調節する
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

//音楽関係の初期化
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

//ファイルの初期化関連のモジュール
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

//変数を初期化
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

//ローディング画面の素材を読み込む
static void LoadMaterial()
{
	t_time = 0;
	MouseCount = 0;
	LoadEnd = 0;
	LoadDivGraph("Data/Picture/LoadingImg.png", 60, 10, 6, 128, 128, LoadImageHandle, TRUE);
}

//ロード画面の表示
static void LoadScreen()
{
	time2 = GetNowCount();

	if (LoadEnd == 1)
	{
		t_time = (time2 - time1) / 1000;
	}

	DrawBox(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT, GetColor(255, 255, 255), TRUE);
	DrawGraph(EDITOR_WIDTH - 188, EDITOR_HEIGHT - 180, LoadImageHandle[MouseCount % 60], TRUE);
	DrawString(EDITOR_WIDTH - 188 - 50, EDITOR_HEIGHT - 190 + 148, "データを読み込んでいます", GetColor(222, 184, 135));
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