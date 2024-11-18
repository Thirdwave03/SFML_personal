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

	sf::Vector2f viewPos = { 0.f,0.f };
	sf::Vector2f viewDirection;
	float viewMoveSpeed = 500.f;
	sf::Vector2f viewSize;
	sf::FloatRect viewBoundary;
	float worldCoordFloat;

	sf::Vector2f mPosWorld;
	sf::Vector2i mPosScreen;
	sf::Vector2i mPosIso;

	sf::View currentView;

	ViewTypes currentViewType = ViewTypes::WorldView;

	// for UiView test only
	sf::RectangleShape viewCheckRect;
	
public:
	void Init();
	void Update(float dt);
	void Reset();
	void Draw(sf::RenderWindow& window);

	sf::View& GetWorldView() { return worldView; }
	sf::View& GetUiView() { return uiView; }
	sf::View& GetEditorView() { return editorView; }
	sf::View& GetCurrentView() { return currentView; }
	
	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos);

	sf::Vector2i WorldToIso(sf::Vector2f tileSize, sf::Vector2f tileScale);
	sf::Vector2f IsoToWorld(sf::Vector2i isoMouseCoord);

	sf::Vector2f GetWorldMousePos() { return mPosWorld; }
	sf::Vector2i GetScreenMousePos() { return mPosScreen; }
	sf::Vector2i GetIsoMousePos() { return mPosIso; }
	float GetWorldMousePosFloat() {	return worldCoordFloat;	}

	void SetScreenMousePos(sf::Vector2i mPosScreen);

	void SetViewType(ViewTypes viewType);

	void SetViewBoundary(sf::FloatRect viewBound, sf::Vector2f isoTileSize, sf::Vector2f isoScale);

	// for UiView test only
	void ResetViewCheckRect();
	sf::RectangleShape& GetViewCheckRect() { return viewCheckRect; }
};

#define VIEW_MGR (Singleton<ViewMgr>::Instance())
