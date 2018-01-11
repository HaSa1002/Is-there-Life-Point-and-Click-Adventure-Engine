#include "stdafx.h"
#include "CppUnitTest.h"
#include <Bus.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(MessageBus) {
	public:
		
		TEST_METHOD(sendAndRecieve) {
			pc::mb::Message message;
			std::string test_string = "Hello World!";
			message.data.push_back(static_cast<const void*>(test_string.data()));
			message.type = pc::mb::MessageType::sfEvent;
			std::function<void(pc::mb::Message)> f_reciever = [](pc::mb::Message message) {
				Assert::AreEqual("Hello World!", static_cast<const char*>(message.data.at(0)));
			};
			bus.subscribe(pc::mb::MessageType::Tree, f_reciever);
			bus.send(message);
		}

	private:
		pc::mb::Bus bus;
		
	};
}