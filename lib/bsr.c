#define BSR_H 1


#define OLIVEC_IMPLEMENTATION
#include "olive.c"
#include "MiniFB.h"
#include <bruter.h>

// olive.c RGBA to ARGB patch
// i am not sure if this patch does anything at all
// seems right, but i see no difference at all between the image generated using this patch and the original olive.c without this patch

// lets first undefine the olivec original macros
#undef OLIVEC_ALPHA
#undef OLIVEC_RED
#undef OLIVEC_GREEN
#undef OLIVEC_BLUE
#undef OLIVEC_ARGB
#undef OLIVEC_RGBA

// now redefine them to use ARGB instead of RGBA
#define OLIVEC_ALPHA(color)   (((color) & 0xFF000000) >> 24)
#define OLIVEC_RED(color)     (((color) & 0x00FF0000) >> 16)
#define OLIVEC_GREEN(color)   (((color) & 0x0000FF00) >> 8)
#define OLIVEC_BLUE(color)    (((color) & 0x000000FF) >> 0)
#define OLIVEC_ARGB(a,r,g,b)  ( ((a)<<24) | ((r)<<16) | ((g)<<8) | (b) )
#define OLIVEC_RGBA(r,g,b,a)  OLIVEC_ARGB(a, r, g, b)

typedef struct 
{
    struct mfb_window *window; // window pointer
    char *title; // window title
    Olivec_Canvas canvas; // canvas for drawing
    uint8_t keys[350]; // key states
    uint8_t key_mods[6]; // shift, ctrl, alt, super, caps lock, num lock
    float mouse_scroll_delta_x; // mouse scroll x
    float mouse_scroll_delta_y; // mouse scroll y
    char character; // last character input
    uint8_t flags;

} BSRWindow;

BruterList *bsr_windows = NULL;

// callbacks

static void resize(struct mfb_window *window, int width, int height)
{
    uint32_t x = 0;
    uint32_t y = 0;
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);


    if(width > current_window->canvas.width)
    {
        x = (width - current_window->canvas.width) >> 1;
        width = current_window->canvas.width;
    }
    if(height > current_window->canvas.height)
    {
        y = (height - current_window->canvas.height) >> 1;
        height = current_window->canvas.height;
    }
    current_window->canvas.pixels = realloc(current_window->canvas.pixels, width * height * 4); // reallocate buffer for the new window size
    if (current_window->canvas.pixels == NULL) {
        printf("Failed to reallocate buffer for window\n");
        return;
    }
    current_window->canvas.width = width;
    current_window->canvas.height = height;
    mfb_set_viewport(window, x, y, width, height);
}

static void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->keys[key] = isPressed ? 1 : 0;
    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}

static void char_input(struct mfb_window *window, unsigned int charCode) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->character = (char)charCode;
}

static void mouse_btn(struct mfb_window *window, mfb_mouse_button button, mfb_key_mod mod, bool isPressed) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    if (button == MOUSE_LEFT) 
    {
        current_window->keys[MOUSE_BTN_1] = isPressed ? 1 : 0;
    } 
    else if (button == MOUSE_RIGHT) 
    {
        current_window->keys[MOUSE_BTN_2] = isPressed ? 1 : 0;
    } 
    else if (button == MOUSE_MIDDLE) 
    {
        current_window->keys[MOUSE_BTN_3] = isPressed ? 1 : 0;
    } 
    else if (button >= MOUSE_BTN_4 && button <= MOUSE_BTN_7) 
    {
        current_window->keys[button] = isPressed ? 1 : 0;
    }

    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}

static void mouse_scroll(struct mfb_window *window, mfb_key_mod mod, float deltaX, float deltaY) 
{
    BSRWindow *current_window = (BSRWindow *)mfb_get_user_data(window);
    current_window->mouse_scroll_delta_x += deltaX;
    current_window->mouse_scroll_delta_y += deltaY;

    current_window->key_mods[0] = (mod & KB_MOD_SHIFT) ? 1 : 0;
    current_window->key_mods[1] = (mod & KB_MOD_CONTROL) ? 1 : 0;
    current_window->key_mods[2] = (mod & KB_MOD_ALT) ? 1 : 0;
    current_window->key_mods[3] = (mod & KB_MOD_SUPER) ? 1 : 0;
    current_window->key_mods[4] = (mod & KB_MOD_CAPS_LOCK) ? 1 : 0;
    current_window->key_mods[5] = (mod & KB_MOD_NUM_LOCK) ? 1 : 0;
}
// functions

function(new_window) 
{
    char *title = bruter_pop_pointer(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int flags = bruter_pop_int(stack);

    struct mfb_window *window = mfb_open_ex(title, width, height, flags);
    if (window == NULL) 
    {
        printf("Failed to create window\n");
        return;
    }
    BSRWindow *bsr_window = (BSRWindow*)malloc(sizeof(BSRWindow));
    if (bsr_window == NULL) 
    {
        printf("Failed to allocate memory for BSRWindow\n");
        mfb_close(window);
        return;
    }
    bsr_window->window = window;
    bsr_window->title = title;
    bsr_window->canvas = olivec_canvas(
        (uint32_t*)malloc(width * height * sizeof(uint32_t)), // allocate memory for pixels
        width, height, width // stride is the same as width in pixels
    );
    bsr_window->flags = flags;
    memset(bsr_window->keys, 0, sizeof(bsr_window->keys));
    memset(bsr_window->key_mods, 0, sizeof(bsr_window->key_mods));
    bsr_window->mouse_scroll_delta_x = 0.0f;
    bsr_window->mouse_scroll_delta_y = 0.0f;
    bsr_window->character = 0;
    mfb_set_user_data(window, bsr_window);
    mfb_set_resize_callback(window, resize);
    mfb_set_keyboard_callback(window, keyboard);
    mfb_set_char_input_callback(window, char_input);
    mfb_set_mouse_button_callback(window, mouse_btn);
    mfb_set_mouse_scroll_callback(window, mouse_scroll);
    
    mfb_set_viewport(window, 0, 0, width, height);

    bruter_push_pointer(bsr_windows, bsr_window, NULL, 0);

    bruter_push_pointer(stack, bsr_window, NULL, BRUTER_TYPE_BUFFER);
}

function(close_window)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;

    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }
    
    for (BruterInt i = 0; i < bsr_windows->size; i++)
    {
        BSRWindow *bsr_window = (BSRWindow*)bsr_windows->data[i].p;
        if (bsr_window && bsr_window->window == window)
        {
            free(bsr_window->canvas.pixels);
            free(bsr_window);
            bsr_windows->data[i].p = NULL; // mark as removed
            bruter_remove(bsr_windows, i);
            break;
        }
    }

    mfb_close(window);
}

function(update_window) 
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    uint8_t *buffer = (uint8_t*)(current_window)->canvas.pixels;
    int width = current_window->canvas.width;
    int height = current_window->canvas.height;
    if (window == NULL || buffer == NULL)
    {
        printf("Window or buffer is NULL\n");
    }
    if (mfb_update_ex(window, buffer, width, height) < 0)
    {
        printf("Failed to update window\n");
    }
    return;
}

function(update_window_events) 
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }
    mfb_update_events(window);
}

function(is_window_active)
{
    bruter_push_int(stack, mfb_is_window_active((struct mfb_window*)((BSRWindow*)(bruter_pop_pointer(stack)))->window), NULL, BRUTER_TYPE_ANY);
}

function(get_window_width)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_window_width(window), NULL, BRUTER_TYPE_ANY);
}

function(get_window_height)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_window_height(window), NULL, BRUTER_TYPE_ANY);
}

function(get_mouse_x)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_mouse_x(window), NULL, BRUTER_TYPE_ANY);
}

function(get_mouse_y)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_mouse_y(window), NULL, BRUTER_TYPE_ANY);
}

function(get_mouse_scroll_x)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_mouse_scroll_x(window), NULL, BRUTER_TYPE_ANY);
}

function(get_mouse_scroll_y)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    bruter_push_int(stack, mfb_get_mouse_scroll_y(window), NULL, BRUTER_TYPE_ANY);
}

function(wait_sync)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }
    bruter_push_pointer(stack, current_window, NULL, BRUTER_TYPE_BUFFER);
}

// io functions

function(is_key_pressed)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }
    mfb_key key = (mfb_key)bruter_pop_int(stack);
    bruter_push_int(stack, current_window->keys[key], NULL, BRUTER_TYPE_ANY);
}

function(get_framebuffer)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }
    uint8_t *buffer = (uint8_t*)(current_window)->canvas.pixels;
    if (buffer == NULL)
    {
        printf("Buffer is NULL\n");
        return;
    }
    
    bruter_push_pointer(stack, buffer, NULL, BRUTER_TYPE_BUFFER);
}


// drawing functions
function(fill)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    uint32_t color = bruter_pop_int(stack);

    olivec_fill(*canvas, color);    
}

function(draw_rect)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_rect(*canvas, x, y, width, height, color);
}

function(draw_frame)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int thickness = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_frame(*canvas, x, y, width, height, thickness, color);
}

function(draw_circle)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_circle(*canvas, x, y, radius, color);
}

function(draw_ellipse)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int radius_x = bruter_pop_int(stack);
    int radius_y = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_ellipse(*canvas, x, y, radius_x, radius_y, color);
}

function(draw_line)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_line(*canvas, x1, y1, x2, y2, color);
}


function(draw_triangle)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    int x3 = bruter_pop_int(stack);
    int y3 = bruter_pop_int(stack);
    uint32_t color = bruter_pop_int(stack);

    olivec_triangle(*canvas, x1, y1, x2, y2, x3, y3, color);
}

function(draw_triangle3c)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    int x3 = bruter_pop_int(stack);
    int y3 = bruter_pop_int(stack);
    uint32_t c1 = bruter_pop_int(stack);
    uint32_t c2 = bruter_pop_int(stack);
    uint32_t c3 = bruter_pop_int(stack);

    olivec_triangle3c(*canvas, x1, y1, x2, y2, x3, y3, c1, c2, c3);
}

function(draw_triangle3z)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    int x3 = bruter_pop_int(stack);
    int y3 = bruter_pop_int(stack);
    float z1 = bruter_pop_float(stack);
    float z2 = bruter_pop_float(stack);
    float z3 = bruter_pop_float(stack);

    olivec_triangle3z(*canvas, x1, y1, x2, y2, x3, y3, z1, z2, z3);
}

function(draw_triangle3uv)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    int x3 = bruter_pop_int(stack);
    int y3 = bruter_pop_int(stack);
    float tx1 = bruter_pop_float(stack);
    float ty1 = bruter_pop_float(stack);
    float tx2 = bruter_pop_float(stack);
    float ty2 = bruter_pop_float(stack);
    float tx3 = bruter_pop_float(stack);
    float ty3 = bruter_pop_float(stack);
    float z1 = bruter_pop_float(stack);
    float z2 = bruter_pop_float(stack);
    float z3 = bruter_pop_float(stack);
    Olivec_Canvas* texture = (Olivec_Canvas*)bruter_pop_pointer(stack);
    if (texture == NULL) {
        printf("Texture is NULL\n");
        return;
    }
    
    olivec_triangle3uv(*canvas, x1, y1, x2, y2, x3, y3, tx1, ty1, tx2, ty2, tx3, ty3, z1, z2, z3, *texture);
}

function(draw_triangle3uv_bilinear)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    int x1 = bruter_pop_int(stack);
    int y1 = bruter_pop_int(stack);
    int x2 = bruter_pop_int(stack);
    int y2 = bruter_pop_int(stack);
    int x3 = bruter_pop_int(stack);
    int y3 = bruter_pop_int(stack);
    float tx1 = bruter_pop_float(stack);
    float ty1 = bruter_pop_float(stack);
    float tx2 = bruter_pop_float(stack);
    float ty2 = bruter_pop_float(stack);
    float tx3 = bruter_pop_float(stack);
    float ty3 = bruter_pop_float(stack);
    float z1 = bruter_pop_float(stack);
    float z2 = bruter_pop_float(stack);
    float z3 = bruter_pop_float(stack);
    Olivec_Canvas* texture = (Olivec_Canvas*)bruter_pop_pointer(stack);
    if (texture == NULL) {
        printf("Texture is NULL\n");
        return;
    }
    
    olivec_triangle3uv_bilinear(*canvas, x1, y1, x2, y2, x3, y3, tx1, ty1, tx2, ty2, tx3, ty3, z1, z2, z3, *texture);
}

/*
OLIVECDEF void olivec_sprite_blend(Olivec_Canvas oc, int x, int y, int w, int h, Olivec_Canvas sprite);
OLIVECDEF void olivec_sprite_copy(Olivec_Canvas oc, int x, int y, int w, int h, Olivec_Canvas sprite);
OLIVECDEF void olivec_sprite_copy_bilinear(Olivec_Canvas oc, int x, int y, int w, int h, Olivec_Canvas sprite);

*/

function(draw_sprite_blend)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int w = bruter_pop_int(stack);
    int h = bruter_pop_int(stack);
    Olivec_Canvas* sprite = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    olivec_sprite_blend(*canvas, x, y, w, h, *sprite);
}

function(draw_sprite_copy)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int w = bruter_pop_int(stack);
    int h = bruter_pop_int(stack);
    Olivec_Canvas* sprite = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    olivec_sprite_copy(*canvas, x, y, w, h, *sprite);
}

function(draw_sprite_copy_bilinear)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int w = bruter_pop_int(stack);
    int h = bruter_pop_int(stack);
    Olivec_Canvas* sprite = (Olivec_Canvas*)bruter_pop_pointer(stack);
    
    olivec_sprite_copy_bilinear(*canvas, x, y, w, h, *sprite);
}

function(argb_to_canvas)
{
    uint32_t *data = (uint32_t*)bruter_pop_pointer(stack);
    uint32_t width = data[0];
    uint32_t height = data[1];
    
    Olivec_Canvas* canvas = (Olivec_Canvas*)malloc(sizeof(Olivec_Canvas));
    if (canvas == NULL) {
        printf("Failed to allocate memory for Olivec_Canvas\n");
        return;
    }
    canvas->pixels = malloc(width * height * sizeof(uint32_t));
    memcpy(canvas->pixels, data + 2, width * height * sizeof(uint32_t));
    canvas->width = width;
    canvas->height = height;
    canvas->stride = width;

    bruter_push_pointer(stack, canvas, NULL, BRUTER_TYPE_BUFFER);
}

function(new_canvas)
{
    uint32_t width = bruter_pop_int(stack);
    uint32_t height = bruter_pop_int(stack);
    
    Olivec_Canvas* canvas = (Olivec_Canvas*)malloc(sizeof(Olivec_Canvas));
    if (canvas == NULL) {
        printf("Failed to allocate memory for Olivec_Canvas\n");
        return;
    }
    canvas->pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (canvas->pixels == NULL) {
        printf("Failed to allocate memory for canvas pixels\n");
        free(canvas);
        return;
    }
    canvas->width = width;
    canvas->height = height;
    canvas->stride = width;

    bruter_push_pointer(stack, canvas, NULL, BRUTER_TYPE_BUFFER);
}

function(get_window_canvas)
{
    BSRWindow *current_window = (BSRWindow*)(bruter_pop_pointer(stack));
    struct mfb_window *window = (struct mfb_window*)(current_window)->window;
    if (window == NULL)
    {
        printf("Window is NULL\n");
        return;
    }

    Olivec_Canvas* canvas = &current_window->canvas;
    bruter_push_pointer(stack, canvas, NULL, BRUTER_TYPE_BUFFER);
}

function(canvas_get_width)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    if (canvas == NULL)
    {
        printf("Canvas is NULL\n");
        return;
    }
    
    bruter_push_int(stack, canvas->width, NULL, BRUTER_TYPE_ANY);
}

function(canvas_get_height)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    if (canvas == NULL)
    {
        printf("Canvas is NULL\n");
        return;
    }
    
    bruter_push_int(stack, canvas->height, NULL, BRUTER_TYPE_ANY);
}

function(free_canvas)
{
    Olivec_Canvas* canvas = (Olivec_Canvas*)bruter_pop_pointer(stack);
    if (canvas == NULL)
    {
        printf("Canvas is NULL\n");
        return;
    }
    if (canvas->pixels != NULL)
    {
        free(canvas->pixels);
    }
    free(canvas);
}

void __bsr_at_exit(void)
{
    if (bsr_windows != NULL)
    {
        for (BruterInt i = 0; i < bsr_windows->size; i++)
        {
            BSRWindow *bsr_window = (BSRWindow*)bsr_windows->data[i].p;
            if (bsr_window != NULL)
            {
                mfb_close(bsr_window->window);
                free(bsr_window);
            }
        }
        bruter_free(bsr_windows);
    }
}

function(init_bsr)
{
    BruterList *context = bruter_pop_pointer(stack);
    bsr_windows = bruter_new(8, true, false);
    
    // add bsr_windows to context
    bruter_push_pointer(context, bsr_windows, "bsr_windows", BRUTER_TYPE_LIST);

    // register at exit function
    atexit(__bsr_at_exit);
}