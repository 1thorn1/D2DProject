// D2DProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "D2DProject.h"
#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DemoApp app;

    app.Initialize(hInstance);
    app.Run();
    app.Uninitialize();
}

// git을 commit 하기 위한 내용을 그냥 첨부해보았슴니다요리
