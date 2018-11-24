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
		Task * const _task;
		mtime_t const _register_time;
		/**
		 * The delay after register_time when the task shall be started.
		 * The special value '-1' denotes the fact that the task has been started already.
		 */
		mtime_t _delay;
		bool const _delete_when_done;

	public:
		TaskWrapper *prev = nullptr;
		TaskWrapper *next = nullptr;

	public:
		TaskWrapper(Task *task, mtime_t register_time, mtime_t delay, bool delete_when_done) :
			_task(task),
			_register_time(register_time),
			_delay(delay == -1 ? -2 : delay), // make sure that the value 0xFFFFFFFF is not accidentally used
			_delete_when_done(delete_when_done)
		{
		}

		~TaskWrapper()
		{
			if (_delete_when_done)
				delete _task;
		}

		bool start(mtime_t now)
		{
			if (_delay != -1 && now - _register_time >= _delay)
			{
				_delay = -1;
				_task->setup();
				return true;
			}
			else
				return false;
		}

		bool hasStarted()
		{
			return _delay == -1;
		}

		bool loop()
		{
			return _task->loop();
		}
};

#endif
