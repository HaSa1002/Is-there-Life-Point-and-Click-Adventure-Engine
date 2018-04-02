#include "Scene.hpp"

namespace pc {
	Scene::Scene(mb::Bus& bus) : message_bus{ bus } {
		bus.subscribe(mb::MessageType::Scene, reciever); //we possibly don't need any messages
	}



}