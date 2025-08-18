#include "bruter.h"
#include "raylib.h"

// constructors
function(feraw_Vector2)
{
    BruterList* list = bruter_new(2, true, true);
    
}


// raylib functions

function(raylib_init_window)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *title = (char*)bruter_pop_pointer(stack);
    InitWindow(width, height, title);
}

function(raylib_close_window)
{
    CloseWindow();
}

function(raylib_window_should_close)
{
    bool shouldClose = WindowShouldClose();
    bruter_push_int(stack, shouldClose, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_ready)
{
    bool isReady = IsWindowReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_fullscreen)
{
    bool isFullscreen = IsWindowFullscreen();
    bruter_push_int(stack, isFullscreen, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_hidden)
{
    bool isHidden = IsWindowHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_minimized)
{
    bool isMinimized = IsWindowMinimized();
    bruter_push_int(stack, isMinimized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_maximized)
{
    bool isMaximized = IsWindowMaximized();
    bruter_push_int(stack, isMaximized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_focused)
{
    bool isFocused = IsWindowFocused();
    bruter_push_int(stack, isFocused, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_resized)
{
    bool isResized = IsWindowResized();
    bruter_push_int(stack, isResized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_state)
{
    int flags = bruter_pop_int(stack);
    bool isState = IsWindowState(flags);
    bruter_push_int(stack, isState, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_window_state)
{
    int flags = bruter_pop_int(stack);
    SetWindowState(flags);
}

function(raylib_clear_window_state)
{
    int flags = bruter_pop_int(stack);
    ClearWindowState(flags);
}

function(raylib_toggle_fullscreen)
{
    ToggleFullscreen();
}

function(raylib_toggle_borderless_windowed)
{
    ToggleBorderlessWindowed();
}

function(raylib_maximize_window)
{
    MaximizeWindow();
}

function(raylib_minimize_window)
{
    MinimizeWindow();
}

function(raylib_restore_window)
{
    RestoreWindow();
}