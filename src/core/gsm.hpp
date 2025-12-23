#pragma once 

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "util/singleton.hpp"
#include "core/game_state.hpp"
#include "render/render_context.hpp"

class GameState;
class RenderContext;

enum class StateActionType { Push, Pop, Change };

struct StateAction {
    StateActionType type;
    std::unique_ptr<GameState> new_state = nullptr;
};

class GameStateManager : public Singleton<GameStateManager> {
    friend class Singleton<GameStateManager>;

public:
    void push(std::unique_ptr<GameState> state);
    void pop();
    void change(std::unique_ptr<GameState> state);
    void applyQueuedActions();

    void handleInput(sf::RenderWindow& window, float dt);
    void update(float dt);
    void render(RenderContext& ctx);

    bool empty() const;

private:
    std::vector<std::unique_ptr<GameState>> m_stack;
    std::vector<StateAction> queued_actions;

};