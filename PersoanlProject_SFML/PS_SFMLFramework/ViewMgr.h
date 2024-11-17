#pragma once
class ViewMgr : public Singleton<ViewMgr>
{
	friend Singleton<ViewMgr>;
private:
	ViewMgr() = default;
	~ViewMgr() = default;
	ViewMgr(const ViewMgr& other) = delete;
	ViewMgr& operator=(const ViewMgr& other) = delete;

protected:
	sf::View worldView;
	sf::View uiView;
	sf::View editorView;

	sf::View currentView;

	ViewTypes currentViewType = ViewTypes::WorldView;

	// for UiView test only
	sf::RectangleShape uiViewCheckRect;
	
public:
	void Init();
	void Update(float dt);
	void Reset();

	sf::View& GetWorldView() { return worldView; }
	sf::View& GetUiView() { return uiView; }
	sf::View& GetEditorView() { return editorView; }
	sf::View& GetCurrentView() { return currentView; }
	
	
	void SetViewType(ViewTypes viewType);

	// for UiView test only
	void ResetUiViewCheckRect();
	sf::RectangleShape& GetUiVewCheckRect() { return uiViewCheckRect; }
};

#define VIEW_MGR (Singleton<ViewMgr>::Instance())
