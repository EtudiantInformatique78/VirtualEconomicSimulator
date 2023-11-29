#pragma once
#include <vector>
#include <iostream>

class Subscriber
{
public:
	virtual void update() = 0;
};

class Publisher
{
protected:
	std::vector<std::shared_ptr<Subscriber>> vect;
	//std::vector<Subscriber> vectSubscriber;

public:
	virtual void subscribe(std::shared_ptr<Subscriber> s) = 0;
	virtual void unsubscribe(std::shared_ptr<Subscriber> s) = 0;
	virtual void notifySubscriber() = 0;
};




class TreeSubscriber : public Subscriber
{
public:
	void update() override
	{
		std::cout << "I am getting a tree ! " << std::endl;
	}
};

class TreePublisher : public Publisher
{
public:
	void subscribe(std::shared_ptr<Subscriber> s) override
	{
		std::shared_ptr<TreeSubscriber> t =  std::dynamic_pointer_cast<TreeSubscriber>(s);
		vect.push_back(t);
	}
	void unsubscribe(std::shared_ptr<Subscriber> s)  override
	{
		std::vector<std::shared_ptr<Subscriber>>::iterator position = std::find(vect.begin(), vect.end(), s);
		if (position != vect.end())
		{
			vect.erase(position);
		}
	}

	void notifySubscriber() override
	{
		std::vector<std::shared_ptr<Subscriber>>::iterator it;
		for (it = vect.begin(); it != vect.end(); ++it)
		{
			it->get()->update();
		}
	}
};

class IronSubscriber : public Subscriber
{
public:
	void update() override
	{
		std::cout << "I am getting an Iron ore ! " << std::endl;
	}
};

class IronPublisher : public Publisher
{
public:
	void subscribe(std::shared_ptr<Subscriber> s) override
	{
		std::shared_ptr<IronSubscriber> t = std::dynamic_pointer_cast<IronSubscriber>(s);
		vect.push_back(t);
	}
	void unsubscribe(std::shared_ptr<Subscriber> s)  override
	{
		std::vector<std::shared_ptr<Subscriber>>::iterator position = std::find(vect.begin(), vect.end(), s);
		if (position != vect.end())
		{
			vect.erase(position);
		}
	}

	void notifySubscriber() override
	{
		std::vector<std::shared_ptr<Subscriber>>::iterator it;
		for (it = vect.begin(); it != vect.end(); ++it)
		{
			it->get()->update();
		}
	}
};