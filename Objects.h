#pragma once
class Objects
{
public:
	Objects();
	~Objects();
	int checkhitflag; //�ʂ蔲���s�\����B0�Ȃ�ʂ蔲������
	void HitCheck(); //�Փ˔���
	virtual void Draw();
	void MakeObject(int temporary_pos_x, int temporary_pos_y, int temporary_pos_x_lu, int temporary_pos_y_lu, 
		int temporary_pos_x_rd, int temporary_pos_y_rd, int temporary_hundle_number, int temporary_checkhitflag = 1); //�I�u�W�F�N�g�����������܂�
	int pos_x_lu; //�I�u�W�F�N�g�̍����x���W�B����p
	int pos_y_lu;
	int pos_x_rd;
	int pos_y_rd; //�I�u�W�F�N�g�̉E����y���W
	int pos_x; //�I�u�W�F�N�g�̍����x���W�B�`��p
	int pos_y; //�I�u�W�F�N�g�̍����x���W�B�`��p
	int mapchip_h2[40]; //�摜�̃n���h��
	int hundle_number; //�I�u�W�F�N�g�̉摜�̃n���h��
};

