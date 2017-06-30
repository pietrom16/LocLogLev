# LocLogLev

Utility to be used with a logger (basically any logger) to modify the way
log levels are treated.

Normally, if the log level is below the threshold, the log is discarded.
The threshold is a value common to all the logs.

This allows to filter the logs on the basis of their priority:

```
                   <--  _level        [log generated]
  globalThreshold
                   <--  _level        [log discarded]
```

`LocLogLev` allows to have multiple threshold levels, so that it is possible
tune the behaviour of the logger in a more flexible way:

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
	log.SetThreshold(warning);

	// Standard case:
	log(detail)  << "Discarded log message";
	log(warning) << "Generated log message";

	// LocLogLev:
	LogLevel threshold1 = detail,
	         threshold2 = error;
	log(detail  | threshold1) << "Generated log message";
	log(warning | threshold1) << "Generated log message";
```

