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
		bool registerFunction(DestinationType dest, const std::string & message, FunctionType function);

	private:
		MessageMap allMessages;
		MutexMap messageMutexes;
		FunctionsMap allFunctions;
		MutexMap functionMutexes;

		/* data */
	};
}