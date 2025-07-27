# ============================================================================
#  https://www.gnu.org/software/autoconf-archive/ax_append_compile_flags.html
# ============================================================================
#
# SYNOPSIS
#
#   AX_APPEND_COMPILE_FLAGS([FLAG1 FLAG2 ...], [FLAGS-VARIABLE], [EXTRA-FLAGS], [INPUT])
#
# DESCRIPTION
#
#   For every FLAG1, FLAG2 it is checked whether the compiler works with the
#   flag.  If it does, the flag is added FLAGS-VARIABLE
#
#   If FLAGS-VARIABLE is not specified, the current language's flags (e.g.
#   CFLAGS) is used.  During the check the flag is always added to the
#   current language's flags.
#
#   If EXTRA-FLAGS is defined, it is added to the current language's default
#   flags (e.g. CFLAGS) when the check is done.  The check is thus made with
#   the flags: "CFLAGS EXTRA-FLAGS FLAG".  This can for example be used to
#   force the compiler to issue an error when a bad flag is given.
#
#   INPUT gives an alternative input source to AC_COMPILE_IFELSE.
#
#   NOTE: This macro depends on the AX_APPEND_FLAG and
#   AX_CHECK_COMPILE_FLAG. Please keep this macro in sync with
#   AX_APPEND_LINK_FLAGS.
#
# LICENSE
#
#   Copyright (c) 2011 Maarten Bosmans <mkbosmans@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.  This file is offered as-is, without any
#   warranty.

##serial 7

AC_DEFUN([AX_APPEND_COMPILE_FLAGS],
[AX_REQUIRE_DEFINED([AX_CHECK_COMPILE_FLAG])
AX_REQUIRE_DEFINED([AX_APPEND_FLAG])
for flag in $1; do
  AX_CHECK_COMPILE_FLAG([$flag], [AX_APPEND_FLAG([$flag], [$2])], [], [$3], [$4])
done
])dnl AX_APPEND_COMPILE_FLAGS
# ===========================================================================
#      https://www.gnu.org/software/autoconf-archive/ax_append_flag.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_APPEND_FLAG(FLAG, [FLAGS-VARIABLE])
#
# DESCRIPTION
#
#   FLAG is appended to the FLAGS-VARIABLE shell variable, with a space
#   added in between.
#
#   If FLAGS-VARIABLE is not specified, the current language's flags (e.g.
#   CFLAGS) is used.  FLAGS-VARIABLE is not changed if it already contains
#   FLAG.  If FLAGS-VARIABLE is unset in the shell, it is set to exactly
#   FLAG.
#
#   NOTE: Implementation based on AX_CFLAGS_GCC_OPTION.
#
# LICENSE
#
#   Copyright (c) 2008 Guido U. Draheim <guidod@gmx.de>
#   Copyright (c) 2011 Maarten Bosmans <mkbosmans@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.  This file is offered as-is, without any
#   warranty.

##serial 8

AC_DEFUN([AX_APPEND_FLAG],
[dnl
AC_PREREQ(2.64)dnl for _AC_LANG_PREFIX and AS_VAR_SET_IF
AS_VAR_PUSHDEF([FLAGS], [m4_default($2,_AC_LANG_PREFIX[FLAGS])])
AS_VAR_SET_IF(FLAGS,[
  AS_CASE([" AS_VAR_GET(FLAGS) "],
    [*" $1 "*], [AC_RUN_LOG([: FLAGS already contains $1])],
    [
     AS_VAR_APPEND(FLAGS,[" $1"])
     AC_RUN_LOG([: FLAGS="$FLAGS"])
    ])
  ],
  [
  AS_VAR_SET(FLAGS,[$1])
  AC_RUN_LOG([: FLAGS="$FLAGS"])
  ])
AS_VAR_POPDEF([FLAGS])dnl
])dnl AX_APPEND_FLAG
# ===========================================================================
#  https://www.gnu.org/software/autoconf-archive/ax_check_compile_flag.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_CHECK_COMPILE_FLAG(FLAG, [ACTION-SUCCESS], [ACTION-FAILURE], [EXTRA-FLAGS], [INPUT])
#
# DESCRIPTION
#
#   Check whether the given FLAG works with the current language's compiler
#   or gives an error.  (Warnings, however, are ignored)
#
#   ACTION-SUCCESS/ACTION-FAILURE are shell commands to execute on
#   success/failure.
#
#   If EXTRA-FLAGS is defined, it is added to the current language's default
#   flags (e.g. CFLAGS) when the check is done.  The check is thus made with
#   the flags: "CFLAGS EXTRA-FLAGS FLAG".  This can for example be used to
#   force the compiler to issue an error when a bad flag is given.
#
#   INPUT gives an alternative input source to AC_COMPILE_IFELSE.
#
#   NOTE: Implementation based on AX_CFLAGS_GCC_OPTION. Please keep this
#   macro in sync with AX_CHECK_{PREPROC,LINK}_FLAG.
#
# LICENSE
#
#   Copyright (c) 2008 Guido U. Draheim <guidod@gmx.de>
#   Copyright (c) 2011 Maarten Bosmans <mkbosmans@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.  This file is offered as-is, without any
#   warranty.

##serial 11

AC_DEFUN([AX_CHECK_COMPILE_FLAG],
[AC_PREREQ(2.64)dnl for _AC_LANG_PREFIX and AS_VAR_IF
AS_VAR_PUSHDEF([CACHEVAR],[ax_cv_check_[]_AC_LANG_ABBREV[]flags_$4_$1])dnl
AC_CACHE_CHECK([whether the _AC_LANG compiler accepts $1], CACHEVAR, [
  ax_check_save_flags=$[]_AC_LANG_PREFIX[]FLAGS
  if test x"m4_case(_AC_LANG,
                     [C], [$GCC],
                     [C++], [$GXX],
                     [Fortran], [$GFC],
                     [Fortran 77], [$G77],
                     [Objective C], [$GOBJC],
                     [Objective C++], [$GOBJCXX],
                     [no])" = xyes ; then
    add_gnu_werror="-Werror"
  fi
  _AC_LANG_PREFIX[]FLAGS="$[]_AC_LANG_PREFIX[]FLAGS $4 $1 $add_gnu_werror"
  AC_COMPILE_IFELSE([m4_default([$5],[AC_LANG_PROGRAM()])],
    [AS_VAR_SET(CACHEVAR,[yes])],
    [AS_VAR_SET(CACHEVAR,[no])])
  _AC_LANG_PREFIX[]FLAGS=$ax_check_save_flags])
AS_VAR_IF(CACHEVAR,yes,
  [m4_default([$2], :)],
  [m4_default([$3], :)])
AS_VAR_POPDEF([CACHEVAR])dnl
])dnl AX_CHECK_COMPILE_FLAGS
# ===========================================================================
#    https://www.gnu.org/software/autoconf-archive/ax_require_defined.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_REQUIRE_DEFINED(MACRO)
#
# DESCRIPTION
#
#   AX_REQUIRE_DEFINED is a simple helper for making sure other macros have
#   been defined and thus are available for use.  This avoids random issues
#   where a macro isn't expanded.  Instead the configure script emits a
#   non-fatal:
#
#     ./configure: line 1673: AX_CFLAGS_WARN_ALL: command not found
#
#   It's like AC_REQUIRE except it doesn't expand the required macro.
#
#   Here's an example:
#
#     AX_REQUIRE_DEFINED([AX_CHECK_LINK_FLAG])
#
# LICENSE
#
#   Copyright (c) 2014 Mike Frysinger <vapier@gentoo.org>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

##serial 2

AC_DEFUN([AX_REQUIRE_DEFINED], [dnl
  m4_ifndef([$1], [m4_fatal([macro ]$1[ is not defined; is a m4 file missing?])])
])dnl AX_REQUIRE_DEFINED
