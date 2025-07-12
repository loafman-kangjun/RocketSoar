#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window   *window   = nullptr;
static SDL_Renderer *renderer = nullptr;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* 让窗口可调整大小（同时保持启动即最大化） */
    constexpr Uint32 winflags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;

    if (!SDL_CreateWindowAndRenderer("Hello World",
                                     800, 600,
                                     winflags,
                                     &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc.) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    /* 如果你想在收到窗口尺寸变化时做额外处理，可取消注释
    if (event->type == SDL_EVENT_WINDOW_RESIZED) {
        // 这里可以更新逻辑或打印日志
    }
    */

    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const char *message = "Hello World!";
    int w = 0, h = 0;
    constexpr float scale = 4.0f;

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    float x = (w / scale - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2.0f;
    float y = (h / scale - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2.0f;

    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* Nothing to do here (renderer/window cleaned up automatically) */
}