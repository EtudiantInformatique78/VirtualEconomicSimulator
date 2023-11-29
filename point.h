#pragma once

enum class FIELD_TYPE
{
	WATER,
	OBSTACLE,
	TEMPEST,
	REEF
};

class Point
{
public:
	Point(int _x, int _y, FIELD_TYPE _type = FIELD_TYPE::WATER);
	~Point();
	const int& getX() const;
	const int& getY() const;
	const FIELD_TYPE& getFieldType() const;
	void setX(int _x);
	void setY(int _y);
	void setFieldType(FIELD_TYPE _fieldType);
private:
	int x;
	int y;
	FIELD_TYPE fieldType;
};
