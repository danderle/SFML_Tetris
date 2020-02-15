#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window)
{
	bool isClicked = false;
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y,
			sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		if (rect.contains(GetMousePosition(window)))
		{
			isClicked = true;
		}
	}
	return isClicked;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
