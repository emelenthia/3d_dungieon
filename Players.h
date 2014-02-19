#pragma once
#include "PlayerBase.h"
class Players :
	public PlayerBase
{
public:
	Players();
	~Players();
	void Draw();
	void Reaction();
	int player_h[96];
	int fast_speed;
	int slow_speed;
	static int moment; //���͂���Ă���������
	static int old_real_pos_x; //����O�̈ʒu���
	static int old_real_pos_y; //����O�̈ʒu���
	static const int pos_x_lu = 3; //�ڐG����̍���̍��W�B�v���C���[�̕`��ʒu���猩�����΍��W
	static const int pos_y_lu = 8; //�ڐG����̍���̍��W
	static const int pos_x_rd = 29; //�ڐG����̉E���̍��W
	static const int pos_y_rd = 48; //�ڐG����̉E���̍��W
	static int pos_x; //�`�悷��ۂ�x���W
	static int pos_y;
	static int direction;
	static int ndirection; //�΂߂̕����B���}���u
	static int real_pos_x; //�Q�[������x���W�B640�𒴂��Ă�������
	static int real_pos_y; //�Q�[������x���W�B480�𒴂��Ă�������
};

