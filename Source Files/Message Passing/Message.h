#pragma once

#include "MessageTypes.h"

namespace Messaging {

	class Message
	{
	public:
		Message(PriorityType p, DestinationType d);
		
		unsigned int getId() const { return id; }
		PriorityType getPriority() const { return priority; }
		DestinationType getDestination() const { return destination };

	protected:
		PriorityType priority;
		DestinationType destination;
		unsigned int id;
		//store the message???

		static std::atomic_uint32_t nextId;
		static std::atomic_uint32_t getNextId() { return nextId++; }


		/* data */
	};
}