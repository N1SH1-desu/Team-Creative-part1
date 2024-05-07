#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"


void SceneGame::init()
{
	p = new MusicData("music.txt");
	int a;
}

void SceneGame::update()
{
	if (!is)
	{
		timer.Start();
		is = true;
	}

	timer.Tick();

	GameLib::debug::setString("currentTime: %lf", timer.DeltaTime());
	GameLib::debug::setString("option: %s", p->getOptionStream().str().c_str());
	GameLib::debug::setString("data: %s", p->getDataStream().str().c_str());


	GameLib::debug::setString("Title : %s", p->getOptions().song_name.c_str());
	GameLib::debug::setString("Wave : %s", p->getOptions().song_path.c_str());
	GameLib::debug::setString("BPM : %d", p->getOptions().bpm);
	GameLib::debug::setString("OFFSET : %f", p->getOptions().offset);
	GameLib::debug::setString("START : %d", p->getOptions().isStart);

	GameLib::debug::setString("note[0][0] : %lf", p->getNoteManager().getNoteTiming(0, 2));

	// シーン切り替えチェック
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG1) { setScene(SCENE::OVER); }
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2) { setScene(SCENE::CLEAR); }
}

void SceneGame::draw()
{
	// 画面をクリア
	GameLib::clear(0, 0, 0);

	// 文字列描画
	GameLib::font::textOut(4, "[Z]GAME OVER", { 0, 660 }, { 2, 2 },
		{ 1, 0, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);

	GameLib::font::textOut(4, "[X]GAME CLEAR", { 0, 700 }, { 2, 2 },
		{ 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);
}
