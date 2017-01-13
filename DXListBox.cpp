#include "DXListBox.h"
#include"Colors.h"


DXListBox::DXListBox() :
	m_pos_x(0),
	m_pos_y(0),
	m_size_x(0),
	m_size_y(0),
	m_bExplanation(false),
	m_choose_now(0)
{
}


DXListBox::~DXListBox()
{
}


void DXListBox::Draw()
{
	m_num_item = (int)m_nameList.size();
	int size_y = m_size_y <= m_num_item * strHigh ? m_size_y : m_num_item * strHigh; //������
	int pos_rx = m_pos_x + m_size_x;
	int pos_ry = m_pos_y + size_y;

	//�܂��͎��͂�`��
	DrawBox(pos_rx, m_pos_y, pos_rx + 2, pos_ry + 1, Colors::yellow, TRUE); //���̎���E
	DrawBox(m_pos_x, m_pos_y, m_pos_x + 2, pos_ry + 1, Colors::yellow, TRUE); //���̎��荶
	DrawBox(m_pos_x, m_pos_y - 2, pos_rx + 2, m_pos_y, Colors::yellow, TRUE); //���̎����
	DrawBox(m_pos_x, pos_ry + 1, pos_rx + 2, pos_ry + 3, Colors::yellow, TRUE); //���̎��艺

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
	DrawBox(m_pos_x + 1, m_pos_y + 1, pos_rx - 1, pos_ry + 1, Colors::black, TRUE); //��
	if (m_bExplanation)
	{
		DrawBox(0, 0, 640, strHigh, Colors::blue, TRUE); //������
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

	DrawBox(m_pos_x + 2, m_pos_y + 1 + m_choose_now * strHigh, pos_rx - 1, m_pos_y + (m_choose_now + 1) * strHigh, Colors::yellow, TRUE); //�I�𒆂̂�����
	if (m_bExplanation)
	{
		DrawFormatString(22, 2, Colors::white, "%s", m_explanationList[m_choose_now].c_str(), TRUE); //�������悤
	}
	for (int i = 0; i < m_num_item; i++)
	{
		DrawFormatString(m_pos_x + 3, m_pos_y + i * strHigh + 2, (m_choose_now == i ? Colors::black : Colors::white), " %s", m_nameList[i].c_str()); //�I�΂ꂽ�̂́A���ł���
	}

}


void DXListBox::AddNameList(string str)
{
	m_nameList.push_back(str);
}


void DXListBox::AddExplanationList(string str)
{
	m_explanationList.push_back(str);
}


void DXListBox::SetExplanationFlag(bool flag)
{
	m_bExplanation = flag;
}



void DXListBox::SetPos(int x, int y, int sizex, int sizey)
{
	m_pos_x = x;
	m_pos_y = y;
	m_size_x = sizex;
	m_size_y = sizey;
}


void DXListBox::SetChoose(int choose)
{
	m_choose_now = choose;
}


void DXListBox::DownChoose()
{
	m_choose_now = (m_choose_now < m_nameList.size() - 1 ? m_choose_now + 1 : 0);

	if (m_choose_now >= m_nameList.size())
	{
		m_choose_now = m_nameList.size() ? m_nameList.size() - 1 : 0;
	}
}


void DXListBox::UpChoose()
{
	m_choose_now = (m_choose_now ? m_choose_now - 1 : m_nameList.size() - 1); //���[�v�ł���悤��

	if (m_choose_now < 0)
	{
		m_choose_now = 0;
	}
}


