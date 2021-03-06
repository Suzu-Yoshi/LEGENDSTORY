//ENEMY.cpp
//敵のクラス

//###################### ヘッダファイル読み込み ######################
#include "ENEMY.hpp"

//###################### クラス定義 ##########################

//コンストラクタ
ENEMY::ENEMY(const char *dir,const char *name)
{
	//メンバ変数初期化
	this->Name = "";
	this->HP = 0;
	this->ATK = 0;
	this->DEF = 0;
	this->SPD = 0;
	this->MaxHP = 0;
	this->EXP = 0;
	this->IsLoad = false;	
	this->SetIsArive(true);	//生きている

	this->EmergenceMap = 0;	//出現MAP
	this->EncounteRate = 0;	//遭遇率

	this->EneType = 0;	//敵の種類
	this->ChoiseSkil = -1;	//使用するスキル初期化

	//画像設定
	if (this->SetImage(dir, name))	//画像が読み込めていたら
	{
		this->IsLoad = true;	//読み込めた
	}
	else		//画像が読み込めていなかったら
	{
		this->IsLoad = false;
	}

	this->SetKeyOperation(false);	//キーボードで操作不可

	return;
}

//デストラクタ
ENEMY::~ENEMY()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Skil.swap(v);		//空と中身を入れ替える

	return;
}

//名前設定
void ENEMY::SetName(const char *name)
{
	this->Name += name;
	return;
}

//最大体力設定
void ENEMY::SetMaxHP(int maxhp)
{
	this->MaxHP = maxhp;
	return;
}

//HP設定
void ENEMY::SetHP(int hp)
{
	this->HP = hp;
	return;
}

//攻撃力設定
void ENEMY::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//防御力設定
void ENEMY::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//速度設定
void ENEMY::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//スキル設定
void ENEMY::SetSkil(int skil)
{
	this->Skil.push_back(skil);
	return;
}

//経験値設定
void ENEMY::SetEXP(int exp)
{
	this->EXP = exp;
	return;
}

//出現MAPの設定
void ENEMY::SetEmergenceMap(int mapno)
{
	this->EmergenceMap = mapno;
	return;
}

//遭遇率の設定
void ENEMY::SetEncounteRate(int encounterate)
{
	this->EncounteRate = encounterate;
	return;
}

//敵ステータス初期設定
void ENEMY::StateSetInit()
{

	this->HP = this->MaxHP;	//HP再設定

	this->SetIsArive(true);	//生きている

	this->ChoiseSkil = -1;	//使用するスキル初期化

	return;
}

//名前取得
const char * ENEMY::GetName(void)
{
	return this->Name.c_str();
}

//体力取得
int ENEMY::GetHP(void)
{
	return this->HP;
}

//攻撃力取得
int ENEMY::GetATK(void)
{
	return this->ATK;
}

//防御力取得
int ENEMY::GetDEF(void)
{
	return this->DEF;
}

//速度取得
int ENEMY::GetSPD(void)
{
	return this->SPD;
}

//経験値取得
int ENEMY::GetEXP(void)
{
	return this->EXP;
}

//出現MAPの取得
int ENEMY::GetEmergenceMap(void)
{
	return this->EmergenceMap;
}

//遭遇率の取得
int ENEMY::GetEncounteRate(void)
{
	return this->EncounteRate;
}

//読み込めたかを取得
bool ENEMY::GetIsLoad()
{
	return this->IsLoad;
}

//使用するスキルの種類を取得
int ENEMY::GetChoiseSkil()
{
	return this->ChoiseSkil;
	//return 2;
}

//行動決定処理
void ENEMY::ActDecision(void)
{
	int rand = GetRand(this->Skil.size() - 1);		//使用するスキルをランダムで決定

	this->ChoiseSkil = rand;	//使用するスキル設定

	return;
	
}
