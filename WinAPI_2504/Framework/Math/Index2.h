#pragma once
struct Index2 
{
	int y; // ROW
	int x; //COL
	Index2():y(0),x(0)
	{
	}
	Index2(int y, int x) : y(y), x(x)
	{
	}

	Index2 operator+(const Index2& other) const
	{
		return Index2(y + other.y,  x+ other.x);
	}
	Index2 operator-(const Index2& other) const
	{
		return Index2(y - other.y,  x- other.x);
	}
	Index2 operator*(const Index2& other) const
	{
		return Index2(y * other.y, x * other.x);
	}
	Index2 operator/(const Index2& other) const
	{
		return Index2(y / other.y, x / other.x);
	}

	Index2 operator*(const int& scala) const
	{
		return Index2(y*scala, x * scala);
	}
	bool operator==(const Index2& other)const
	{
		if (y != other.y)
			return false;
		if (x != other.x)
			return false;
	
		return true;
	}
	bool operator!=(const Index2& other)const
	{
		if (y != other.y)
			return true;
		if (x != other.x)
			return true;
	
		return false;
	}
	void operator+=(const Index2& other)
	{
		y += other.y;
		x += other.x;
	}
	void operator-=(const Index2& other)
	{
		y -= other.y;
		x -= other.x;
	}
	void operator*=(const Index2& other)
	{
		y *= other.y;
		x *= other.x;
	}
	void operator/=(const Index2& other)
	{
		y /= other.y;
		x /= other.x;
	}
	void operator*=(const int& scala)
	{
		y *= scala;
		x *= scala;
	}


	static const Index2 Zero() { return Index2(0, 0); }
	static const Index2 One() { return Index2(1, 1); }

	static const Index2 Right() { return Index2(0, 1); }
	static const Index2 Left() { return Index2(0, -1); }
	static const Index2 Down() { return Index2(-1, 0); }
	static const Index2 Up() { return Index2(1, 0); }

};