#include "stdafx.h"
#include "CppUnitTest.h"
#include <Bus.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(MessageBus) {
	public:

		void reviever(pc::mb::Message message) {
			Assert::AreEqual("Hello World!", static_cast<const char*>(message.data.at(1)));
		}
		
		TEST_METHOD(sendAndRecieve) {
			pc::mb::Message message;
			std::string test_string = "Hello World!";
			message.data.push_back(static_cast<const void*>(test_string.data()));
			message.type = pc::mb::MessageType::Tree;
			std::function<void(pc::mb::Message)> f_reciever = [](pc::mb::Message message) {
				Assert::AreEqual("Hello World!", static_cast<const char*>(message.data.at(1)));
			};
			bus.subscribe(pc::mb::MessageType::Tree, f_reciever);
			bus.send(message);
		}

		TEST_METHOD(subscribe) {

		}

		TEST_METHOD(unsubscribe) {

		}

	private:
		pc::mb::Bus bus;
		
	};
}