/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				　 */

//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "ANIMATION.hpp"
#include "FONT.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MAPIMAGE.hpp"
#include "TEXTSTR.hpp"


//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成
IMAGE *title;						//タイトル画像
IMAGE *back;						//背景画像
FONT *font;							//フォント
TEXTSTR *text;						//文字列
PLAYER *player;						//主人公
MAPIMAGE *mapimage;					//マップチップのデータ
MAP *mapdata[MAP_LAYER_KIND];		//マップデータ

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン

bool StrSet_Flg = false;					//文字列設定フラグ
bool GameEnd_Flg = false;					//ゲーム終了フラグ

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 読み込み処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//タイトル画像を生成
	if (title->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK);			//背景画像を生成
	if (back->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	text = new TEXTSTR();

	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//読み込み失敗
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //読み込み失敗
	player->SetInit();	//初期設定

	mapimage = new MAPIMAGE();	//マップチップ生成
	if (mapimage->GetIsLoad() == false) { return -1; }	//読み込み失敗

	mapdata[FIRST_LAYER] = new MAP();	//一層目のマップデータ生成
	if (mapdata[FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1) == false) { return -1; }		//読み込み失敗

	mapdata[SECOND_LAYER] = new MAP();	//二層目のマップデータ生成
	if (mapdata[SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2) == false) { return -1; }		//読み込み失敗


	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 読み込み処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	while (TRUE)	//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		keydown->KeyDownUpdate();	//キーの入力状態を更新する

		fps->Update();				//FPSの処理[更新]

		keydown->IsKeyDown(KEY_INPUT_LEFT);

		if (GameEnd_Flg)		//ゲーム終了フラグが立っていたら
		{
			break;				//ループを抜け、ゲーム終了
		}

		//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:		//タイトル画面だったら
			
			Title();					//タイトル画面の処理

			break;

		case (int)GAME_SCENE_PLAY:		//プレイ画面だったら

			Play();						//プレイ画面の処理

			break;

		case (int)GAME_SCENE_END:		//エンド画面だったら

			End();						//エンド画面の処理

			break;

		default:
			break;

		}


		//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

		fps->Draw(0, 0);				//FPSの処理[描画]

		ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();				//FPSの処理[待つ]
	}

	delete title;			//titleを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete text;			//textを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄
	delete mapimage;		//mapimageを破棄

	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		delete mapdata[cnt];	//mapdataを破棄
	}

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の処理
void Title()
{

	back->Draw(0, 0);	//背景画像描画

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//画面中央にタイトル描画

	std::vector<std::string> str = { "START","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//描画文字セット

		StrSet_Flg = true;		//文字列設定

		font->SetSize(BIG_FONTSIZE);		//フォントサイズ変更
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),true);	//描画（矢印付き）

	if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押されたら
	{
		text->Next();	//選択を一つ次へ
	}
	else if (keydown->IsKeyDown(KEY_INPUT_W))	//Wキーを押されたら
	{
		text->Back();	//選択を一つ前へ
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))				//エンターキーを押されたら
	{
		if (*text->GetPos() == str.begin()->c_str())		//選択している文字列が"START"だったら
		{
			StrSet_Flg = false;						//文字列未設定
			GameSceneNow = (int)GAME_SCENE_PLAY;	//プレイ画面へ
		}
		else
		{
			GameEnd_Flg = true;	//ゲーム終了
		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}

//プレイ画面の処理
void Play()
{
	//マップ描画処理
	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		mapdata[cnt]->Draw(mapimage->GetHandle((int)FILED));		//マップ描画
	}

	std::vector<std::string> str = { "PUSH SPACE" };
	
	text->SetText(str);		//文字列セット
	
	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),false);	//文字列描画（矢印なし）

	player->Operation(keydown);	//プレイヤーキー操作
	player->DrawAnime();		//アニメーション描画

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		GameSceneNow = (int)GAME_SCENE_END;	//エンド画面へ
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	return;
}

//エンド画面の処理
void End()
{

	std::vector<std::string> str = { "PUSH BACK" };

	text->SetText(str);		//文字列セット

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),false,GetColor(255,255,255));	//文字列描画（色指定）（矢印なし）


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_BACK))
	{
		GameSceneNow = (int)GAME_SCENE_TITLE;	//タイトル画面へ
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}