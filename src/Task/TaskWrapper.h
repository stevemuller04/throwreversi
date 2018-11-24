#ifndef INCLUDE_SRC_TASK_TASKWRAPPER_H
#define INCLUDE_SRC_TASK_TASKWRAPPER_H

#include "Task.h"
#include "../types.h"

/**
 * Internal class for describing an item on a list of tasks for a task manager.
 */
struct TaskWrapper
{
	private:
		Task * const task;
		mtime_t const register_time;
		/**
		 * The delay after register_time when the task shall be started.
		 * The special value '-1' denotes the fact that the task has been started already.
		 */
		mtime_t delay;
		bool const delete_when_done;

	public:
		TaskWrapper *prev = nullptr;
		TaskWrapper *next = nullptr;

	public:
		TaskWrapper(Task* task, mtime_t register_time, mtime_t delay, bool delete_when_done) :
			task(task),
			register_time(register_time),
			delay(delay == -1 ? -2 : delay), // make sure that the value 0xFFFFFFFF is not accidentally used
			delete_when_done(delete_when_done)
		{
		}

		~TaskWrapper()
		{
			if (delete_when_done)
				delete task;
		}

		bool start(mtime_t now)
		{
			if (delay != -1 && now - register_time >= delay)
			{
				delay = -1;
				task->setup();
				return true;
			}
			else
				return false;
		}

		bool hasStarted()
		{
			return delay == -1;
		}

		bool loop()
		{
			return task->loop();
		}
};

#endif
