#include "core/gsm.hpp"
#include "core/game_state.hpp"

void GameStateManager::push(std::unique_ptr<GameState> state) {
    queued_actions.push_back({ StateActionType::Push, std::move(state) });
}

void GameStateManager::pop() {
    queued_actions.push_back({ StateActionType::Pop });
}

void GameStateManager::change(std::unique_ptr<GameState> game_state) {
    queued_actions.push_back({ StateActionType::Change, std::move(game_state) });
}

void GameStateManager::applyQueuedActions() {
    for (auto& action : queued_actions) {
        switch (action.type) {
        case StateActionType::Change:
        case StateActionType::Pop:
            if (!m_stack.empty()) {
                m_stack.back()->onExit();
                m_stack.pop_back();
            }
            if(action.type == StateActionType::Pop) break;
        case StateActionType::Push:
            if (action.new_state) {
                action.new_state->onEnter();
                m_stack.push_back(std::move(action.new_state));
            }
            break;
        }
        
    }
    queued_actions.clear();
}

void GameStateManager::handleInput(sf::RenderWindow& window, float dt) {

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
        {
            for (int i = static_cast<int>(m_stack.size()) - 1; i >= 0; --i) {
                m_stack[i]->ev_h.handleSingleKeyEvents(key_pressed);
                if (m_stack[i]->blocksEventsBelow())
                    break;
            }

        }
    }

    for (int i = static_cast<int>(m_stack.size()) - 1; i >= 0; --i) {
        m_stack[i]->ev_h.handleRepeatKeyEvents();
        m_stack[i]->ev_h.runScheduledEvents(dt);
        if (m_stack[i]->blocksEventsBelow())
            break;
    }
}

void GameStateManager::update(float dt) {
    for (int i = static_cast<int>(m_stack.size()) - 1; i >= 0; --i) {
        m_stack[i]->update(dt);
        if (m_stack[i]->blocksUpdateBelow())
            break;
    }
}

void GameStateManager::render(RenderContext& ctx) {
    for (size_t i = 0; i < m_stack.size(); ++i) {
        m_stack[i]->render(ctx);
        if (m_stack[i]->blocksRenderBelow())
            break;
    }
}

bool GameStateManager::empty() const {
    return m_stack.empty();
}
