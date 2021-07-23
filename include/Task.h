/*
 * Task.h
 *
 *  Created on: Jul 19, 2021
 *      Author: becomingguru
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
private:

public:
	virtual void run() = 0;

	virtual ~Task(){}
};

#endif /* TASK_H_ */
