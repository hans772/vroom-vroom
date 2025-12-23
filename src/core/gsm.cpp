#include "core/gsm.hpp"
#include "core/game_state.hpp"

void GameStateManager::push(std::unique_ptr<GameState> state) {
    queuedActions.push_back({ StateActionType::Push, std::move(state) });
}

void GameStateManager::pop() {
    queuedActions.push_back({ StateActionType::Pop });
}

void GameStateManager::change(std::unique_ptr<GameState> game_state) {
    queuedActions.push_back({ StateActionType::Change, std::move(game_state) });
}

void GameStateManager::applyQueuedActions() {
    for (auto& action : queuedActions) {
        switch (action.type) {
        case StateActionType::Change:
        case StateActionType::Pop:
            if (!stateStack.empty()) {
                stateStack.back()->onExit();
                stateStack.pop_back();
            }
            if(action.type == StateActionType::Pop) break;
        case StateActionType::Push:
            if (action.newState) {
                action.newState->onEnter();
                stateStack.push_back(std::move(action.newState));
            }
            break;
        }
        
    }
    queuedActions.clear();
}

void GameStateManager::handleInput(sf::RenderWindow& window, float dt) {

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
        {
            for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
                stateStack[i]->evHandler.handleSingleKeyEvents(key_pressed);
                if (stateStack[i]->blocksEventsBelow())
                    break;
            }

        }
    }

    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        stateStack[i]->evHandler.handleRepeatKeyEvents();
        stateStack[i]->evHandler.runScheduledEvents(dt);
        if (stateStack[i]->blocksEventsBelow())
            break;
    }
}

void GameStateManager::update(float dt) {
    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        stateStack[i]->update(dt);
        if (stateStack[i]->blocksUpdateBelow())
            break;
    }
}

void GameStateManager::render(RenderContext& ctx) {
    for (size_t i = 0; i < stateStack.size(); ++i) {
        stateStack[i]->render(ctx);
        if (stateStack[i]->blocksRenderBelow())
            break;
    }
}

bool GameStateManager::empty() const {
    return stateStack.empty();
}
