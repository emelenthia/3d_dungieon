#include"Character_Show.h"
#include"DxLib.h"
#include"Colors.h"

void Character_Show::Draw()
{
	character_show_f->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
	DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
	DrawString(20, 2, "�L�����N�^�[�̔\�͂̏ڍׂ��m�F�ł��܂��B", Colors::white);
}


int Character_Show::Reaction()
{
	return character_show_f->Reaction();
}


