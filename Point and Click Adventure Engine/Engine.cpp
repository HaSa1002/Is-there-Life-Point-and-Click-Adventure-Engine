#include "Engine.hpp"

namespace pc {
	auto Engine::getRendering() -> Rendering & {
		return rendering;
	}

	auto Engine::getBus() -> mb::Bus & {
		return bus;
	}

	auto Engine::getPipeline() -> Pipeline & {
		return pipeline;
	}
	auto Engine::getEcs() -> cs::System &
	{
		return ecs;
	}
}