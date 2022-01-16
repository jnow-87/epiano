#ifndef TASK_H
#define TASK_H


#include <stddef.h>


/* incomplete types */
struct task_t;


/* types */
typedef void (*task_hdlr_t)(struct task_t *task);

typedef struct task_t{
	struct task_t *prev,
				  *next;

	task_hdlr_t hdlr;
	float period_ms;
	size_t ticks;
} task_t;


/* prototypes */
void task_init(void);

task_t *task_issue(task_hdlr_t hdlr, float period_ms);
void task_terminate(task_t *task);

void task_update_period(task_t *task, float period_ms);


#endif // TASK_H
