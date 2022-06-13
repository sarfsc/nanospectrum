/***********************************************************************************************************************
**
** Copyright (C) 2022 Evgeny Sinelnikov. <sin@altlinux.org>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#ifndef NANOSPECTRUM_COMMON_H
#define NANOSPECTRUM_COMMON_H

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
#define NANOSPECTRUM_SYMBOL_EXPORT __attribute__((__dllexport__))
#define NANOSPECTRUM_SYMBOL_IMPORT __attribute__((__dllimport__))
#else

#if defined (__LCC__)
#define NANOSPECTRUM_SYMBOL_EXPORT
#else
#define NANOSPECTRUM_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#endif

#define NANOSPECTRUM_SYMBOL_IMPORT
#endif

namespace nanospectrum {

}

#endif // NANOSPECTRUM_COMMON_H
