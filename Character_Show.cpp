#include"Character_Show.h"
#include"DxLib.h"
#include"Colors.h"

void Character_Show::Draw()
{
	character_show_f->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
	DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す
	DrawString(20, 2, "キャラクターの能力の詳細を確認できます。", Colors::white);
}


int Character_Show::Reaction()
{
	return character_show_f->Reaction();
}


