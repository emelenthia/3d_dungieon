#include "Dungeon.h"
#include"DxLib.h"
#include<stdio.h>
#include"Key_Input.h"
#include"Options.h"
#include<math.h>
#include"Flags.h"
#include"SaveData.h"
#include"Party.h"

#define PI    3.1415926535897932384626433832795f

int Dungeon::floors = 0;

Dungeon::Dungeon()
{
	black = GetColor(0, 0, 0);
	yellow = GetColor(255, 255, 0);
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);

	SetTransColor(255, 255, 255); //���𓧉ߐF��
	yajirushi_h = LoadGraph("./dungeon/yajirushi.png");
	SetTransColor(0, 0, 0); //�ꉞ�߂�

	if (yajirushi_h == -1)
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}
	SetUseZBuffer3D(TRUE); //�[�x�X�e���V���o�b�t�@
	SetWriteZBuffer3D(TRUE); //�B���̂Ƃ���K�v�Ȃ��c�Ǝv������A����ʍs�̕ǂ��r�Ԃ邱�Ƃւ̑Ώ����ł���B��u�Â��Ȃ�͎̂d���Ȃ�?
	
	savedata = SaveData::GetInstance();
	options = Options::GetInstance();
	party = Party::GetInstance();
	

}


Dungeon::~Dungeon()
{
}


void Dungeon::Draw()
{
	//�J�����̈ړ�
	//target_camera = VGet(pos_x * 100 + (muki % 2 ? (muki - 1 ? 0 : 100) : 50), y * 100 - 50, (pos_z * 100 + (muki % 2 ? 50 : (muki ? 0 : 100))));
	//player_camera = VGet(pos_x * 100 + (muki % 2 ? (muki - 1 ? 100 : 0) : 50), y * 100 - 50, (pos_z * 100 + (muki % 2 ? 50 : (muki ? 100 : 0))));
	SetCameraPositionAndTarget_UpVecY(player_camera, target_camera);

	//���C���`��
	DrawMap_c(map_data, x_max, z_max);

	//���̑�
	if (state == 7)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 212); //����
		DrawBox(0, 190, 640, 290, black, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
		DrawBox(0, 190, 640, 195, yellow, TRUE);
		DrawBox(0, 285, 640, 290, yellow, TRUE);
		DrawBox(0, 240 + nowchoose * 20, 640, 260 + nowchoose * 20, yellow, TRUE);
		DrawString(235, 200, "�_���W��������o�܂���?", white);
		DrawString(310, 240, "�͂�", (nowchoose ? white : black));
		DrawString(305, 260, "������", (nowchoose ? black : white));
	}
	else
	{
		DrawMiniMap();
	}

	//�p�[�e�B�̕`��
	party->Draw();
}


int Dungeon::Reaction()
{
	//�}�b�v�̓��j
	if (!(savedata->map_open_flag[floors - 1][pos_z][pos_x]))
	{
		savedata->map_open_flag[floors - 1][pos_z][pos_x] = 1;
	}

	if (!state)
	{

		if (Key_Input::buff_time[KEY_INPUT_LEFT] == 1)
		{
			state = 4;
		}
		else if (Key_Input::buff_time[KEY_INPUT_RIGHT] == 1)
		{
			state = 2;
		}
		else if (Key_Input::buff_time[KEY_INPUT_DOWN] == 1)
		{
			state = 3;
		}
		else if (Key_Input::buff_time[KEY_INPUT_A] == 1)
		{
			for (int i = 0; !i; i++) //�ׂ��ǂȂ�ړ����Ȃ�
			{
				if (muki == 0 && (map_data[pos_z][pos_x] & 8))
				{
					break;
				}
				if (muki == 1 && (map_data[pos_z][pos_x] & 1))
				{
					break;
				}
				if (muki == 2 && (map_data[pos_z][pos_x] & 2))
				{
					break;
				}
				if (muki == 3 && (map_data[pos_z][pos_x] & 4))
				{
					break;
				}
				state = 6;
			}
		}
		else if (Key_Input::buff_time[KEY_INPUT_D] == 1)
		{
			for (int i = 0; !i; i++) //�ׂ��ǂȂ�ړ����Ȃ�
			{
				if (muki == 0 && (map_data[pos_z][pos_x] & 2))
				{
					break;
				}
				if (muki == 1 && (map_data[pos_z][pos_x] & 4))
				{
					break;
				}
				if (muki == 2 && (map_data[pos_z][pos_x] & 8))
				{
					break;
				}
				if (muki == 3 && (map_data[pos_z][pos_x] & 1))
				{
					break;
				}
				state = 5;
			}
		}
		else if (Key_Input::buff_time[KEY_INPUT_UP] == 1)
		{
			for (int i = 0; !i; i++)
			{
				if (muki == 0 && (map_data[pos_z][pos_x] & 1))
				{
					break;
				}
				if (muki == 1 && (map_data[pos_z][pos_x] & 2))
				{
					break;
				}
				if (muki == 2 && (map_data[pos_z][pos_x] & 4))
				{
					break;
				}
				if (muki == 3 && (map_data[pos_z][pos_x] & 8))
				{
					break;
				}
				state = 1;
			}
		}
		else if (Key_Input::buff_time[KEY_INPUT_Z] == 1 && !Flags::menuflag && pos_x == start_x && pos_z == start_z) //�X�^�[�g�n�_�Ȃ�A�X�ɖ߂�
		{
			state = 7;
		}
	}

	switch (state)
	{

	case 1: //�O�i
	{
			  time += options->move_speed;
			  if (time >= 60 && !flaging) //����ʍs�̎��ɕǂ������Ă��܂��̂ŉ��}���u
			  {
				  flaging++;
				  switch (muki)
				  {
				  case 0:
					  pos_z++;
					  break;
				  case 1:
					  pos_x++;
					  break;
				  case 2:
					  pos_z--;
					  break;
				  case 3:
					  pos_x--;
					  break;
				  default:
					  break;
				  }
			  }
			  if (time < 100)
			  {
				  switch (muki)
				  {
				  case 0:
					  target_camera.z += options->move_speed;
					  player_camera.z += options->move_speed;
					  break;
				  case 1:
					  target_camera.x += options->move_speed;
					  player_camera.x += options->move_speed;
					  break;
				  case 2:
					  target_camera.z -= options->move_speed;
					  player_camera.z -= options->move_speed;
					  break;
				  case 3:
					  target_camera.x -= options->move_speed;
					  player_camera.x -= options->move_speed;
					  break;
				  default:
					  DrawString(0, 0, "Error! Dungeon.cpp have missing muki.",GetColor(255,0,0));
					  WaitKey();
					  break;
				  }
			  }
			  else
			  {
				  switch (muki)
				  {
				  case 0:
					  target_camera.z = pos_z * 100 + 100;
					  player_camera.z = pos_z * 100;
					  break;
				  case 1:
					  target_camera.x = pos_x * 100 + 100;
					  player_camera.x = pos_x * 100;
					  break;
				  case 2:
					  target_camera.z = pos_z * 100;
					  player_camera.z = pos_z * 100 + 100;
					  break;
				  case 3:
					  target_camera.x = pos_x * 100;
					  player_camera.x = pos_x * 100 + 100;
					  break;
				  default:
					  DrawString(0, 0, "Error! Dungeon.cpp have missing muki.", GetColor(255, 0, 0));
					  WaitKey();
					  break;
				  }
				  flaging = 0;
				  state = 0;
				  time = 0;
			  }
	}
		break;

	case 2:
	{
			  if (time < 50)
			  {
				  time += options->revolve_speed;
				  Return_right();
			  }
			  else
			  {
				  time = 0;
				  state = 0;
			  }
	}
		break;
	case 3: //�������B2�{����2��E�]��
	{
				options->revolve_speed *= 2;
				switch (muki)
				{
				case 0:
					/*if (time < 50)
					{
					time += options->revolve_speed;
					Return_right();
					}
					else
					{
					time = 0;
					down_help++;
					if (down_help>1) //�E�]���2��Ăяo��
					{
					state = 0;
					down_help = 0;
					}
					}*/
					/*if (time < 100)
					{
					time += 1;
					target_camera.z -= 1;
					player_camera.z += 1;
					if (time > 100)
					{
					target_camera.z += time - 100;
					player_camera.z -= time - 100;
					}
					}
					else
					{
					time = 0;
					state = 0;
					}*/
					if (time < 100)
					{
						if (time < 50)
						{
							time += options->revolve_speed;
							target_camera.x += options->revolve_speed;
							player_camera.x -= options->revolve_speed;
							target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 50)
							{
								target_camera.x -= time - 50;
								player_camera.x += time - 50;
								target_camera.z = pos_z * 100 + 50;
								player_camera.z = pos_z * 100 + 50;
								time = 50;
							}
						}
						else
						{
							time += options->revolve_speed;
							target_camera.x -= options->revolve_speed;
							player_camera.x += options->revolve_speed;
							target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 100)
							{
								target_camera.x += time - 100;
								player_camera.x -= time - 100;
								target_camera.z = pos_z * 100;
								player_camera.z = pos_z * 100 + 100;
							}

						}
					}
					else
					{
						time = 0;
						state = 0;
						muki = 2;
					}
					break;

				case 1: //�E����
					if (time < 100)
					{
						if (time < 50)
						{
							time += options->revolve_speed;
							target_camera.x -= options->revolve_speed;
							player_camera.x += options->revolve_speed;
							target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 50)
							{
								target_camera.x += time - 50;
								player_camera.x -= time - 50;
								target_camera.z = pos_z * 100;
								player_camera.z = pos_z * 100 + 100;
								time = 50;
							}
						}
						else
						{
							time += options->revolve_speed;
							target_camera.x -= options->revolve_speed;
							player_camera.x += options->revolve_speed;
							target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 100)
							{
								target_camera.x += time - 100;
								player_camera.x -= time - 100;
								target_camera.z = pos_z * 100 + 50;
								player_camera.z = pos_z * 100 + 50;
							}

						}
					}
					else
					{
						time = 0;
						state = 0;
						muki = 3;
					}
					break;

				case 2: //������
					if (time < 100)
					{
						if (time < 50)
						{
							time += options->revolve_speed;
							target_camera.x -= options->revolve_speed;
							player_camera.x += options->revolve_speed;
							target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 50)
							{
								target_camera.x += time - 50;
								player_camera.x -= time - 50;
								target_camera.z = pos_z * 100;
								player_camera.z = pos_z * 100 + 100;
								time = 50;
							}
						}
						else
						{
							time += options->revolve_speed;
							target_camera.x += options->revolve_speed;
							player_camera.x -= options->revolve_speed;
							target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 100)
							{
								target_camera.x -= time - 100;
								player_camera.x += time - 100;
								target_camera.z = pos_z * 100 + 100;
								player_camera.z = pos_z * 100;
							}

						}
					}
					else
					{
						time = 0;
						state = 0;
						muki = 0;
					}
					break;

				case 3: //�����E
					if (time < 100)
					{
						if (time < 50)
						{
							time += options->revolve_speed;
							target_camera.x += options->revolve_speed;
							player_camera.x -= options->revolve_speed;
							target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 50)
							{
								target_camera.x -= time - 50;
								player_camera.x += time - 50;
								target_camera.z = pos_z * 100 + 100;
								player_camera.z = pos_z * 100;
								time = 50;
							}
						}
						else
						{
							time += options->revolve_speed;
							target_camera.x += options->revolve_speed;
							player_camera.x -= options->revolve_speed;
							target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
							player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
							if (time >= 100)
							{
								target_camera.x -= time - 100;
								player_camera.x += time - 100;
								target_camera.z = pos_z * 100 + 50;
								player_camera.z = pos_z * 100 + 50;
							}

						}
					}
					else
					{
						time = 0;
						state = 0;
						muki = 1;
					}
					break;
				}
	}
		options->revolve_speed /= 2;
		break;

	case 4:
	{
			  if (time < 50)
			  {
				  time += options->revolve_speed;
				  switch (muki)
				  {
				  case 0:
					  target_camera.x -= options->revolve_speed;
					  player_camera.x += options->revolve_speed;
					  target_camera.z -= options->revolve_speed;
					  player_camera.z += options->revolve_speed;
					  if (time >= 50)
					  {
						  target_camera.x += time - 50;
						  player_camera.x -= time - 50;
						  target_camera.z += time - 50;
						  player_camera.z -= time - 50;
						  muki = 3;
					  }
					  break;
				  case 1:
					  target_camera.x -= options->revolve_speed;
					  player_camera.x += options->revolve_speed;
					  target_camera.z += options->revolve_speed;
					  player_camera.z -= options->revolve_speed;
					  if (time >= 50)
					  {
						  target_camera.x += time - 50;
						  player_camera.x -= time - 50;
						  target_camera.z -= time - 50;
						  player_camera.z += time - 50;
						  muki--;
					  }
					  break;
				  case 2:
					  target_camera.x += options->revolve_speed;
					  player_camera.x -= options->revolve_speed;
					  target_camera.z += options->revolve_speed;
					  player_camera.z -= options->revolve_speed;
					  if (time >= 50)
					  {
						  target_camera.x -= time - 50;
						  player_camera.x += time - 50;
						  target_camera.z -= time - 50;
						  player_camera.z += time - 50;
						  muki--;
					  }
					  break;
				  case 3:
					  target_camera.x += options->revolve_speed;
					  player_camera.x -= options->revolve_speed;
					  target_camera.z -= options->revolve_speed;
					  player_camera.z += options->revolve_speed;
					  if (time >= 50)
					  {
						  target_camera.x -= time - 50;
						  player_camera.x += time - 50;
						  target_camera.z += time - 50;
						  player_camera.z -= time - 50;
						  muki--;
					  }
					  break;
				  default:
					  break;
				  }
			  }
			  else
			  {
				  time = 0;
				  state = 0;
			  }
	}
		break;

	case 5: //D�{�^����������
		time += options->move_speed;
		if (time < 100)
		{
			switch (muki)
			{
			case 0: //�����
				target_camera.x += options->move_speed;
				player_camera.x += options->move_speed;
				if (time >= 50 && !flaging) //�����ňړ����邱�Ƃɂ��ǂ̌����������������Ȃ�̂�h��
				{
					pos_x++;
					flaging++;
				}
				break;
			case 1:
				target_camera.z -= options->move_speed;
				player_camera.z -= options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_z--;
					flaging++;
				}
				break;
			case 2:
				target_camera.x -= options->move_speed;
				player_camera.x -= options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_x--;
					flaging++;
				}
				break;
			case 3:
				target_camera.z += options->move_speed;
				player_camera.z += options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_z++;
					flaging++;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if (muki % 2) //�E�����������Ă���
			{
				target_camera.z = pos_z * 100 + 50;
				player_camera.z = pos_z * 100 + 50;
			}
			else
			{
				target_camera.x = pos_x * 100 + 50;
				player_camera.x = pos_x * 100 + 50;
			}
			flaging = 0;
			time = 0;
			state = 0;
		}
		break;

	case 6: //A�{�^����������
		time += options->move_speed;
		if (time < 100)
		{
			switch (muki)
			{
			case 0:
				target_camera.x -= options->move_speed;
				player_camera.x -= options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_x--;
					flaging++;
				}
				break;

			case 1:
				target_camera.z += options->move_speed;
				player_camera.z += options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_z++;
					flaging++;
				}
				break;

			case 2:
				target_camera.x += options->move_speed;
				player_camera.x += options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_x++;
					flaging++;
				}
				break;

			case 3:
				target_camera.z -= options->move_speed;
				player_camera.z -= options->move_speed;
				if (time >= 50 && !flaging)
				{
					pos_z--;
					flaging++;
				}
				break;

			default:
				break;
			}
		}
				else
				{
					if (muki % 2) //�E�����������Ă���
					{
						target_camera.z = pos_z * 100 + 50;
						player_camera.z = pos_z * 100 + 50;
					}
					else
					{
						target_camera.x = pos_x * 100 + 50;
						player_camera.x = pos_x * 100 + 50;
					}
					flaging = 0;
					time = 0;
					state = 0;
				}
			break;
	case 7:
		if (flaging)
		{
			if (!nowchoose && Key_Input::buff_time[KEY_INPUT_Z] == 1)
			{
				Flags::nowscene = 0x8011d;
				flaging = 0;
			}
			else if (nowchoose && Key_Input::buff_time[KEY_INPUT_Z] == 1)
			{
				state = 0;
				flaging = 0;
			}
			else if (Key_Input::buff_time[KEY_INPUT_UP] == 1 || Key_Input::buff_time[KEY_INPUT_DOWN] == 1)
			{
				nowchoose = !nowchoose;
			}
		}
		else
		{
			flaging++;
		}

		break;

	default:
		break;
		
	}
	return 0;
}


int Dungeon::DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd)
//����̍��W�ƉE���̍��W�����
{
	
	VERTEX3D Vertex[4];
	WORD Index[6];
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		Vertex[i].dif = GetColorU8(255, 255, 255, 255);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}
	double t_z1 = pos_z_lu;
	double t_z2 = pos_z_rd;
	if (pos_y_lu == pos_y_rd) //�c�Ɖ��̏��������B�v�l��
	{
		double keep_z = t_z1;
		t_z1 = t_z2;
		t_z2 = keep_z;
	}

	// �Q�|���S�����̒��_�̃f�[�^���Z�b�g
	Vertex[0].pos = VGet(pos_x_lu, pos_y_lu, pos_z_lu); //����̓_
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;

	Vertex[1].pos = VGet(pos_x_lu, pos_y_rd, t_z1); //�����̓_
	Vertex[1].u = 0.0f;
	Vertex[1].v = 1.0f;

	Vertex[2].pos = VGet(pos_x_rd, pos_y_lu, t_z2); //�E��̓_
	Vertex[2].u = 1.0f;
	Vertex[2].v = 0.0f;

	Vertex[3].pos = VGet(pos_x_rd, pos_y_rd, pos_z_rd); //�E���̓_
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;

	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 3;
	Index[4] = 2;
	Index[5] = 1;
	
	return DrawPolygonIndexed3D(Vertex, 4, Index, 2, kabe_handle, FALSE);
}


int Dungeon::DrawMap(unsigned char(*map_data)[10], int x_max, int z_max)
{
	int now_num = 0;
	const int debug = 0;

	int ** map_dis = new int*[z_max];
	for (int i = 0; i<z_max; i++)
	{
		map_dis[i] = new int[x_max];
	}

	int *dis_com;
	dis_com = (int*)malloc(sizeof(int)*z_max*x_max);
	for (int i = 0; i < z_max*x_max; i++)
	{
		dis_com[i] = -1;
	}

	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			map_dis[z][x] = (z - pos_z)*(z - pos_z) + (x - pos_x)*(x - pos_x);
			for (int i = 0; i<z_max*x_max; i++)
			{
				if (dis_com[i] == map_dis[z][x])
				{
					goto nuke;
				}
			}
			dis_com[now_num] = map_dis[z][x];
			now_num++;
		nuke:;
		}
	}


	for (int i = 0; i < z_max*x_max; i++)
	{
		if (dis_com[i] == -1)
		{
			goto dainuke;
		}
		for (int i2 = i; i2 <= z_max*x_max; ++i2)
		{
			if (dis_com[i2] == -1)
			{
				goto mininuke;
			}
			if (dis_com[i]<dis_com[i2])
			{
				int keep = dis_com[i];
				dis_com[i] = dis_com[i2];
				dis_com[i2] = keep;
			}
		}
	mininuke:;
	}
dainuke:;


	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			DrawSquare(x * 100, 0, (z + 1) * 100, (x + 1) * 100, 0, z * 100); //��
			DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 100, z * 100); //�V��
		}
	}


	int x = x_max;
	int slowcheack = 0;
	for (int i = 0; i<(z_max+1)*(x_max+1); i++)
	{
		for (int z = z_max - 1; z >= 0; z--)
		{
			while (x > 0)
			{
				x--;
				if (map_dis[z][x] == dis_com[i])
				{
					slowcheack = 0;
					if (z < pos_z)
					{
						slowcheack += 1;
					}
					if (x < pos_x)
					{
						slowcheack += 2;
					}
					if (z > pos_z)
					{
						slowcheack += 4;
					}
					if (x > pos_x)
					{
						slowcheack += 8;
					}

					for (int now = 0; now < 2; now++)
					{
						if ((map_data[z][x] & 1) && ((!now&&!(slowcheack & 1)) || (now && (slowcheack & 1))))
						{if (z>=z_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
							{
								goto sugusoko1;
							}
							else if (pos_z > z && !(map_data[z + 1][x] & 4)) //����ʍs���l��
							{
							}
							else
							{
							sugusoko1:;
								DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 0, (z + 1) * 100);
							}
						}
						if ((map_data[z][x] & 2) && ((!now&&!(slowcheack & 2)) || (now && (slowcheack & 2))))
						{if (x >= x_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
							{
								goto sugusoko2;
							}
							else if (pos_x > x &&!(map_data[z][x + 1] & 8)) //����ʍs���l��
							{
							}
							else
							{
							sugusoko2:;
								DrawSquare((x + 1) * 100, 100, z * 100, (x + 1) * 100, 0, (z + 1) * 100);
							}
						}
						if ((map_data[z][x] & 4) && ((!now && !(slowcheack & 4)) || (now && (slowcheack & 4))))
						{
							if (!z) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
							{
								goto sugusoko4;
							}
							else if (pos_z < z && !(map_data[z - 1][x] & 1)) //����ʍs���l��
							{
							}
							else
							{
							sugusoko4:;
								DrawSquare(x * 100, 100, z * 100, (x + 1) * 100, 0, z * 100);
							}
						}
						if ((map_data[z][x] & 8) && ((!now&&!(slowcheack & 8)) || (now && (slowcheack & 8))))
						{
							if (!x) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
							{
								goto sugusoko8;
							}
							else if (pos_x < x && !(map_data[z][x - 1] & 2)) //����ʍs���l��
							{
							}
							else
							{
							sugusoko8:;
								DrawSquare(x * 100, 100, (z + 1) * 100, x * 100, 0, z * 100);
							}
						}
					}
				}
			}
			x = x_max;
		}
	}
	


/*for (int z = 0; z < z_max; z++)
{
	for (int x = 0; x < x_max; x++)
	{
		DrawSquare(x * 100, 0, (z + 1) * 100, (x + 1) * 100, 0, z * 100); //��
		DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 100, z * 100); //�V��
	}
}
for (int z = 0; z < z_max; z++)
{
	for (int x = 0; x < x_max; x++)
	{
		if ((map_data[z][x] & 1))
		{
			DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 0, (z + 1) * 100);
		}
		if ((map_data[z][x] & 2))
		{
			DrawSquare((x + 1) * 100, 100, z * 100, (x + 1) * 100, 0, (z + 1) * 100);
		}
		if ((map_data[z][x] & 4))
		{
			DrawSquare(x * 100, 100, z * 100, (x + 1) * 100, 0, z * 100);
		}
		if ((map_data[z][x] & 8))
		{
			DrawSquare(x * 100, 100, (z + 1) * 100, x * 100, 0, z * 100);
		}
	}
}*/
	DrawFormatString(0, 0, GetColor(255, 0, 0), "x:%d,z:%d,%d", pos_x, pos_z, muki);
	if (1) //�f�o�b�O�p�R�[�h
	{
		for (int z = z_max - 1; z >= 0; --z)
		{
			for (int x = x_max - 1; x >= 0; --x)
			{
				//DrawFormatString(20 * (x), 20 + 20 * (z_max + 1 - z), GetColor(255, 0, 0), "%d", map_data[z][x]);
				DrawFormatString(20 * (x), 20 + 20 * (z_max + 1 - z), GetColor(255, 0, 0), "%d", savedata->map_open_flag[floors - 1][z][x]);
			}
		}
		/*for (int i = 0; i < 25; i++)
		{
			DrawFormatString(240, i * 20, GetColor(255, 0, 0), "%d", dis_com[i]);
		}*/
	}

	DrawFormatString(0, 100, GetColor(0, 0, 255), "t_x:%d,t_z:%d,p_x:%d,p_z:%d", (int)target_camera.x,(int)target_camera.z,(int)player_camera.x,(int)player_camera.z);
	/*for (int i = 0; i<x; i++) //�������̉��
	{
		delete[] map_dis[i];
	}
	delete[] map_dis;
	free(dis_com);*/
	return 0;
}


int Dungeon::DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max)
{

	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			DrawSquare(x * 100, 0, (z + 1) * 100, (x + 1) * 100, 0, z * 100); //��
			DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 100, z * 100); //�V��
		}
	}



	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			if ((map_data[z][x] & 1))
			{
				if (z >= z_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko1;
				}
				else if (pos_z > z && !(map_data[z + 1][x] & 4)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko1:;
					DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 0, (z + 1) * 100);
				}
			}
			if ((map_data[z][x] & 2))
			{
				if (x >= x_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko2;
				}
				else if (pos_x > x &&!(map_data[z][x + 1] & 8)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko2:;
					DrawSquare((x + 1) * 100, 100, z * 100, (x + 1) * 100, 0, (z + 1) * 100);
				}
			}
			if ((map_data[z][x] & 4))
			{
				if (!z) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko4;
				}
				else if (pos_z < z && !(map_data[z - 1][x] & 1)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko4:;
					DrawSquare(x * 100, 100, z * 100, (x + 1) * 100, 0, z * 100);
				}
			}
			if ((map_data[z][x] & 8))
			{
				if (!x) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko8;
				}
				else if (pos_x < x && !(map_data[z][x - 1] & 2)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko8:;
					DrawSquare(x * 100, 100, (z + 1) * 100, x * 100, 0, z * 100);
				}
			}
		}
	}

	DrawFormatString(0, 0, GetColor(255, 0, 0), "x:%d,z:%d,%d", pos_x, pos_z, muki);
	if (1) //�f�o�b�O�p�R�[�h
	{
		for (int z = z_max - 1; z >= 0; --z)
		{
			for (int x = x_max - 1; x >= 0; --x)
			{
				DrawFormatString(20 * (x), 20 + 20 * (z_max + 1 - z), GetColor(255, 0, 0), "%d", savedata->map_open_flag[floors - 1][z][x]);
			}
		}
	}

	DrawFormatString(0, 100, GetColor(0, 0, 255), "t_x:%d,t_z:%d,p_x:%d,p_z:%d", (int)target_camera.x, (int)target_camera.z, (int)player_camera.x, (int)player_camera.z);

	return 0;
}


void Dungeon::Return_right()
{
	switch (muki)
	{
	case 0:
		target_camera.x += options->revolve_speed;
		//target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
		player_camera.x -= options->revolve_speed;
		//player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
		target_camera.z -= options->revolve_speed;
		player_camera.z += options->revolve_speed;
		if (time >= 50)
		{
			target_camera.x -= time - 50;
			player_camera.x += time - 50;
			target_camera.z += time - 50;
			player_camera.z -= time - 50;
			muki++;
		}
		break;
	case 1:
		target_camera.x -= options->revolve_speed;
		player_camera.x += options->revolve_speed;
		target_camera.z -= options->revolve_speed;
		player_camera.z += options->revolve_speed;
		if (time >= 50)
		{
			target_camera.x += time - 50;
			player_camera.x -= time - 50;
			target_camera.z += time - 50;
			player_camera.z -= time - 50;
			muki++;
		}
		break;
	case 2:
		target_camera.x -= options->revolve_speed;
		player_camera.x += options->revolve_speed;
		target_camera.z += options->revolve_speed;
		player_camera.z -= options->revolve_speed;
		if (time >= 50)
		{
			target_camera.x += time - 50;
			player_camera.x -= time - 50;
			target_camera.z -= time - 50;
			player_camera.z += time - 50;
			muki++;
		}
		break;
	case 3:
		target_camera.x += options->revolve_speed;
		player_camera.x -= options->revolve_speed;
		target_camera.z += options->revolve_speed;
		player_camera.z -= options->revolve_speed;
		if (time >= 50)
		{
			target_camera.x -= time - 50;
			player_camera.x += time - 50;
			target_camera.z -= time - 50;
			player_camera.z += time - 50;
			muki -= muki;
		}
		break;
	default:
		break;
	}
}


void Dungeon::LoadDungeon() //�s���\��̊K�w�̏���ǂݍ��ނ�������
{
	switch (floors)
	{
	case 1:
		fp = fopen("./dungeon/map1F.cns", "r");
		break;
	case 2:
		fp = fopen("./dungeon/map2F.cns", "r");
		break;
	case 3:
		fp = fopen("./dungeon/map3F.cns", "r");
		break;
	}

	//GraphFilter(kabe_handle, DX_GRAPH_FILTER_GAUSS, 32, 55600);

	if (fp == NULL) //�G���[�`�F�b�N
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}

	fscanf(fp, "%d,%d", &x_max, &z_max);
	for (int i = 0; i < z_max; i++)
	{
		for (int i2 = 0; i2 < x_max; i2++)
		{
			fscanf(fp, "%d,", &map_data[i][i2]);
			//fscanf(fp, "%c");
		}
	}
	fscanf(fp, "%d,%d", &start_x, &start_z);
	fscanf(fp, "%d", &feel_flag);
	fscanf(fp, "%s", kabe_name);
	fscanf(fp, "%d,%d,%d", &fog_r, &fog_g, &fog_b);
	fscanf(fp, "%f,%f", &fog_start, &fog_goal);

	SetTransColor(255, 255, 255); //���𓧉ߐF��
	kabe_handle = LoadGraph(kabe_name);
	SetTransColor(0, 0, 0); //�ꉞ�߂�


	if (kabe_handle == -1) //�G���[�`�F�b�N
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}

	if (feel_flag)
	{
		int keep = 0;
		for (int i = 0; i < z_max / 2; i++)
		{
			for (int i2 = 0; i2 < x_max; i2++)
			{
				keep = map_data[i][i2];
				map_data[i][i2] = map_data[z_max - i - 1][i2];
				map_data[z_max - i - 1][i2] = keep;
			}
		}
	}

	pos_x = start_x;
	pos_z = start_z;
	state = 0;
	time = 0;
	muki = 0;
	nowchoose = 0;
	//�J�����̏�����
	target_camera = VGet(pos_x * 100 + 50, 50, pos_z * 100 + 100);
	player_camera = VGet(pos_x * 100 + 50, 50, pos_z * 100);

	//�t�H�O�̐ݒ�
	SetFogEnable(TRUE);
	SetFogColor(fog_r, fog_g, fog_b);
	SetFogStartEnd(fog_start, fog_goal);
}


void Dungeon::DrawMiniMap()
{
	//���n
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 72); //����
	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			DrawBox(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white, FALSE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 212); //����
	DrawBox(640 - (x_max + 1) * 20, 279, 640 - 20, 279 - z_max * 20, black, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�


		for (int z = 0; z < z_max; z++)
		{
			for (int x = 0; x < x_max; x++)
			{
				if (savedata->map_open_flag[floors - 1][z][x])
				{
					if (map_data[z][x] & 1)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - (z + 1) * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white);
						if (z < z_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z + 1][x] & 4) && savedata->map_open_flag[floors - 1][z + 1][x]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 + 3, 280 - (z + 1) * 20 - 10, "��", white);
							}
						}
					}
					if (map_data[z][x] & 2)
					{
						DrawLine(640 - (x_max - x) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white);
						if (x < x_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z][x + 1] & 8) && savedata->map_open_flag[floors - 1][z][x + 1]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x) * 20 - 10, 280 - (z + 1) * 20 + 3, "��", white);
							}
						}
					}
					if (map_data[z][x] & 4)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - z * 20, white);
						if (z > 0) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z - 1][x] & 1) && savedata->map_open_flag[floors - 1][z - 1][x]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 + 3, 280 - z * 20 - 10, "��", white);
							}
						}
					}
					if (map_data[z][x] & 8)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x + 1) * 20, 280 - (z + 1) * 20, white);
						if (x > 0) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z][x - 1] & 2) && savedata->map_open_flag[floors - 1][z][x - 1]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 - 10, 280 - (z + 1) * 20 + 3, "��", white);
							}
						}
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 72); //����
					DrawBox(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, blue, TRUE); //������
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
				}
			}
		}

	DrawRotaGraph(640 - (x_max - pos_x) * 20 - 10, 280 - (pos_z + 1) * 20 + 10, 20.0 / 128.0, muki * PI / 2.0, yajirushi_h,TRUE);
}