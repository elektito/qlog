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

#include "qlog.hh"

#include <cxxabi.h>
#include <stdio.h>

#include <QDateTime>
#include <QMutexLocker>

namespace qlog {

GlobalLog* GlobalLog::singleInstance = NULL;
QMutex GlobalLog::globalLogMutex;

void GlobalLog::log(LogLevel level, QString msg) {
  switch (level) {
  case LOG_LEVEL_DEBUG:
    this->logDebug(msg);
    break;
  case LOG_LEVEL_FUNCTION:
    this->logFunction("", "NO_FUNCTION_NAME", msg);
    break;
  case LOG_LEVEL_LOGIC:
    this->logLogic(msg);
    break;
  case LOG_LEVEL_INFO:
    this->logInfo(msg);
    break;
  case LOG_LEVEL_WARNING:
    this->logWarning(msg);
    break;
  case LOG_LEVEL_ERROR:
    this->logError(msg);
    break;
  }
}

void GlobalLog::logDebug(QString msg) {
  QString formatted = this->DebugMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    msg);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logFunction(QString className, QString function)
{
  if (className != "") {
    size_t bufLen = 256;
    char demangledName[bufLen];
    int status;
    abi::__cxa_demangle(className.toAscii().constData(), demangledName, &bufLen, &status);
    className = QString(QByteArray(demangledName, bufLen)) + "::";
  }

  QString formatted = this->FunctionMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    className,
    function,
    "");

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logFunction(
  QString className, QString function, QString params)
{
  if (className != "") {
    size_t bufLen = 256;
    char demangledName[bufLen];
    int status;
    abi::__cxa_demangle(className.toAscii().constData(), demangledName, &bufLen, &status);
    className = QString(QByteArray(demangledName, bufLen)) + "::";
  }

  QString formatted = this->FunctionMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    className,
    function,
    params);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logLogic(QString msg) {
  QString formatted = this->LogicMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    msg);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logInfo(QString msg) {
  QString formatted = this->InfoMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    msg);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logWarning(QString msg) {
  QString formatted = this->WarningMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    msg);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::logError(QString msg) {
  QString formatted = this->ErrorMsgFormat.arg(
    QDateTime::currentDateTime().toString(DateTimeFormat),
    msg);

  LOCK_GLOBAL_LOG;
  printf("%s\n", formatted.toLocal8Bit().constData());
}

void GlobalLog::setDateTimeFormat(QString format) {
  this->DateTimeFormat = format;
}

void GlobalLog::setDebugMsgFormat(QString format) {
  this->DebugMsgFormat = format;
}

void GlobalLog::setFunctionMsgFormat(QString format) {
  this->FunctionMsgFormat = format;
}

void GlobalLog::setLogicMsgFormat(QString format) {
  this->LogicMsgFormat = format;
}

void GlobalLog::setInfoMsgFormat(QString format) {
  this->InfoMsgFormat = format;
}

void GlobalLog::setWarningMsgFormat(QString format) {
  this->WarningMsgFormat = format;
}

void GlobalLog::setErrorMsgFormat(QString format) {
  this->ErrorMsgFormat = format;
}

} // namespace qlog
