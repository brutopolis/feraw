#include <emscripten.h>
#include <bruter.h>

#define WIDTH  256
#define HEIGHT 256

uint8_t *framebuffer;

EM_JS(void, draw_frame, (int ptr), {
    imgData.data.set(HEAPU8.subarray(ptr, ptr + fb_size));
    ctx.putImageData(imgData, 0, 0);
});

EM_JS(void, init_canvas, (int ptr, int w, int h), {
    fb_ptr = ptr;
    fb_size = w * h * 4;

    canvas.width = w;
    canvas.height = h;
    ctx = canvas.getContext('2d');
    imgData = ctx.createImageData(w, h);

    HEAPU8 = Module.HEAPU8;
});

EM_JS(void, evaluate_js, (char* str), {
    eval(UTF8ToString(str));
});

void render_frame()
{
    static int frame = 0;
    frame++;

    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            int idx = (y * WIDTH + x) * 4;
            framebuffer[idx + 0] = (x + frame) % 256;
            framebuffer[idx + 1] = (y + frame) % 256;
            framebuffer[idx + 2] = (x + y + frame) % 256;
            framebuffer[idx + 3] = 255;
        }
    }

    // EM_ASM({ draw_frame(); });
    draw_frame((int)framebuffer);
}

int main()
{
    framebuffer = malloc(WIDTH * HEIGHT * 4);

    EM_ASM({
        canvas = document.createElement('canvas');
        canvas.id = 'c';
        document.body.appendChild(canvas);
    });

    init_canvas((int)framebuffer, WIDTH, HEIGHT);

    emscripten_set_main_loop(render_frame, 0, 1);
}
