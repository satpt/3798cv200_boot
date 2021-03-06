#ifndef __IR_UTILS_H__
#define __IR_UTILS_H__
#include <stdarg.h>

#define KERN_WARNING
#define KERN_ERR
#define KERN_NOTICE
#define KERN_DEBUG

#define hiir_error HI_ERR_IR

#ifdef HIIR_DEBUG
void hiir_debug(char *fmt, ...);
void hiir_info(char *fmt, ...);
void ir_set_dbg(int on);
void ir_set_info(int on);
#else 
#define hiir_debug(fmt...)
#define hiir_info(fmt...)
#endif

#define wake_up_interruptible(...)	do { } while (0)
#define init_waitqueue_head(x) do{}while(0)


/* module */
#define THIS_MODULE		0
#define try_module_get(...)	1
#define module_put(...)		do { } while (0)
#define module_init(...)
#define module_exit(...)
#define EXPORT_SYMBOL(...)
#define EXPORT_SYMBOL_GPL(...)
#define module_param_call(...)
#define MODULE_PARM_DESC(...)
#define MODULE_VERSION(...)
#define MODULE_DESCRIPTION(...)
#define MODULE_AUTHOR(...)

void ir_insert_key_tail(struct ir_buffer *head, struct key_attr *key);
struct key_attr *ir_first_write_key(struct ir_buffer *head);
struct key_attr *ir_first_read_key(struct ir_buffer *head);
struct key_attr *ir_get_write_key_n(struct ir_buffer *head, u32 n);
struct key_attr *ir_get_prev_write_key(struct ir_buffer *head);
struct key_attr *ir_get_read_key_n(struct ir_buffer *head, u32 n);
struct key_attr *ir_next_reader_clr_inc(struct ir_buffer *head);
struct key_attr *ir_reader_inc(struct ir_buffer *head);
/* return 1 while d is in [min, max] */
static inline int data_fallin(u32 d, u32 min, u32 max)
{
	return (d >= min && d <= max);
}
#define TO_STR(is_pulse)	((is_pulse) ? "pulse" : "space")
static inline int geq_margin(u32 d1, u32 d2, u32 margin)
{
	return d1 > (d2 - margin);
}

static inline int eq_margin(u32 d1, u32 d2, u32 margin)
{
	return ((d1 > (d2 - margin)) && (d1 < (d2 + margin)));
}
struct ir_signal {
	unsigned int duration;
	unsigned int  pulse;          //1:pulse  0:space
};
static inline u32 is_transition(struct ir_signal *x, struct ir_signal *y)
{
	return x->pulse != y->pulse;
}

static inline void decrease_duration(struct ir_signal *signal, u32 duration)
{
	if (duration > signal->duration)
		signal->duration = 0;
	else
		signal->duration -= duration;
}
#endif
