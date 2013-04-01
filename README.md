qlog
====

qlog is a small Qt-based, thread-safe logging library. It defines a
few macros to log your messages at different levels, and other macros
to globally or selectively turn on/off logging.

At the moment it's so small that I suggest, if you want to use it, to
grab the files and throw them in your project.

Obviously this might not be a good choice for large and complex
projects, but if you want something small to use in your throwaway
program, and you want it to accept QStrings and have a name with a "q"
at the beginning, this is a good choice for you.

Oh, and qlog is distributed under GPLv3. Just saying!

Have fun!

# qlog macros

The following macros can be used to log something passed as a QString:

 - QLOG_DEBUG(msg)
 - QLOG_INFO(msg)
 - QLOG_LOGIC(msg)
 - QLOG_WARNING(msg)
 - QLOG_ERROR(msg)

There are also the following macros which also get a QString, but are
intended for logging function/method calls and their parameter is
intended to contain the argument list:

 - QLOG_FUNCTION_PARAMS(params)
 - QLOG_METHOD_PARAMS(params)

The following two methods are equivalents to the two above, only they
don't get an argument.

 - QLOG_FUNCTION
 - QLOG_METHOD

All four macros add the name of the function/method at the beginning
of the message.

The following macros determine how qlog behaves:

 - ENABLE_LOGGING: If not defined nothing is logged. The logging
   macros are defined as empty, so using them will cause no
   performance loss.

 - DISABLE_THREAD_SAFE_LOGGING: Disables synchronization. This might
   be helpful when you want to stop the locks from causing strange
   situations involving concurrency.

 - DISABLE_DEBUG_LOGS, DISABLE_FUNCTION_LOGS, DISABLE_LOGIC_LOGS,
   DISABLE_INFO_LOGS, DISABLE_WARNING_LOGS, DISABLE_ERROR_LOGS: These
   can be used to disable certain levels of logging selectively.

# formatting

The following macros can be used to format qlog's output:

  - QLOG_SET_DATETIME_FORMAT(QString format)

    Sets the date-time format to use. Anything acceptable to
    QDateTime::toString can be used.

  - QLOG_SET_DEBUG_FORMAT(QString format) and friends

    Sets the format of messages logged at the 'debug' level. %1 is
    replaced with the date-time, and %2 with the logged message
    itself. Similar macros exist for all other logging levels except
    for the function/method level: QLOG_SET_LOGIC_FORMAT,
    QLOG_SET_INFO_FORMAT, QLOG_SET_WARNING_FORMAT,
    QLOG_SET_ERROR_FORMAT.

  - QLOG_SET_FUNCTION_FORMAT(QString format)

    Sets the format of messages logged at the 'function' level. %1 is
    replaced with the date-time, %2 with the name of the class (in
    case of methods), %3 with the function name and and %4 with
    whatever has been passed as the logged message which, by
    convention, is the list of arguments to the function/method.
