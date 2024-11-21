#pragma once


enum class TowerTypes
{
	None = -1,
	ElectricRocquet,
	SprayF,
	SprayR,
	MosquitoRepellent,
};

enum class Stages
{
	None = -1,
	Default,
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
};

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

enum class Origin5SQ
{
	o00, o10, o20, o30, o40,
	o01, o11, o21, o31, o41,
	o02, o12, o22, o32, o42,
	o03, o13, o23, o33, o43,
	o04, o14, o24, o34, o44,
};

enum class Sides
{
	Left,
	Right,
	None,
};