/* Copyright (C) 2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#include <not-cancel.h>


DIR *
fdopendir (int fd)
{
  struct stat64 statbuf;

  if (__builtin_expect (__fxstat64 (_STAT_VER, fd, &statbuf), 0) < 0)
    goto out;
  if (__builtin_expect (! S_ISDIR (statbuf.st_mode), 0))
    {
      __set_errno (ENOTDIR);
    out:
      close_not_cancel_no_status (fd);
      return NULL;
    }

  return __alloc_dir (fd, &statbuf);
}