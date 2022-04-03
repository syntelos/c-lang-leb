/*
 * Syntelos LEB
 * Copyright (C) 2021, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _syntelos_leb_h
#define _syntelos_leb_h

#include "bint.h"
/*
 *
 */
typedef struct leb {

    off_t count;

    uint64_t value;

} leb;
/*
 * Decode from byte buffer.
 */
leb* leb_decode(char*,size_t);
/*
 * Encode to byte buffer.
 */
off_t leb_encode(uint64_t,char*,size_t);
/*
 * Clean and free memory.
 */
void leb_destroy(leb*);
/*
 * Count content octets in argument.
 */
uint8_t leb_length(uint64_t);

#endif
