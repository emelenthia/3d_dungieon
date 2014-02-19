#include "DxLib.h"
#include<time.h>
#include "SceneBase.h"
#include"Battle.h"
#include"Field.h"
#include"Key_Input.h"
#include"Flags.h"
#include"Events.h"
#include"Scene.h"
#include"Character_Haruka.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	//SetBackgroundColor(0, 0, 0); //�w�i�̐F�ύX5
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Scene scene; //���݂̏��
	Key_Input key_input; //�L�[���͗p
	//int reaction_return; //Reaction()�̕Ԃ�l���󂯎��
	Flags flags;
	Events *events = Events::GetInstance();
	//Character_Haruka *Haruka;
	Character_Data *char_p[2];
	char_p[0] = Character_Haruka::GetInstance();
	while (1) //���C�����[�v
	{

		ClearDrawScreen(); //��ʂ��N���A�B�`�揈���͂������ɏ���

		key_input.KeyUpdate(); //�L�[����
		//reaction_return = nowpointa->Reaction(); //�L�[���͂Ȃǂɂ����̍X�V
		scene.Reaction(); //�L�[���͂Ȃǂɂ����̍X�V
		scene.Draw(); //���݂̏�ʂ̕`��


		ScreenFlip(); //���ƕ\�̒�����B�`�揈��������ɏ���


		if (ProcessMessage()) //�~�N���b�N�҂�
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)  //Esc���͑҂�
		{
			break;
		}
	}
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}