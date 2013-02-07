qlog
====

qlog is a small Qt-based, thread-safe logging library. It defines a
few macros to log your messages at different levels, and other macros
to globally or selectively turn on/off logging.

At the moment it's so small that I suggest, if you want to use it, to
grab the files and throw them in your project.

Obviously this might not be a good choice for large and complex
projects, but if you want something small to use in your throwaway
program, and you want it to accept QStrings and have a name with the
"q" at the beginning, this is a good choice for your.

Have fun!

# qlog macros

The following macros can be used to log something passed as a QString:

 - LOG_DEBUG(msg)
 - LOG_INFO(msg)
 - LOG_LOGIC(msg)
 - LOG_WARNING(msg)
 - LOG_ERROR(msg)

There are also the following macros which also get a QString, but are
intended for logging function/method calls and their parameter is
intended to contain the argument list:

 - LOG_FUNCTION_PARAMS(params)
 - LOG_METHOD_PARAMS(params)

The following two methods are equivalents to the two above, only they
don't get an argument.

 - LOG_FUNCTION
 - LOG_METHOD

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
