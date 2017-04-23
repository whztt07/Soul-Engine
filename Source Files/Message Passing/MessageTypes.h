#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <atomic>
#include <mutex>

#define ALL_PRIORITIES { LOW, HIGH, IMMEDIATE }
#define ALL_DESTINATIONS { DISPLAY, SCHEDULER, PHYS_ENG, RASTER_ENG, RAY_ENG, RENDERER, SETTINGS, LOGGER }


namespace Messaging {
	enum Priority ALL_PRIORITIES; // { LOW, HIGH, IMMEDIATE };
	enum Destination ALL_DESTINATIONS; // { DISPLAY, SCHEDULER, PHYS_ENG, RASTER_ENG, RAY_ENG, RENDERER, SETTINGS, LOGGER };

	typedef Priority PriorityType;
	typedef Destination DestinationType;

	typedef std::shared_ptr<Message> MessagePointer;

	typedef std::priority_queue<MessagePointer, std::vector<MessagePointer>, detail::compareMessages> MessageQueue;
	typedef std::unordered_map<DestinationType, MessageQueue> MessageMap;
	typedef std::unordered_map<DestinationType, std::mutex> MutexMap;

	namespace detail {
		const std::vector<PriorityType> priorities = ALL_PRIORITIES; // { LOW, HIGH, IMMEDIATE };
		const std::vector<DestinationType> destinations = ALL_DESTINATIONS; // { DISPLAY, SCHEDULER, PHYS_ENG, RASTER_ENG, RAY_ENG, RENDERER, SETTINGS, LOGGER };

		struct compareMessages{
			bool operator()(MessagePointer m1, MessagePointer m2) const {
				if (m1->getPriority() > m2->getPriority()) return true;
				else if (m2->getPriority() > m1->getPriority()) return false;
				else return m1->getId() < m2->getId();
			}
		};
	}
}