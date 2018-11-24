#include "TaskManager.h"
#include <Arduino.h>

TaskManager::~TaskManager()
{
	clear();
}

void TaskManager::add(Task *task, mtime_t delay, bool delete_when_done)
{
	// Create wrapper for task
	TaskWrapper *wrapper = new TaskWrapper(task, millis(), delay, delete_when_done);

	// Check if the manager has already some other tasks
	if (_tasks != nullptr)
	{
		// If yes, just add the task to the manager
		wrapper->next = _tasks;
		_tasks->prev = wrapper;
		_tasks = wrapper;
	}
	else
	{
		// If the manager is empty, the wrapper will be the first (and only) element of the manager.
		_tasks = wrapper;
	}
}

void TaskManager::clear()
{
	// Process manager and delete all objects
	while (_tasks != nullptr)
	{
		// Delete wrapper object and move on to next task
		// This will automatically delete the wrapped object, if required
		TaskWrapper *next = _tasks->next;
		delete _tasks;
		_tasks = next;
	}
}

void TaskManager::loop()
{
	mtime_t const now = millis();

	for (TaskWrapper *ptr = _tasks; ptr != nullptr; )
	{
		// If task has not been started yet, try to start it
		// The method start() will return false if the task is delayed
		if (!ptr->hasStarted() && !ptr->start(now))
		{
			// Proceed with next task
			ptr = ptr->next;
			continue;
		}

		// Execute current task; loop() will return false when the task is done
		if (!ptr->loop())
		{
			// Delete wrapper object and move on to next task
			// This will automatically delete the wrapped object, if required

			// First update the references of the previous and next tasks in the collection
			if (ptr->prev != nullptr)
				ptr->prev->next = ptr->next;
			if (ptr->next != nullptr)
				ptr->next->prev = ptr->prev;
			// Special case:
			// If this was the first task in the collection, we also need to update the collection pointer
			if (_tasks == ptr)
				_tasks = ptr->next;

			// Move `ptr` to the next task, and destroy the current task
			TaskWrapper *newptr = ptr->next;
			delete ptr;
			ptr = newptr;
		}
		else
		{
			// Current task was executed and is not done yet (so no need to delete)
			// Proceed with next task
			ptr = ptr->next;
		}
	}
}
