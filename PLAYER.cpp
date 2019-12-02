//PLAYER.cpp
//プレイヤークラス

//############## ヘッダファイル読み込み ################
#include "PLAYER.hpp"

//############## クラス定義 ##################

//コンストラクタ
PLAYER::PLAYER()
{
	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	delete this->Anime;
	delete this->Collision;
	delete this->Ilast;
	delete this->menuwindow;
	delete this->BattleCommand;
	return;
}

//初期設定
bool PLAYER::SetInit()
{
	this->HP = 100;		//初期HP設定
	this->ATK = 10;		//初期攻撃力設定
	this->DEF = 10;		//初期防御力設定
	this->SPD = 10;		//初期速度設定
	this->Dist = FLONT;	//初期向き設定
	this->MoveSpeed = 5;//初期移動速度設定

	this->BattleFlgInit();	//バトル用フラグ初期化

	this->Ilast->SetInit();	//画像初期設定
	this->IsKeyDown = false;//キーボード押されていない
	this->IsMenu = false;	//メニューウィンドウ描画されていないS

	this->Collision = new COLLISION();		//当たり判定の領域を作成
	this->Collision->SetValue(GAME_LEFT, GAME_TOP, this->Anime->GetWidth(),this->Anime->GetHeight());	//当たり判定の領域を設定

	this->menuwindow = new MENU();			//メニューウィンドウ作成

	this->BattleCommand = new COMMAND();	//バトルコマンド作成


	return true;
}

//アニメーション画像設定
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：画像の総分割数
//引　数：int：画像の横向きの分割数
//引　数：int：画像の縦向きの分割数
//引　数：int：画像の分割された横の大きさ
//引　数：int：画像の分割された縦の大きさ
//引　数：double：次の画像に変更する速さ
//引　数：bool：アニメーションをループするかどうか
bool PLAYER::SetAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->Anime = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->Anime->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}

//画像設定
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//読み込み失敗

	return true;

}

//HP設定
void PLAYER::SetHP(int hp)
{
	this->HP = hp;
	return;
}

//攻撃力設定
void PLAYER::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//防御力設定
void PLAYER::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//速度設定
void PLAYER::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//移動速度設定
void PLAYER::SetMoveSpeed(int movespeed)
{
	this->MoveSpeed = movespeed;
	return;
}

//生きているか設定
void PLAYER::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//キーボードで操作できるか設定
void PLAYER::SetKeyOperation(bool Iskeyoperation)
{
	this->IsKeyOperation = IsKeyOperation;
	return;
}


//描画できるか設定
void PLAYER::SetIsDraw(bool Isdraw)
{
	this->IsDraw = IsDraw;
	return;
}

//位置を設定
//引数：int：X位置を相対的に指定
//引数：int：Y位置を相対的に指定
void PLAYER::SetPosition(int x, int y)
{
	this->Collision->Left += x;	//X位置を設定
	this->Collision->Top += y;	//Y位置を設定

	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//戦闘画面で選んだコマンドを設定する
void PLAYER::SetBattleFlg(std::vector<std::string>::iterator choise_itr)
{
	this->BattleFlgInit();	//バトル用フラグ初期化
	if (*choise_itr == "こうげき")			//攻撃を選んだ場合
	{
		this->AtkFlg = true;	//攻撃フラグセット
		return;
	}
	else if (*choise_itr == "ぼうぎょ")		//防御を選んだ場合
	{
		this->DefFlg = true;	//防御フラグセット
		return;
	}
	else if (*choise_itr == "まほう")			//魔法を選んだ場合
	{
		this->MagicFlg = true;	//魔法フラグセット
		return;	
	}
	else if (*choise_itr == "アイテム")		//アイテムを選んだ場合
	{
		this->ItemFlg = true;	//アイテムフラグセット
		return;
	}
	else if (*choise_itr == "にげる")			//逃げるを選んだ場合
	{
		this->EscFlg = true;	//逃げるフラグセット
		return;
	}
	return;
}

//バトル用フラグ初期化
void PLAYER::BattleFlgInit()
{
	this->AtkFlg = false;	//攻撃フラグ
	this->DefFlg = false;	//防御フラグ
	this->MagicFlg = false;	//魔法フラグ
	this->ItemFlg = false;	//アイテムフラグ
	this->EscFlg = false;	//逃げるフラグ
	return;
}

//体力取得
int PLAYER::GetHP(void)
{
	return this->HP;
}

//攻撃力取得
int PLAYER::GetATK(void)
{
	return this->ATK;
}

//防御力取得
int PLAYER::GetDEF(void)
{
	return this->DEF;
}

//速度取得
int PLAYER::GetSPD(void)
{
	return this->SPD;
}

//移動速度取得
int PLAYER::GetMoveSpeed(void)
{
	return this->MoveSpeed;
}

//生きているか取得
bool PLAYER::GetIsArive()
{
	return this->IsArive;
}

//描画できるか取得
bool PLAYER::GetIsDraw()
{
	return this->IsDraw;
}

//キーボード操作できるか取得
bool PLAYER::GetKeyOperation()
{
	return this->IsKeyOperation;
}

//当たり判定を取得
COLLISION * PLAYER::GetCollision()
{
	return this->Collision;
}

//操作
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (this->IsMenu ==false && keydown->IsKeyDown(KEY_INPUT_W))		//メニュー描画中でなく、Wキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = BACK;			//移動方向を上にする
		this->MoveUp();				//上へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//メニュー描画中でなく、Sキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = FLONT;			//移動方向下
		this->MoveDown();			//下へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//メニュー描画中でなく、Aキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = LEFT;			//移動方向左
		this->MoveLeft();			//左へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//メニュー描画中でなく、Dキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = RIGHT;			//移動方向右
		this->MoveRight();			//右へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_Q))	//Qキーを押しているとき
	{
		this->IsMenu = true;		//メニュー描画開始
	}
	else
	{
		this->IsKeyDown = false;	//キー入力なし
	}

	if (this->IsMenu)	//メニュー描画中
	{
		if (keydown->IsKeyDown(KEY_INPUT_ESCAPE))	//エスケープキーを押されたら
		{
			this->IsMenu = false;	//メニュー描画終了
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_W))	//Wキーを押された瞬間
		{
			this->menuwindow->Back();	//前の要素へ
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//Sキーを押された瞬間
		{
			this->menuwindow->Next();	//次の要素へ
		}
		this->DrawMenu();	//メニューウィンドウ描画
	}


	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;

}

//戦闘画面の操作
void PLAYER::BattleOperation(KEYDOWN *keydown)
{
	//コマンド選択処理
	if (keydown->IsKeyDownOne(KEY_INPUT_D))			//Dキーを押された瞬間
	{
		this->BattleCommand->Next();	//次の要素へ
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_A))	//Aキーを押された瞬間
	{
		this->BattleCommand->Back();	//前の要素へ
	}

	//コマンド決定処理
	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーが押された瞬間
	{
		auto itr = this->BattleCommand->GetCommand();	//選択しているコマンドを取得
		this->SetBattleFlg(itr);	//バトルフラグ設定
	}

	//コマンド決定後処理
	if (this->AtkFlg)	//攻撃を選んだ場合
	{
		this->DrawAtk();
	}
	else if (this->DefFlg)	//防御を選んだ場合
	{
		this->DrawDef();
	}
	else if (this->MagicFlg)	//魔法を選んだ場合
	{

	}
	else if (this->ItemFlg)		//アイテムを選んだ場合
	{

	}
	else if (this->EscFlg)		//逃げるを選んだ場合
	{

	}

	return;
}


//描画
void PLAYER::DrawAnime()
{

	if (this->IsKeyDown)		//キーボードが押されているとき
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, true);	//アニメーションで描画

	}
	else						//キーボードが押されていないとき
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, false);	//通常描画
	}
}

//メニューウィンドウ描画
void PLAYER::DrawMenu()
{
	this->menuwindow->Draw();	//メニュー描画
	return;
}

//バトルコマンド描画
void PLAYER::DrawCommand()
{
	this->BattleCommand->Draw();	//描画
	return;
}

//攻撃を選んだ時の描画
void PLAYER::DrawAtk()
{
	DrawBox(100, 100, 300, 300, GetColor(255, 0, 0), TRUE);	
	return;
}

//防御を選んだ時の描画
void PLAYER::DrawDef()
{
	DrawBox(100, 100, 300, 300, GetColor(0, 255, 0), TRUE);
}

//上へ移動
void PLAYER::MoveUp()
{
	if (this->Collision->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->Collision->Top -= this->MoveSpeed;	//当たり判定と、描画位置を上へ移動
	}

	return;
}

//下へ移動
void PLAYER::MoveDown()
{
	if (this->Collision->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->Collision->Top += this->MoveSpeed;	//下へ移動
	}
	return;
}

//左へ移動
void PLAYER::MoveLeft()
{
	if (this->Collision->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->Collision->Left -= this->MoveSpeed;	//左へ移動
	}
	return;
}

//右へ移動
void PLAYER::MoveRight()
{
	if (this->Collision->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->Collision->Left += this->MoveSpeed;	//右へ移動
	}
	return;
}

//ダメージ計算
void PLAYER::DamegeCalc()
{

}
