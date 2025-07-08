#pragma once

class EventManager : public Singleton<EventManager>
{
	friend class Singleton;

private:
	EventManager();
	~EventManager();

public:
	int AddEvent(const string& eventName, function<void(void*)> event)
	{
		eventWithParams[eventName].push_back(event);
		return eventWithParams[eventName].size()-1;
	}

	void ExcuteEvent(const string& eventName, void* param)
	{
		if (eventWithParams.count(eventName) > 0)
		{
			for (function<void(void*)> event : eventWithParams[eventName])
			{
				event(param);
			}
		}
	}
	void RemoveEvent(const string& eventName, const int& key)
	{
		eventWithParams[eventName].erase(eventWithParams[eventName].begin() + key);
	}

private:
	//vector<function<void()>> events;
	unordered_map<string, vector<function<void(void*)>>> eventWithParams;
};