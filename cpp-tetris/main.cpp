#include <iostream>
#include <windows.h>
#include "Presenter.hpp"

void display(const auto& tetris)
{
    for(index_type y = 0; y < MATRIX_HEIGHT; ++y){
        for(index_type x = 0; x < MATRIX_WIDTH; ++x){
            std::cout << tetris(y, x);
        }
        std::cout << '\n';
    }
}

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

Presenter presenter;
TetrisView tetris_view = presenter.make_view();

int main()
{
    INPUT_RECORD irInBuf[128];

    // Get the standard input handle.

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.

    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (! SetConsoleMode(hStdin, fdwMode) )
        ErrorExit("SetConsoleMode");

    // Loop to read and handle the next 100 input events.

    tetris_view.start();

    int counter = 0;

    while (counter++ <= 100)
    {
        // Wait for the events.

        DWORD cNumRead;

        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.

        for (DWORD i = 0; i < cNumRead; ++i)
        {
            std::system("cls");

            switch(irInBuf[i].EventType)
            {
                case KEY_EVENT: // keyboard input
                    KeyEventProc(irInBuf[i].Event.KeyEvent);
                    break;

                case FOCUS_EVENT:  // disregard focus events

                case MENU_EVENT:   // disregard menu events
                    break;

                default:
                    ErrorExit("Unknown event type");
                    break;
            }

            display(tetris_view);
        }
    }

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}

VOID ErrorExit (LPCSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    static WORD previous_key;
    static bool previous_pushed;

    switch(ker.wVirtualKeyCode){
        case VK_LEFT:
            if(!previous_pushed || previous_key != VK_LEFT) tetris_view.proc(Command::MOVE_LEFT);
            previous_key = VK_LEFT;
            std::cout << "Left key pressed\n";
            break;
        case VK_RIGHT:
            if(!previous_pushed || previous_key != VK_RIGHT) tetris_view.proc(Command::MOVE_RIGHT);
            previous_key = VK_RIGHT;
            std::cout << "Right key pressed\n";
            break;
        case VK_CONTROL:
            if(!previous_pushed || previous_key != VK_RIGHT) tetris_view.proc(Command::ROTATE_LEFT);
            previous_key = VK_CONTROL;
            std::cout << "Ctrl key pressed\n";
            break;
        case VK_UP:
            if(!previous_pushed || previous_key != VK_UP) tetris_view.proc(Command::ROTATE_RIGHT);
            previous_key = VK_UP;
            std::cout << "Up key pressed\n";
            break;
        case VK_DOWN:
            if(!previous_pushed || previous_key != VK_DOWN) tetris_view.proc(Command::MOVE_DOWN);
            previous_key = VK_DOWN;
            std::cout << "Down key pressed\n";
            break;
        case VK_SPACE:
            if(!previous_pushed || previous_key != VK_SPACE) tetris_view.proc(Command::HARD_DROP);
            previous_key = VK_SPACE;
            std::cout << "Space key pressed\n";
            break;
        default:
            std::cout << "No key is being pressed\n";
            break;
    }

    previous_pushed = ker.bKeyDown;
}