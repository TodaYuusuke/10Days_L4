#include <Adapter.h>
#include "class/scene/Title.h"
#include "class/scene/TestScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	LWP::System::Run<Title>(L"4008_円で囲まれた者が奴に石を投げなさい");
	return 0;
}