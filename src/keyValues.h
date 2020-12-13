#pragma once
#include <string>
#include <vector>

class dict
{
public:
	std::string key;
	float value;

	dict(std::string _key, float _value) { key = _key, value = _value; }
};

class KeyValue
{
	std::vector<dict> data;

public:
	float get(std::string k)
	{
		for (auto& d : data)
		{
			if (d.key == k)
				return d.value;
		}
		return -999;
	}

	bool del(std::string k)
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].key == k)
			{
				std::vector<dict>::const_iterator iter = data.begin();
				data.erase(iter + i);
				return true;
			}
		}
		return false;
	}

	bool set(std::string _key, float _value)
	{
		dict _d(_key, _value);

		// ������ �����Ͱ� ���� ��� �����͸� ���� �߰���
		if (get(_d.key) == -999)
		{
			data.push_back(_d);
			return true;
		}

		// �̹� �����Ͱ� ���� ��� ���� �����͸� ������
		for (auto& d : data)
		{
			if (d.key == _d.key)
			{
				d.value = _d.value;
				return true;
			}
		}
		return false;
	}

	void clear()
	{
		data.clear();
		set("Red", 0);
		set("Blue", 0);
		set("Green", 0);

		set("chrSpeed", 0.05);

		set("chrHpUpdateInterval", 1000);
	}
};