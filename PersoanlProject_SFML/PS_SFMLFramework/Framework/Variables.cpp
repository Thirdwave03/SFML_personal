#include "stdafx.h"
#include "Variables.h"

bool Variables::isDrawHitBox = false;
Languages Variables::currentLang = Languages::English;

void Variables::SetFont(sf::Text& text)
{
	switch ((int)Variables::currentLang)
	{
	case 0:
		text.setFont(FONT_MGR.Get("fonts/malgun.ttf"));
		break;
	case 1:
		text.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
		break;
	case 2:
		text.setFont(FONT_MGR.Get("fonts/NotoSansJP-VariableFont_wght.ttf"));
		break;
	case 3:
		text.setFont(FONT_MGR.Get("fonts/NotoSansSC-VariableFont_wght.ttf"));
		break;
	default:
		text.setFont(FONT_MGR.Get("fonts/malgun.ttf"));
		break;
	}
}
