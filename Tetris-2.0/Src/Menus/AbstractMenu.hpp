#ifndef ABSTRACTMENU_HPP
#define ABSTRACTMENU_HPP

#include <SFML/Graphics.hpp>
#include "../main.hpp"

class AbstractMenu : public sf::Drawable, public sf::Transformable
{
public:

public:
	AbstractMenu();
	~AbstractMenu();

	virtual void setSelection(int sel) { mSel = sel; };
	virtual int getSelection() const { return mSel; };

	virtual void setMenuSize(sf::Vector2f const & size) { mMenuFrame.setSize(size); };
	virtual sf::Vector2f getMenuSize() const { return mMenuFrame.getSize(); };
	virtual void setFont(sf::Font const& f) = 0;

protected:
	int mSel;
	sf::CircleShape mTriangleSel;
	sf::RectangleShape mMenuFrame;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif
