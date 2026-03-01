#include <windows.h>
#include "Presenter.hpp"
#include "TetrisInterface.hpp"

constexpr int CELL_SIZE = 20;
constexpr int GRID_WIDTH  = MATRIX_WIDTH  * CELL_SIZE;
constexpr int GRID_HEIGHT = MATRIX_HEIGHT * CELL_SIZE;

Presenter presenter;
TetrisView tetris_view = presenter.make_view();

static HBRUSH hBrushes[9];

void draw_grid(HDC hdc)
{
    RECT rc;
    for(index_type y = 0; y < MATRIX_HEIGHT; ++y){
        for(index_type x = 0; x < MATRIX_WIDTH; ++x){
            Cell c = tetris_view(y, x);
            int idx = static_cast<int>(c);
            rc.left   = x * CELL_SIZE;
            rc.top    = y * CELL_SIZE;
            rc.right  = rc.left + CELL_SIZE;
            rc.bottom = rc.top + CELL_SIZE;
            FillRect(hdc, &rc, hBrushes[idx]);
            FrameRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        hBrushes[0] = CreateSolidBrush(RGB(255,255,255)); // EMPTY white
        hBrushes[1] = CreateSolidBrush(RGB(0,255,255));   // I cyan
        hBrushes[2] = CreateSolidBrush(RGB(255,255,0));   // O yellow
        hBrushes[3] = CreateSolidBrush(RGB(128,0,128));   // T purple
        hBrushes[4] = CreateSolidBrush(RGB(0,255,0));     // S green
        hBrushes[5] = CreateSolidBrush(RGB(255,0,0));     // Z red
        hBrushes[6] = CreateSolidBrush(RGB(255,165,0));   // L orange
        hBrushes[7] = CreateSolidBrush(RGB(0,0,255));     // J blue
        hBrushes[8] = CreateSolidBrush(RGB(192,192,192)); // B gray
        tetris_view.start();
        SetTimer(hwnd, 1, 500, nullptr);
        return 0;
    case WM_TIMER:
        if(wParam == 1){
            tetris_view.proc(Command::MOVE_DOWN);
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        return 0;
    case WM_KEYDOWN:
        switch(wParam)
        {
        case VK_LEFT:  tetris_view.proc(Command::MOVE_LEFT);  break;
        case VK_RIGHT: tetris_view.proc(Command::MOVE_RIGHT); break;
        case VK_UP:    tetris_view.proc(Command::ROTATE_RIGHT); break;
        case VK_DOWN:  tetris_view.proc(Command::MOVE_DOWN); break;
        case VK_SPACE: tetris_view.proc(Command::HARD_DROP); break;
        case VK_CONTROL: tetris_view.proc(Command::ROTATE_LEFT); break;
        default: break;
        }
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        draw_grid(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        for(int i = 0; i < 9; ++i){
            if(hBrushes[i]) DeleteObject(hBrushes[i]);
        }
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TetrisClass";

    RegisterClassA(&wc);

    RECT wr = {0,0, GRID_WIDTH, GRID_HEIGHT};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, FALSE);

    HWND hwnd = CreateWindowA(
        "TetrisClass", "Tetris",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, hInstance, nullptr);

    if(!hwnd) return 0;
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}