#include "Result.h"
#include "SelectStage.h"
#include "Dxlib.h"

Result::Result()
{
}

Result::~Result()
{
}

// 描画以外の更新を実装
AbstractScene* Result::Update()
{
	return this;
}

//描画に関することを実装
void Result::Draw() const
{
	DrawFormatString(0, 0, 0xffffff, "リザルト画面");
}