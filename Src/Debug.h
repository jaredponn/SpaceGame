#pragma once

/** Debug.h
 * This includes the macro named "GLOBAL_LOGGER_BOOL", where if it is defined,
 * it will compile the logger. Without it defined, logging functionality will
 * not be included in the final binary. In addition, it includes the global
 * logging level. Setting it to 0 means it will log everything. Setting it to 1
 * will only diplay things 1 and lower. So the lower the number, the more
 * important logging is it
 */

#define GLOBAL_LOGGER_BOOL TRUE

#ifdef GLOBAL_LOGGER_BOOL
static unsigned int LOG_LEVEL = 0;
#endif
