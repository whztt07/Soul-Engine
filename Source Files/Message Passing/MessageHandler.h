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

		//Note: function must be implemented by engine module dest.
		//Also, function must delete args param, or memory leaks will occur
		bool registerFunction(DestinationType dest, const std::string & message, FunctionType function); 

	private:
		MessageMap allMessages;
		MutexMap messageMutexes;
		FunctionsMap allFunctions;
		MutexMap functionMutexes;

		/* data */
	};
}