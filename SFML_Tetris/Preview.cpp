#include "Preview.h"


Preview::Preview(const TextBox& textbox)
	:
	textBox(textbox)
{
}

void Preview::SetNext(const Tetrimino& tetrimino)
{
	shapes.clear();
	rows = tetrimino.GetHeight() + 1;
	columns = tetrimino.GetWidth() + 1;
	width = columns * dimensions;
	height = rows * dimensions;
	sf::Color color = tetrimino.GetColor();
	auto tetri = tetrimino.GetPosition();
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			sf::RectangleShape shape({ (float)dimensions, (float)dimensions });
			if (tetriCol)
			{
				shape.setFillColor(color);
				shape.setOutlineThickness(outLineThick);
				shape.setOutlineColor(BLACK);
			}
			else
			{
				shape.setFillColor(BLACK);
			}
			shapes.push_back(shape);
		}
	}
	Center();
}

void Preview::Center()
{
	auto pos = textBox.GetPosition();
	pos.x += (textBox.GetRect().width - width) / 2;
	pos.y += (textBox.GetRect().height - height) / 2;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			int index = columns * row + col;
			shapes[index].setPosition(pos.x + (dimensions * col), pos.y + (dimensions * row));
		}
	}
}

void Preview::Draw(sf::RenderWindow& wnd)
{
	for (auto shape : shapes)
	{
		wnd.draw(shape);
	}
}
