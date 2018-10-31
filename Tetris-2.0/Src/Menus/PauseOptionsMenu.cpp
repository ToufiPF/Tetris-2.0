#include "PauseOptionsMenu.hpp"



PauseOptionsMenu::PauseOptionsMenu()
	: OptionsMenu() 
{
}
PauseOptionsMenu::~PauseOptionsMenu() {
}

void PauseOptionsMenu::setSelection(int sel) {
	mSel = sel;

	if (mSel < 0)
		mSel = 0;
	else if (mSel >= PauseOptionSelection::PauseOptionCount)
		mSel = PauseOptionSelection::PauseOptionCount - 1;

	switch (mSel) {
	case PauseOptionSelection::BGM_VOL:
		mTriangleSel.setPosition(mBgmTxt.getGlobalBounds().left - 20,
			mBgmTxt.getGlobalBounds().top + (mBgmTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	case  PauseOptionSelection::SFX_VOL:
		mTriangleSel.setPosition(mSfxTxt.getGlobalBounds().left - 20,
			mSfxTxt.getGlobalBounds().top + (mSfxTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	case PauseOptionSelection::APPLY:
		mTriangleSel.setPosition(mSaveOptTxt.getGlobalBounds().left - 20,
			mSaveOptTxt.getGlobalBounds().top + (mSaveOptTxt.getGlobalBounds().height - mTriangleSel.getGlobalBounds().height) / 2);
		break;

	default:
		break;
	}

}

void PauseOptionsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(mMenuFrame, states);

	target.draw(mBgmTxt, states);
	target.draw(mBgmVolumeBar, states);
	target.draw(mSfxTxt, states);
	target.draw(mSfxVolumeBar, states);
	target.draw(mSaveOptTxt, states);

	target.draw(mTriangleSel, states);
}

