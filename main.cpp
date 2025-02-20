#include <chrono>
#include <format>
#include <print>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct AppState {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int window_x;
    int window_y;

    uint64_t fps {0};
    uint64_t ticks_since_fps_update {0};
    std::chrono::time_point<std::chrono::steady_clock> prev_fps_update {
        std::chrono::steady_clock::now()
    };

    AppState(int window_x, int window_y):
        window_x(window_x),
        window_y(window_y)
    {}

    // Return the current FPS. The value returned from this function will change
    // at most once-per-second, irrespective of how many times it is called in
    // the intervening second.
    uint64_t flip_fps() {
        const auto now {std::chrono::steady_clock::now()};

        ++ticks_since_fps_update;

        if (now > prev_fps_update + std::chrono::seconds(1)) {
            fps = ticks_since_fps_update;

            ticks_since_fps_update = 0;

            prev_fps_update = now;
        }

        return fps;
    }
};

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* as = static_cast<AppState*>(appstate);
    auto &renderer {as->renderer};

    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const auto fps {as->flip_fps()};
    const auto fps_str {std::format("FPS: {}", fps)};

    SDL_SetRenderScale(renderer, 1.4, 1.4);
    SDL_SetRenderDrawColor(renderer, 0, 100, 155, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, 2, 2, fps_str.c_str());
    SDL_SetRenderScale(renderer, 1.0, 1.0);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    AppState* as = new AppState(200, 400);

    if (!as) {
        return SDL_APP_FAILURE;
    }

    for (int i {0}; i < SDL_GetNumRenderDrivers(); ++i) {
        std::println("Render driver: [{}]", SDL_GetRenderDriver(i));
    }

    if (
        !SDL_CreateWindowAndRenderer(
            "boxes that can't touch",
            as->window_x, as->window_y,
            0,
            &as->window, &as->renderer)
    ) {
        return SDL_APP_FAILURE;
    }

    std::println("Renderer name: [{}]", SDL_GetRendererName(as->renderer));

    if (SDL_SetRenderVSync(as->renderer, SDL_RENDERER_VSYNC_ADAPTIVE)) {
        std::println("Set vsync adaptive");
    }
    else if (SDL_SetRenderVSync(as->renderer, 1)) {
        std::println("Set vsync every refresh");
    }
    else if (SDL_SetRenderVSync(as->renderer, 2)) {
        std::println("Set vsync every other refresh");
    }
    else if (SDL_SetRenderVSync(as->renderer, SDL_RENDERER_VSYNC_DISABLED)) {
        std::println("Set vsync disabled");
    }
    else {
        std::println("Failed to disable vsync after failure to set vsync.");

        return SDL_APP_FAILURE;
    }

    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);
    SDL_RenderPresent(as->renderer);

    *appstate = as;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;

    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    AppState* as = static_cast<AppState*>(appstate);

    delete as;
}
