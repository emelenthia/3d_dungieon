#include"Character_Show.h"
#include"DxLib.h"
#include"Colors.h"

void Character_Show::Draw()
{
	character_show_f->Draw(); 
	DrawString(20, 2, "キャラクターの能力の詳細を確認できます。", Colors::white);

}


int Character_Show::Reaction()
{
	return character_show_f->Reaction();
}