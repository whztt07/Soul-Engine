#include "Message.h"

namespace Messaging {
	std::atomic_uint32_t Message::nextId = 0;

	Message::Message(PriorityType p, Destination d) {
		priority = p; 
		id = static_cast<unsigned int>(getNextId());
		destination = d;
	}
}