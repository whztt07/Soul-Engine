#include "MessageHandler.h"

namespace Messaging {
	MessageHandler::MessageHandler() {
		for (int i = 0; i < detail::destinations.size(); ++i) {
			DestinationType dest = detail::destinations[i];
			allMessages[dest]; // = MessageQueue(); // create a message queue for each destination
			mutexes[dest]; // Default construct a mutex
		}
	}

	bool MessageHandler::addMessage(MessagePointer message) {
		if (!message) return false;
		DestinationType dest = message->getDestination();
		PriorityType p = message->getPriority();
		MessageQueue & queue = allMessages[dest];
		mutexes[dest].lock();
		
		//if (queue.empty()) {
		//	mutexes[dest].unlock();
		//	return false;
		//}
		
		queue.push(message);
		mutexes[dest].unlock();

		if (p == IMMEDIATE) {
			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, false, [dest,this]() {
				this->getMessage(dest);
			});
		}

		return true;
	}

	bool MessageHandler::getMessage(DestinationType dest) {
		MessageQueue & queue = allMessages[dest];
		mutexes[dest].lock();
		if (queue.empty()) {
			mutexes[dest].unlock();
		}

		MessagePointer message = queue.top();
		queue.pop();
		mutexes[dest].unlock();

		// PROCESS MESSAGE HERE

	}
}