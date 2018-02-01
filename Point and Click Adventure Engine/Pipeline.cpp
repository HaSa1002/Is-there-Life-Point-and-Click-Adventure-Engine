////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
// Copyright (c) 2017 Johannes Witt (johawitt@outlook.de)
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
#include "Exception.hpp"
#include "Pipeline.hpp"

namespace pc {

	Pipeline::Pipeline(mb::Bus& message_bus) :bus{ message_bus } {
		//Prevent double construction
		if (pipeline_is_constructed)
			throw(Exception::Pipeline_is_constructed);
		pipeline_is_constructed = true;
	}

	Pipeline::~Pipeline() {
		pipeline_is_constructed = false;
	}

	auto Pipeline::addTask(TaskCode task, const std::string & task_id) -> State {

		return State();
	}

	auto Pipeline::requestState(const std::string & task_id) -> State {

		return State();
	}

	auto Pipeline::collect(const std::string & task_id) -> State {

		return State();
	}

	auto Pipeline::getTaskCode(const std::string & task_id) -> TaskCode {

		return TaskCode();
	}

	Pipeline::Task::Task(const TaskCode& task_code, const std::string& task_id, std::shared_ptr<Data> data) :data{ data }, code{ task_code }, task_id{ task_id }, state{ State::Created } {}

	Pipeline::Data::~Data() {

	}

}