#ifndef __ZIPC_STUB_H__
#define __ZIPC_STUB_H__
#include <string.h>

/* ---- event buffer (replaces ZIPC runtime) ---- */
extern char ZMainEvent[256];

/* event check: compare current event string against a name */
#define ZNOTIFY_CHECK_EVENT(buf, name)  (strcmp((buf), (name)) == 0)

/* tracing macros -> no-ops (these were ZIPC simulation hooks) */
#define ZNOTIFY_STM_STATE_ENTRY(a,b,c)
#define ZNOTIFY_STM_STATE_NO(a,b,c)
#define ZNOTIFY_STM_STATE_EXIT(a,b,c)
#define ZNOTIFY_STM_ACTION_ENTRY(a,b,c)
#define ZNOTIFY_STM_EVENT_INIT(a,b)
#define ZNOTIFY_STM_EVENT_ENTRY(a,b,c)
#define ZNOTIFY_STM_EVENT_NO(a,b,c)

/* current state accessor (defined in harness) */
extern int zipc_current_state(void);

/* action capture: record which action fired this tick */
extern char g_last_action[64];
#define CAPTURE_ACTION(name) strncpy(g_last_action, name, 63)

#endif
