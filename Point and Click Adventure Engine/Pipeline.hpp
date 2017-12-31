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

#ifndef PC_PIPELINE
#define PC_PIPELINE

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <queue>

namespace pc {
	////////////////////////////////////////////////////////////
	// It blocks a second construction of the pipeline, as it
	// then would be stupid to build such a wrapper
	////////////////////////////////////////////////////////////
	bool pipeline_is_constructed = false;

	////////////////////////////////////////////////////////////
	/// Class that handles all File actions
	///
	////////////////////////////////////////////////////////////
	class Pipeline {
	public:

		////////////////////////////////////////////////////////////
		/// Task Code to know what should be done
		///
		////////////////////////////////////////////////////////////
		enum TaskCode {

		};

		////////////////////////////////////////////////////////////
		/// States the task state
		///
		///////////////////////////////////////////////////////////
		enum State {
			UnknownState = -1,			/// State is unknown
			Accepted,					/// Task is accepted
			Queued,						/// Task is queued
			Working,					/// Task is working
			Paused,						/// Task is paused
			WaitingForResource,			/// Task waits for a different resource (intern)
			WaitingForFileInput,		/// Task needs a specific file entered
			Completed,					/// Task is completed and can be collected
			Aborded,					/// Task was aborded
			Error,						/// An unknown Error occured
			ErrorIdAllreadyAssigned,	/// The id was already assinged, so that the task is not accepted
			ErrorFileNotFound,			/// A File wasn't found
			ErrorThreading,				/// Error occured with the threading
			UnknownId					/// The given id is not set
		};

		////////////////////////////////////////////////////////////
		/// Default constructor
		///
		/// This should ONLY constructed ONCE!
		///
		///////////////////////////////////////////////////////////
		Pipeline();

		////////////////////////////////////////////////////////////
		/// Default deconstructor
		///
		///////////////////////////////////////////////////////////
		~Pipeline();

		////////////////////////////////////////////////////////////
		/// adds a task to the queue
		///
		/// Adds a task to the queue. From now on the pipeline is handling
		/// the task autonomisly and returns you probably your processed
		/// data.
		///
		/// param task expresses what to do
		/// param task_id is the identifier for the pipeline and externs
		///			to recognize the task. Has to be unique!
		///
		/// returns State of the Task
		///
		///////////////////////////////////////////////////////////
		auto addTask(TaskCode task, const std::string& task_id)->State;

		////////////////////////////////////////////////////////////
		/// requests the state of the specific task
		///
		///
		/// param task_id of the task
		///
		/// returns State of the Task
		///
		/// seealso State
		///
		///////////////////////////////////////////////////////////
		auto requestState(const std::string& task_id)->State;

		////////////////////////////////////////////////////////////
		/// collects the data of the task
		///
		/// This method just returns a state, because it has tbi!
		/// A Collect method should NEVER return a State.
		///
		/// param task_id of the task
		///
		/// returns State of the Task
		///
		/// seealso State
		///
		///////////////////////////////////////////////////////////
		auto collect(const std::string& task_id)->State;

		////////////////////////////////////////////////////////////
		/// returns the TaskCode for your Task
		///
		/// param task_id of the task
		///
		/// returns TaskCode of the Task
		///
		/// throws an State Exception, if an error occured!
		///
		/// seealso TaskCode
		///
		///////////////////////////////////////////////////////////
		auto getTaskCode(const std::string& task_id)->TaskCode;

	private:

	};
}
#endif // !PC_PIPELINE

//TODO: Think about multithreading