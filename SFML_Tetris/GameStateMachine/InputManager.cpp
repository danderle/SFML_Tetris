#include "InputManager.h"

bool InputManager::IsRectClicked(sf::Rect<float> rect, sf::Mouse::Button buttonPressed, sf::RenderWindow& window)
{
	bool isClicked = false;
	if (sf::Mouse::isButtonPressed(buttonPressed))
	{
		auto msePosition = GetMousePosition(window);
		if (rect.contains({ (float)msePosition.x, (float)msePosition.y }))
		{
			isClicked = true;
		}
	}
	return isClicked;
}

bool InputManager::IsHovering(sf::Rect<float> rect, sf::RenderWindow& window)
{
	auto msePosition = GetMousePosition(window);
	return rect.contains({ (float)msePosition.x, (float)msePosition.y});
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

bool InputManager::KeyHit(sf::Keyboard::Key key) const
{
	return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::KeyReleased(sf::Event event, sf::Keyboard::Key key) const
{
	return event.KeyReleased && event.key.code == key;
}
