/* -*- Mode:C++; -*- */
/*
 * This is an example program for qlog, a small, Qt-based, thread-safe
 * logging library.
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

int main(int argc, char *argv[]) {
  QLOG_DEBUG("some debug information.");
  QLOG_INFO("some information.");
  QLOG_LOGIC("very logical indeed.");
  QLOG_WARNING("you've been warned.");
  QLOG_ERROR("an error. run for your life!");

  return 0;
}
