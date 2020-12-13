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

		// 기존에 데이터가 없을 경우 데이터를 새로 추가함
		if (get(_d.key) == -999)
		{
			data.push_back(_d);
			return true;
		}

		// 이미 데이터가 있을 경우 기존 데이터를 수정함
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