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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "leb.h"
#include "bix.h"
/*
 */
typedef enum proc_kind {
    proc_unk = 0,
    proc_enc = 1,
    proc_dec = 2,
    proc_cnt = 4
} proc_kind;
/*
 */
proc_kind proc_decode(char* arg){
    if (0 == strcmp("enc",arg)){

        return proc_enc;
    }
    else if (0 == strcmp("dec",arg)){

        return proc_dec;
    }
    else if (0 == strcmp("cnt",arg)){

        return proc_cnt;
    }
    else {
        return proc_unk;
    }
}
/*
 */
int usage(char* pn){
    fprintf(stderr,"usage\n\t%s (enc|dec|cnt) <hexbits>\n\ndescription\n\n\tTest LEB functions.\n\n",pn);
    return 1;
}
int main_dec(bix* bin){
    if (null != bin){
        leb* li = leb_decode(bin->content,bin->size);
        if (null != li){
            fprintf(stdout,"%lx\n",li->value);
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
int main_enc(bix* bin){
    if (null != bin){
        bix *hex = bix_encode(bin->content,bin->size);
        if (null != hex){
            fwrite(hex->content,1,hex->size,stdout);
            putc('\n',stdout);
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
int main_cnt(bix* bin){
    if (null != bin){
        leb* li = leb_decode(bin->content,bin->size);
        if (null != li){
            fprintf(stdout,"%zu\n",li->count);
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
/*
 */
int main(int argc, char** argv){
    char* pn = argv[0];

    if (3 == argc){
        proc_kind proc = proc_decode(argv[1]);
        char *hex = argv[2];

        bix *bin = bix_decode(hex,bix_count(hex,strlen(hex)));
        if (null != bin){
            switch(proc){
            case proc_dec:
                return main_dec(bin);
            case proc_enc:
                return main_enc(bin);
            case proc_cnt:
                return main_cnt(bin);

            default:
                return usage(pn);
            }
        }
        else {
            fprintf(stderr,"%s error: unrecognized <hex> input.\n",pn);
            return 1;
        }
    }
    else {
        return usage(pn);
    }
}
