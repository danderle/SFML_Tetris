#pragma once
#include "DEFINITIONS.h"
#include "Tetrimino.h"
#include "TextBox.h"

class Preview
{
public:
	Preview() = delete;
	Preview(const TextBox& textbox);
	void SetNext(const Tetrimino& tetrimino);
	void Center();
	void Draw(sf::RenderWindow& wnd);

private:
	std::vector<sf::RectangleShape> shapes;
	const TextBox& textBox;
	int rows = 0;
	int columns = 0;
	int width = 0;
	int height = 0;
	static constexpr int outLineThick = -1;
	static constexpr int dimensions = 36;
};

