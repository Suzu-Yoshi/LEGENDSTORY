//LIST.cpp
//魔法やスキルの一覧を管理するクラス

//################### ヘッダファイル読み込み ###########################
#include "LIST.hpp"

//################### クラス定義 ############################

//コンストラクタ
LIST::LIST()
{
	return;
}

//デストラクタ
LIST::~LIST()
{

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->CodeNum.swap(v);			//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<std::string> v2;			//空のvectorを作成する
	this->Name.swap(v2);					//空と中身を入れ替える

	return;
}

//名前設定
void LIST::SetName(std::string name)
{
	this->Name.push_back(name.c_str());	//名前設定
	return;
}

//コード番号設定
void LIST::SetCodeNum(int code)
{
	this->CodeNum.push_back(code);	//コード番号設定
	return;
}

//リストの要素数を設定
void LIST::SetSize(void)
{
	this->Size = this->CodeNum.size();	//サイズ設定
	return;
}

//読み込めたか設定
void LIST::SetIsLoad(bool Isload)
{
	this->IsLoad = Isload;	//読み込めたか設定
	return;
}

//名前取得
const char * LIST::GetName(int kind)
{
	return this->Name[kind].c_str();
}

//読み込めたか取得
bool LIST::GetIsLoad(void)
{
	return this->IsLoad;
}

//リストの要素数を取得
int LIST::GetListSize(void)
{
	return this->Size;
}

//コード番号取得
int LIST::GetCodeNum(int kind)
{
	return this->CodeNum[kind];
}
