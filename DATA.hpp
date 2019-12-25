//DATA.hpp
//データクラス
//テキストファイルの文字コードをANSIにして保存する

#pragma once

//############## ヘッダファイル読み込み #################
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "PLAYER.hpp"
#include "ENEMY.hpp"


//############## マクロ定義：ファイル名、パス ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//メッセージテキストのファイル名
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//プレイヤーのデータのファイル名
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//敵のデータのファイル名

#define DATA_NAME	R"(msg.txt)"			//メッセージテキストの名前
#define PLAYER_DATA_NAME	R"(Player_Data.csv)"//プレイヤーのデータのcsvファイル
#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//敵のデータの名前

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//############## クラス定義 #####################
class DATA
{
private:

public:

	DATA();		//コンストラクタ

	~DATA();								//デストラクタ

	bool LoadPlayer(PLAYER *,const char *, const char *);		//読み込み（味方データ）
	bool LoadEnemy(ENEMY *[],const char *, const char *);		//読み込み（敵データ）
	bool Save(PLAYER *,const char *,const char *);		//セーブ

};
