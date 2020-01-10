//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "COMMAND.hpp"
#include "MENU.hpp"
#include "PLAYER.hpp"
#include "ITEM.hpp"

//######################### マクロ定義 #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI画像のフォルダ名

#define	UI_NAME R"(ui1.png)"		//uiの名前

//######################### 列挙型 #################################
enum UI_IMAGE_TYPE
{
	UI_ARROW		//選択用の画像
};

//######################### クラス定義 #####################################
class UI
{
private:

	MENU *menuwindow;				//メニューウィンドウ

	COMMAND *BattleCommand;			//バトルコマンド

	STATEWINDOW *StateWindow;		//ステータスウィンドウ

	IMAGE *UiImage;					//uiの画像

	int BattleCommadType;			//選択したバトルコマンドの種類

	int ChoiseMenu;					//メニュー画面で選択した内容

public:

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//メニューウィンドウ関連
	void MenuOperation(KEYDOWN *,bool);	//メニューウィンドウのキーボード操作
	void DrawMenu(int ,int);				//メニューウィンドウ描画
	void SetChoiseMenu(std::vector<std::string>::iterator);	//メニューで選んだ内容を設定する
	int GetChoiseMenu();				//メニュー画面での選択内容を取得
	void ResetMenu();					//メニュー関係のメンバーをリセット
	void DrawChoiseMenu(PLAYER *,ITEM *[]);	//選んだメニュー内容ごとの描画
	bool GetIsChoise(void);				//選択されているか取得

	//バトルコマンド関連
	void SetBattleFlg(std::vector<std::string>::iterator);	//戦闘画面で選んだコマンドのフラグを設定する
	int GetChoiseCommamd();									//選択したコマンドの種類を取得
	void DrawCommand();										//バトルコマンド描画
	void BattleOperation(KEYDOWN *);						//戦闘画面の操作
	void BattleInit();										//バトルコマンドで使用する要素を初期化する

	//ステータスウィンドウ関連
	void SetStateWindow(int,int,int);	//ステータスウィンドウの設定をする
	void DrawStateWindow();			//ステータスウィンドウ描画

	void DrawWindow(int,int,int,int);				//ウィンドウを描画する

	//UI画像関係
	void DrawUiImage(int, int,int);				//UIの画像を描画する
	bool AddUiImage(const char *, const char *,int);//ui画像を追加する

	int GetUiImageWidth(int);					//ui画像の横幅取得
	int GetUiImageHeight(int);					//ui画像の高さ取得

	//選択肢を描画
	template<typename...Args>
	void ChoiseDraw(int x,int y,Args...args)
	{
		
		int Size = sizeof...(args);	//要素数取得

		std::vector<std::string> Str = { args... };		//展開

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 幅、高さ取得処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		int Strlen = 0;		//文字列の長さ取得用
		int Width = 0;
		std::string MaxStr;	//最も長い文字列

		MaxStr = Str[0].c_str();	//最も長い文字列に最初の文字列をセット

		for (int i = 0; i < Str.size(); i++)
		{
			if (MaxStr < Str[i].c_str())	//現在の最大文字列よりも大きければ
			{
				MaxStr = Str[i].c_str();	//最大文字列を更新
			}
		}

		//文字列の長さを取得
		Strlen = strlen(MaxStr.c_str());

		Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);	//横幅取得

		x -= (Width / 2);	//文字の幅の半分を引いて、真ん中に描画する

		int Height = GetFontSize();	//高さ取得
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 幅、高さ取得処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		//描画処理
		for (int i = 0; i < Size; ++i)		//要素数の分ループ
		{
			DrawFormatString(x, y + i * Height, GetColor(255, 255, 255), "%s", Str[i].c_str());	//文字描画
		}

		//vectorのメモリ解放を行う
		std::vector<std::string> v;			//空のvectorを作成する
		Str.swap(v);						//空と中身を入れ替える

		return;

	}

};
