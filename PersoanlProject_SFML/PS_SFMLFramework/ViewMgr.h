#pragma once

class IsometricTileMap;

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
	float worldCoordFloatBL;
	float worldCoordFloatBR;
	float devidedBR;
	float devidedBL;

	int xIndex = 0;
	int yIndex = 0;

	sf::Vector2f mPosWorld;
	sf::Vector2f mPosWorldNonModified;
	sf::Vector2i mPosScreen;
	sf::Vector2i mPosIso;
	sf::Vector2f mPosIsoToWorld;

	sf::View currentView;

	ViewTypes currentViewType = ViewTypes::WorldView;
	
	IsometricTileMap* isoTile;

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
	sf::Vector2f ScreenToWorldNonModification(sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos);
	
	sf::Vector2i WorldToIso(sf::Vector2f tileSize = {64.f, 32.f}, sf::Vector2f tileScale = {3.f,3.f});
	sf::Vector2f IsoToWorld(sf::Vector2i mPosIso, sf::Vector2f tileSize = {64.f,32.f}, sf::Vector2f tileScale = {3.f,3.f});
	sf::Vector2f NonModifiedIsoWorldPos(sf::Vector2i isoCoord);

	sf::Vector2f IsoToWorld();
	sf::Vector2f IsoToWorldTest();

	sf::Vector2f GetWorldMousePos() { return mPosWorld; }
	sf::Vector2f GetWorldMousePosNonModified() { return mPosWorldNonModified; }
	sf::Vector2i GetScreenMousePos() { return mPosScreen; }
	sf::Vector2i GetIsoMousePos();
	float GetWorldMousePosFloatBL() { return worldCoordFloatBL; }
	float GetWorldMousePosFloatBR() { return worldCoordFloatBR; }
	float GetDevidedBR() { return devidedBR; }
	float GetDevidedBL() { return devidedBL; }
	
	int GetXindex() { return xIndex; }
	int GetYindex() { return yIndex; }

	bool Build();

	sf::Vector2f GetMouseOnIsoTilePos() { return mPosIsoToWorld; }

	IsometricTileMap& GetIsoTileMap() { return *isoTile; }
	

	void SetScreenMousePos(sf::Vector2i mPosScreen);

	void SetViewType(ViewTypes viewType);
	void AllignIsoTile(IsometricTileMap& isoTile);

	void SetViewBoundary(sf::FloatRect viewBound, sf::Vector2f isoTileSize, sf::Vector2f isoScale);

};

#define VIEW_MGR (Singleton<ViewMgr>::Instance())
