#pragma once

#include "util/event_handler.hpp"
#include "render/render_context.hpp"

class GameState {
public:

    EventHandler evHandler;
    
    virtual ~GameState() = default;
    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void update(float dt) = 0;
    virtual void render(RenderContext& ctx) = 0;

    virtual bool blocksUpdateBelow() const { return true; }
    virtual bool blocksEventsBelow() const { return true; }
    virtual bool blocksRenderBelow() const { return true; }
};