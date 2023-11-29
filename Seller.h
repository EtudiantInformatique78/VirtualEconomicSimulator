#pragma once
#include <vector>

class Subscriber
{
public:
	virtual void update() = 0;
};

class TreeSubscriber : public Subscriber
{
public:
	void update() override
	{
	
	}
};




class Publisher
{
protected:
	std::vector<Subscriber> vectSubscriber;

public:
	void subscribe(Subscriber s)
	{
		vectSubscriber.push_back(s);
	}
	void unsubscribe(Subscriber s)
	{
		std::vector<Subscriber>::iterator position = std::find(vectSubscriber.begin(), vectSubscriber.end(), s);
		if (position != vectSubscriber.end())
		{
			vectSubscriber.erase(position);
		}
	}

	void notifySubscriber()
	{
		std::vector<Subscriber>::iterator it;
		for(it = vectSubscriber.begin(); it != vectSubscriber.end() ; ++it)
		{
			it->update();
		}
	}

};