#include <errno.h>

#ifndef _GUILIB_SYSLOG_H
#define _GUILIB_SYSLOG_H

#define GUILIB_LOG_INFO   1
#define GUILIB_LOG_ERROR  2

/**
 * Opens a log on GNU/Linux systems.
 *
 * @param ident is some arbitrary identifier string specified by GNU libc.
 */

void guilib_openlog(const char *ident);

/**
 * Write an error message to the syslog.
 *
 * @param level is the priority for the syslog message
 * @param tag is the identifier used to write to the syslog.
 * @param format is the formatted string to write to the syslog.
 */
void guilib_syslog(int level, const char *format, ...) __attribute__ ((format(printf, 2, 3)));

#endif
