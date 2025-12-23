#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <functional>

using KeyCallback = std::function<void()>;
using SchedCallback = std::function<void()>;

struct KeyEvent {
	KeyCallback callback;
	bool repeat;
};

struct ScheduledEvent {
	SchedCallback callback;
	int repeats;
	bool indefinite;
	float nextExecute;
	float seconds_interval;
};


class EventHandler {

	std::unordered_map<sf::Keyboard::Scan, std::vector<KeyEvent>> key_events;
	std::vector<ScheduledEvent> scheduled_events;
	std::vector<sf::Keyboard::Key> pressed_keys;

	float elapsed_time = 0;

public:
	void registerKeyEvent(sf::Keyboard::Scan key, KeyCallback callback, bool repeat);
	void scheduleEvent(SchedCallback callback, float interval, int repeats, bool indefinite = false);
	void handleSingleKeyEvents(const sf::Event::KeyPressed*);
	void handleRepeatKeyEvents();
	void runScheduledEvents(float dt);
};