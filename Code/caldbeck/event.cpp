#include <caldbeck/event.hpp>

Event::Event(EventType type) { m_type = type; }

EventType Event::GetType() { return m_type; }