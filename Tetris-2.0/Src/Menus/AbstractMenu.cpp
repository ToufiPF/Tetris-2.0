#include "AbstractMenu.hpp"

AbstractMenu::AbstractMenu()
	: sf::Drawable(), sf::Transformable(), mTriangleSel(20, 3)
{
	mSel = 0;
	mTriangleSel.setFillColor(sf::Color(200, 200, 200));
	mTriangleSel.setRotation(90.0f);

	mMenuFrame.setOutlineThickness(-10.0f);
	mMenuFrame.setOutlineColor(sf::Color(200, 200, 200, 150));
	mMenuFrame.setFillColor(sf::Color(40, 40, 40, 200));
}
AbstractMenu::~AbstractMenu() {
}