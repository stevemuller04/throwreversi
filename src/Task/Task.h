#ifndef INCLUDE_SRC_TASK_TASK_H
#define INCLUDE_SRC_TASK_TASK_H

/**
 * Represents a task that can be executed.
 */
class Task
{
	public:
		/**
		 * This method must be called when the task is about to be executed, before calling loop().
		 */
		virtual void setup() = 0;

		/**
		 * Executes the next instruction of the task.
		 * This method must be continuously called to execute the task completely.
		 * @return - Returns true when the loop method shall be called again. Returns false when the task has finished.
		 */
		virtual bool loop() = 0;
};

#endif
