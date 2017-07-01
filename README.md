# LocLogLev

Utility to be used with a logger (basically any logger) to modify the way
log levels are treated.

Normally, if the log level is below the threshold, the log is discarded,
and the threshold is a value common to all the logs.

This allows to filter the logs on the basis of their priority:

```
                   <--  _level        [log generated]
  globalThreshold
                   <--  _level        [log discarded]
```

`LocLogLev` allows to have multiple threshold levels, so that it is possible
to tune the behaviour of the logger in a finer way:

```
                   <--  _level  ==>  _level            [log generated]
  globalThreshold
                   <--  _level  ==>  globalThreshold   [log generated]
  _localThreshold
                   <--  _level  ==>  _level            [log discarded]
```

So, in the standard case, the logs can be filtered in a uniform way, only.
With `LocLogLev` they can be filtered on the basis of multiple different
criteria.

E.g.: assuming we are using a generic logger `log`:

```C++
	log.SetThreshold(warning);    // set global threshold

	// Standard behaviour:
	log(detail)  << "Log discarded";
	log(warning) << "Log generated";

	// LocLogLev:
	LogLevel threshold1 = detail,
	         threshold2 = error;
	log(detail  | threshold1) << "Log generated";
	log(warning | threshold1) << "Log generated";
	log(detail  | threshold2) << "Log discarded";
	log(warning | threshold2) << "Log generated";
```

So, `LocLogLev` allows to localize the threshold in different parts of the
project, providing a greater level of log detail only where needed.

It is also possible to mix different threshold levels in the same areas of
the code, typically for different kinds of logs, allowing to tune the level
of detail on a "subject" basis.

All this to generate a smaller, more focused log file, useful in case of an
otherwise huge one, or when particular hardware is used (SSD, ramdisk, remote
destination), and in performance critical systems, where logs may be needed in
production code but their performance hit must be minimized.

This is achieved by the simple `operator|`, defined for the LogLevel enumeration.
Dealing with a generic logger, it is easy to customize it to the specific log
levels used, or if using integer values, the Level(int, int) function can be
used.


