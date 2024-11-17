#include "stdafx.h"
#include "ViewMgr.h"

void ViewMgr::Init()
{
	Reset();
}

void ViewMgr::Update(float dt)
{

}

void ViewMgr::Reset()
{
	auto wSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(wSize);
	uiView.setSize(wSize);
	editorView.setSize(wSize * 2.f);
	worldView.setCenter(0.f,0.f);
	uiView.setCenter(wSize / 2.f);
	editorView.setCenter(wSize);

	ResetUiViewCheckRect();
	SetViewType(ViewTypes::WorldView);
}

void ViewMgr::SetViewType(ViewTypes viewType)
{
	currentViewType = viewType;
	switch (currentViewType)
	{
	case ViewTypes::WorldView:
		currentView = worldView;
		break;
	case ViewTypes::UiView:
		currentView = uiView;
		break;
	case ViewTypes::EditorView:
		currentView = editorView;
		break;
	default:
		currentView = worldView;
		break;
	}

	FRAMEWORK.GetWindow().setView(currentView);
}

void ViewMgr::ResetUiViewCheckRect()
{
	auto uvSize = uiView.getSize();
	auto uvCenterPos = uiView.getCenter();
	uiViewCheckRect.setSize(uvSize);
	uiViewCheckRect.setOutlineColor(sf::Color::Magenta);
	uiViewCheckRect.setOutlineThickness(30.f);
	Utils::SetOrigin(uiViewCheckRect, Origins::MC);
	uiViewCheckRect.setPosition(uvCenterPos);
}
