#pragma once

struct Float2
{
	float x;
	float y;


	Float2()
		: x(0), y(0) {}


	Float2(float x, float y)
		: x(x), y(y) {}

	Float2(int x, int y)
		: x(x), y(y) {}

	inline void operator=(Float2 input)
	{
		x = input.x;
		y = input.y;
	}

	inline void operator+(Float2 input)
	{
		x += input.x;
		y += input.y;
	}

	inline void operator-(Float2 input)
	{
		x -= input.x;
		y -= input.y;
	}

	inline bool operator==(Float2 input)
	{
		return (x == input.x && y == input.y);
	}

};