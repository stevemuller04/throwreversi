#ifndef INCLUDE_SRC_TASK_TASKMANAGER_H
#define INCLUDE_SRC_TASK_TASKMANAGER_H

#include "Task.h"
#include "TaskWrapper.h"

/**
 * Represents a manager for tasks that are executed one after another.
 */
class TaskManager
{
	private:
		TaskWrapper *_tasks = nullptr;

	public:
		/**
		 * Adds the given task to the manager.
		 * It will be executed after the given delay.
		 * @param task - The task to be added to the manager.
		 * @param delay - An additional delay after which the task will be executed.
		 * @param delete_when_done - If true, the given task will be deleted (and its memory freed) when the task has finished.
		 */
		void add(Task* task, mtime_t delay, bool delete_when_done);

		/**
		 * Removes all running and scheduled tasks from this task manager.
		 * In particular, any on-going tasks will be aborted.
		 */
		void clear();

		/**
		 * Loop method that must be continuously called so as to execute the tasks.
		 * This method will call the respective loop() method of the tasks.
		 */
		void loop();
};

#endif
