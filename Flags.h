#pragma once
class Flags //�t���O���܂Ƃ߂�N���X?
{
public:
	Flags();
	~Flags();
	static int talkflag; //���݉�b���ł���t���O
	static int menuflag; //���j���[��ʂł���`�B�ł����݂̓L�����v
	static int nowscene; //0xf1e1d�Ȃ�_���W�����A0xba771e�Ȃ�퓬�A0x8011d�Ȃ�M���h
	static int guild_now; //�����s���Ă���G���g�����X�̃��j���[
	static int menu_window_size_x; //�M���h�̃��j���[���̉E��x���W
	static int menu_window_size_y; //�M���h�̃��j���[���̉E��y���W
	static int character_show_flag; //�L�����N�^�[�̏������Ă���t���O
	static int battleflag; //���ݐ퓬���ł���t���O
};

