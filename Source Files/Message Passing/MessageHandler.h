#pragma once
#include "Message.h"
#include "../Multithreading/Scheduler.h"

/*
	Note to self: get running on scheduler maybe.
*/

namespace Messaging {
	class MessageHandler
	{
	public:
		MessageHandler();
		bool addMessage(MessagePointer message);
		bool getMessage(DestinationType dest);

	private:
		MessageMap allMessages;
		MutexMap mutexes;

		/* data */
	};
}