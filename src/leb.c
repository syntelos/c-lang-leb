/*
 * Syntelos LEB
 * Copyright (C) 2022, John Pritchard, Syntelos
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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include "leb.h"
/*
 */
leb* leb_decode( void* source, size_t length){
    off_t count = 0;
    uint64_t value = 0;
    if (null != source && 0 < length){
        uint8_t *sp = source;
        uint8_t shift = 0;
        off_t index;
        for (index = 0; index < length; index++){
            uint8_t sourceb = *sp;
            bool_t continuation = (sourceb & 0x80);
            uint64_t content = (sourceb & 0x7F);
            value |= (content << shift);
            count += 1;

            if (continuation){
                shift += 7;
                if (56 < shift){
                    break;
                }
                else {
                    sp += 1;
                }
            }
            else {
                break;
            }
        }
    }

    leb *r = calloc(1,sizeof(leb));
    if (null != r){
        r->count = count;
        r->value = value; // be_to_he performed by CPL [CC code generator]
    }
    return r;
}
/*
 */
off_t leb_encode( uint64_t source, void* target, size_t length){
    uint8_t *tp = target;
    if (0 == source){
        *tp = 0;

        return 1;
    }
    else {
        /*
         * This encoder performs a bit count which it
         * employs as production control.  This method has
         * greater complexity than practical alternatives,
         * benefiting the return result structure.
         */
        off_t count = leb_length(source);
        off_t terminal = (count-1);
        off_t index;

        for (index = 0; index < count; index++){

            uint8_t octet = (source & 0x7F);
            source >>= 7;
            if (index < terminal){

                octet |= 0x80;
            }

            *tp++ = octet;
        }
        return count;
    }
}
/*
 */
void leb_destroy(leb* r){
    if (null != r){
        memset(r,0,sizeof(leb));
        free(r);
    }
}
/*
 */
uint8_t leb_length(uint64_t value){
    if (0 == value){
        return 1;
    }
    else {
        uint8_t count = 8;
        uint8_t shift = 56;
        while (0 != shift){

            if (0 == ((value >> shift) & 0xFF)){

                count -= 1;
                shift -= 8;
            }
            else {
                break;
            }
        }
        return count;
    }
}
