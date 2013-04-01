/* -*- Mode:C++; -*- */
/*
 * This is a small Qt-based, thread-safe logging library.
 *
 * Copyright 2011 Mostafa Razavi <mostafa@sepent.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _QLOG_HH__
#define _QLOG_HH__

#include <QString>
#include <QMutex>

#include <typeinfo>

namespace qlog {

enum LogLevel {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_FUNCTION,
  LOG_LEVEL_LOGIC,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_ERROR
};

/**
 * An instance of this class can be obtained by calling the instance()
 * method and used for logging.
 *
 * Logging is by default thread-safe. Thread-safety is achieved
 * through the use of locks. Locks however can sometimes affect the
 * way a concurrent program works and might interfere with debugging
 * (which can defeat the purpose of logging itself). This is why locks
 * can be turned off (by defining a DISABLE_THREAD_SAFE_LOGGING
 * macro).
 */
class GlobalLog {
protected:
  static GlobalLog* singleInstance;
  static QMutex globalLogMutex;

  QString DateTimeFormat;
  QString DebugMsgFormat;
  QString FunctionMsgFormat;
  QString LogicMsgFormat;
  QString InfoMsgFormat;
  QString WarningMsgFormat;
  QString ErrorMsgFormat;

  GlobalLog() :
    DateTimeFormat("yyyy-MM-dd HH:mm:ss.zzz"),
    DebugMsgFormat("[DEBUG][%1] %2"),
    FunctionMsgFormat("[FUNCTION][%1] %2%3(%4)"),
    LogicMsgFormat("[LOGIC][%1] %2"),
    InfoMsgFormat("[INFO][%1] %2"),
    WarningMsgFormat("[WARNING][%1] %2"),
    ErrorMsgFormat("[ERROR][%1] %2")
  {}

public:
  /**
   * Returns the single instance of this class (creating it if it's
   * the first time).
   */
  static GlobalLog* instance() {
    if (GlobalLog::singleInstance == NULL)
      GlobalLog::singleInstance = new GlobalLog;
    return GlobalLog::singleInstance;
  }

  /**
   * Logs 'msg' at level 'level'.
   */
  void log(LogLevel level, QString msg);

  /**
   * Logs 'msg' at level 'debug'.
   */
  void logDebug(QString msg);

  /**
   * Logs the use of the specified function (or method, if className
   * is not empty).
   */
  void logFunction(QString className, QString function);

  /**
   * Logs the use of the specified function (or method, if className
   * is not empty). 'params' is displayed in front of the function
   * name and is intended to contain a representation of the functions
   * argument list.
   */
  void logFunction(
    QString className, QString function, QString params);

  /**
   * Logs 'msg' at level 'logic'.
   */
  void logLogic(QString msg);

  /**
   * Logs 'msg' at level 'info'.
   */
  void logInfo(QString msg);

  /**
   * Logs 'msg' at level 'warning'.
   */
  void logWarning(QString msg);

  /**
   * Logs 'msg' at level 'error'.
   */
  void logError(QString msg);

  /**
   * Sets the format of the date-times in the logged messages.
   * Anything acceptable to QDateTime::toString can be used.
   */
  void setDateTimeFormat(QString format);

  /**
   * Sets the format of messages logged at the 'debug' level. %1 is
   * replaced with the date-time, and %2 with the logged message
   * itself.
   */
  void setDebugMsgFormat(QString format);

  /**
   * Sets the format of messages logged at the 'function' level. %1 is
   * replaced with the date-time, %2 with the name of the class (in
   * case of methods), %3 with the function name and and %4 with
   * whatever has been passed as the logged message which, by
   * convention, is the list of arguments to the method.
   */
  void setFunctionMsgFormat(QString format);

  /**
   * Sets the format of messages logged at the 'logic' level. %1 is
   * replaced with the date-time, and %2 with the logged message
   * itself.
   */
  void setLogicMsgFormat(QString format);

  /**
   * Sets the format of messages logged at the 'info' level. %1 is
   * replaced with the date-time, and %2 with the logged message
   * itself.
   */
  void setInfoMsgFormat(QString format);

  /**
  * Sets the format of messages logged at the 'warning' level. %1 is
   * replaced with the date-time, and %2 with the logged message
   * itself.
   */
  void setWarningMsgFormat(QString format);

  /**
   * Sets the format of messages logged at the 'error' level. %1 is
   * replaced with the date-time, and %2 with the logged message
   * itself.
   */
  void setErrorMsgFormat(QString format);
};

} // namespace qlog

#ifndef ENABLE_LOGGING
#define QLOG_DEBUG(msg)
#define QLOG_FUNCTION
#define QLOG_FUNCTION_PARAMS(params)
#define QLOG_METHOD
#define QLOG_METHOD_PARAMS(params)
#define QLOG_INFO(msg)
#define QLOG_LOGIC(msg)
#define QLOG_WARNING(msg)
#define QLOG_ERROR(msg)
#endif // ifndef ENABLE_LOGGING

// enable the ability to turn on/off synchronization code (this might
// be helpful in order to stop the locks from meddling with strange
// situations involving concurrency)
#ifdef DISABLE_THREAD_SAFE_LOGGING
#define LOCK_GLOBAL_LOG
#endif // ifdef DISABLE_THREAD_SAFE_LOGGING
#ifndef DISABLE_THREAD_SAFE_LOGGING
#define LOCK_GLOBAL_LOG QMutexLocker locker(&globalLogMutex);
#endif // ifndef DISABLE_THREAD_SAFE_LOGGING

#ifdef ENABLE_LOGGING

// define __FUNCTION__ as an empty string if it is not supported by the
// compiler
#if !defined(__FUNCTION__) && !defined(__GNUC__)
#define __FUNCTION__ ""
#endif //!defined(__FUNCTION__) && !defined(__GNUC__)

#ifndef DISABLE_DEBUG_LOGS
#define QLOG_DEBUG(msg) \
  qlog::GlobalLog::instance()->logDebug(msg)
#else
#define QLOG_DEBUG(msg)
#endif

#ifndef DISABLE_FUNCTION_LOGS
#define QLOG_FUNCTION \
  qlog::GlobalLog::instance()->logFunction("", __FUNCTION__)

#define QLOG_FUNCTION_PARAMS(params) \
  qlog::GlobalLog::instance()->logFunction( \
    "", __FUNCTION__, params)

#define QLOG_METHOD \
  qlog::GlobalLog::instance()->logFunction( \
    typeid(*this).name(), __FUNCTION__)

#define QLOG_METHOD_PARAMS(params) \
  qlog::GlobalLog::instance()->logFunction( \
    typeid(*this).name(), __FUNCTION__, params)
#else

#define QLOG_FUNCTION
#define QLOG_FUNCTION_PARAMS(params)
#define QLOG_METHOD
#define QLOG_METHOD_PARAMS(params)

#endif

#ifndef DISABLE_LOGIC_LOGS
#define QLOG_LOGIC(msg) \
  qlog::GlobalLog::instance()->logLogic(msg)
#else
#define QLOG_LOGIC(msg)
#endif

#ifndef DISABLE_INFO_LOGS
#define QLOG_INFO(msg) \
  qlog::GlobalLog::instance()->logInfo(msg)
#else
#define QLOG_INFO(msg)
#endif

#ifndef DISABLE_WARNING_LOGS
#define QLOG_WARNING(msg) \
  qlog::GlobalLog::instance()->logWarning(msg)
#else
#define QLOG_WARNING(msg)
#endif

#ifndef DISABLE_ERROR_LOGS
#define QLOG_ERROR(msg) \
  qlog::GlobalLog::instance()->logError(msg)
#else
#define QLOG_ERROR(msg)
#endif

#endif // ifdef ENABLE_LOGGING

#define QLOG_SET_DATETIME_FORMAT(format) \
  qlog::GlobalLog::instance()->setDateTimeFormat(format)
#define QLOG_SET_DEBUG_FORMAT(format) \
  qlog::GlobalLog::instance()->setDebugMsgFormat(format)
#define QLOG_SET_LOGIC_FORMAT(format) \
  qlog::GlobalLog::instance()->setLogicMsgFormat(format)
#define QLOG_SET_FUNCTION_FORMAT(format) \
  qlog::GlobalLog::instance()->setFunctionMsgFormat(format)
#define QLOG_SET_INFO_FORMAT(format) \
  qlog::GlobalLog::instance()->setInfoMsgFormat(format)
#define QLOG_SET_WARNING_FORMAT(format) \
  qlog::GlobalLog::instance()->setWarningMsgFormat(format)
#define QLOG_SET_ERROR_FORMAT(format) \
  qlog::GlobalLog::instance()->setErrorMsgFormat(format)

#endif /* _QLOG_HH__ */
