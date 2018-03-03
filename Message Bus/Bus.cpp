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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Bus.hpp"

#include <cassert>

namespace pc {
	namespace mb {
		bool message_bus_constructed;
		Bus::Bus() {
			assert(message_bus_constructed == false && "The Message Bus should never be constructed more then once!");
			/*if (message_bus_constructed)
				throw(Exception::message_bus_constructed);*/
			message_bus_constructed = true;
		}



		Bus::~Bus() {
			message_bus_constructed = false;
		}



		void Bus::send(const Message& message) {
			for (const std::pair<size_t, Subscription>& i : bound_reciever) {
				for (unsigned int j = 0; j < i.second.first.size(); j++) {
					if (i.second.first.at(j) == message.type) {
						i.second.second(message);
						break;
					}
					if (i.second.first[j] == MessageType::ALL) {
						i.second.second(message);
						break;
					}
				}
			}
		}



		auto Bus::subscribe(const std::vector<MessageType>& types, Reciever reciever)->std::size_t{
			std::size_t hash_reciever = std::hash<Reciever*>{}(&reciever);
			std::vector<MessageType> input;
			if (auto vec = bound_reciever.find(hash_reciever) != bound_reciever.end()) {
				input = bound_reciever.find(hash_reciever)->second.first;
			}
			for (unsigned int i = 0; i < types.size(); ++i) {
				input.push_back(types.at(i));
			}
			bound_reciever.insert_or_assign(hash_reciever, Subscription(input, reciever));
			return hash_reciever;
		}



		auto Bus::subscribe(const MessageType& type, Reciever reciever)->std::size_t {
			std::size_t hash_reciever = std::hash<Reciever*>{}(&reciever);
			std::vector<MessageType> input;
			if (auto vec = bound_reciever.find(hash_reciever) != bound_reciever.end()) {
				input = bound_reciever.find(hash_reciever)->second.first;
			}
			input.push_back(type);
			bound_reciever.insert_or_assign(hash_reciever, Subscription(input, reciever));
			return hash_reciever;
		}



		void Bus::unsubscribe(const std::vector<MessageType>& types, Reciever reciever) {
			auto hash_reciever = std::hash<Reciever*>{}(&reciever);
			assert(bound_reciever.find(hash_reciever) != bound_reciever.end());
			auto vec = bound_reciever.at(hash_reciever).first;
			for (unsigned int i = 0; i < vec.size(); ++i) {
				for (unsigned int j = 0; j < types.size(); ++j) {
					if (vec.at(i) == types.at(j)) {
						MessageType temp = vec.back();
						vec.at(i) = temp;
						vec.pop_back();
					}
				}
			}
		}



		void Bus::unsubscribe(const MessageType& type, Reciever reciever) {
			auto hash_reciever = std::hash<Reciever*>{}(&reciever);
			assert(bound_reciever.find(hash_reciever) != bound_reciever.end());
			auto vec = bound_reciever.at(hash_reciever).first;
			for (unsigned int i = 0; i < vec.size(); ++i) {
				
				if (vec.at(i) == type) {
					MessageType temp = vec.back();
					vec.at(i) = temp;
					vec.pop_back();
				}
			}
		}



		void Bus::unsubscribe(Reciever reciever) {
			bound_reciever.erase(std::hash<Reciever*>{}(&reciever));
		}
	}
}