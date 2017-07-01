/** LocLogLev.h
 *
 *  Utility to pass a log level and a local level threshold to
 *  almost any logger, obtaining this behaviour:
 *
 *                   <--  _level  ==>  _level            [log generated]
 *  globalThreshold
 *                   <--  _level  ==>  globalThreshold   [log generated]
 *  _localThreshold
 *                   <--  _level  ==>  _level            [log canceled]
 *
 *  This allows to have different log level thresholds for different
 *  parts of a project, and for different kinds of logs. The result is
 *  that the logs can be more focused on specific aspects.
 *
 *  E.g.:
 *    LogLevel localThreshold = detail;
 *    log(warning) << "Standard log message";
 *    log(warning | localThreshold) << "Log message";
 *
 *
 *  Logger requirements:
 *   - Must accept either a numeric log level or an enum; in this case
 *     this file needs to be tailored to use this specific enum,  just
 *     substituting the current LogLevel one.
 *
 *  Tested with these loggers:
 *   - Trivial logger in the `LocLogLev_test.cpp` test file.
 *   - More to come...
 */

/* Copyright (C) 2017 Pietro Mele
 * License: BSD
 */

#ifndef LOCLOGLEV_H
#define LOCLOGLEV_H

// Specify log levels through either this or any other enumeration type
enum LogLevel { nolog = 0, verbose, detail, info, warning, error, critical, fatal };

static const LogLevel globalThreshold = warning;
//extern LogLevel globalThreshold;


/// Operator to combine a global and a local threshold

LogLevel operator|(LogLevel _level, LogLevel _localThreshold)
{
	if(_level >= globalThreshold)
		return _level;

	if(_level >= _localThreshold)
		return globalThreshold;

	return _level;
}

/// Functions in case levels are expressed as int values

LogLevel Level(int _level, int _localThreshold)
{
	if(_level >= globalThreshold)
		return LogLevel(_level);

	if(_level >= _localThreshold)
		return globalThreshold;

	return LogLevel(_level);
}


int ILevel(int _level, int _localThreshold)
{
	if(_level >= globalThreshold)
		return _level;

	if(_level >= _localThreshold)
		return globalThreshold;

	return _level;
}



#endif // LOCLOGLEV_H
