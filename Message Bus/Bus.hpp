////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#ifndef PC_MB_BUS
#define PC_MB_BUS

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Message.hpp"
#include "MessageTypes.hpp"

#include <functional>
#include <map>
#include <vector>

namespace pc {
	namespace mb {

		bool message_bus_constructed = false;

		typedef std::function<void(Message)> Reciever;
		typedef std::pair<std::vector<MessageType>, Reciever> Subscription;

		class Bus {
		public:
			Bus();
			~Bus();

			void send(Message message);
			auto subscribe(std::vector<MessageType>& types, Reciever reciever)->std::size_t;
			void unsubscribe(std::vector<MessageType>& types, Reciever reciever);
			void unsubscribe(const MessageType & type, Reciever reciever);
			void unsubscribe(Reciever reciever);

		private:
			std::map<std::size_t, std::pair<std::vector<MessageType>, Reciever>> bound_reciever;
		};
	}
}



#endif // !PC_MB_BUS