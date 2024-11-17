#pragma once

enum class ViewTypes
{
	WorldView,
	UiView,
	EditorView,
};


enum class Languages
{
	Korean,
	English,
	Japanese,
	Chinese,
	Count,
};

enum class SortingLayers
{
	Background,
	Tiles,
	Foreground,
	Default,
	InfoBox,
	UI,
};

enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
	Count,
};

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};