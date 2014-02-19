#pragma once
class Events //イベントを処理するクラス。多分singleton
{
public:   // 唯一のアクセス経路
	static Events* GetInstance()
	{
		static Events instance;  // 唯一のインスタンス
		return &instance;
	}
	// あとは、このクラス自身が必要なメンバを定義する
	int ev_act(int number); //与えられた番号に対するイベントの呼び出し
	void in_battle(); //戦闘シーンに移動

private:
	// 生成やコピーを禁止する
	Events(){}
	Events(const Events& rhs);
	Events& operator=(const Events& rhs);
	~Events();
};

