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
    proc_cnt = 3,
    proc_val = 4
} proc_kind;
/*
 */
proc_kind proc_decode(char* arg){
    switch(*arg){
    case 'c':
        if (0 == strcmp("cnt",arg)){

            return proc_cnt;
        }
        else {
            return proc_unk;
        }
    case 'd':
        if (0 == strcmp("dec",arg)){

            return proc_dec;
        }
        else {
            return proc_unk;
        }
    case 'e':
        if (0 == strcmp("enc",arg)){

            return proc_enc;
        }
        else {
            return proc_unk;
        }
    case 'v':
        if (0 == strcmp("val",arg)){

            return proc_val;
        }
        else {
            return proc_unk;
        }
    default:
        return proc_unk;
    }
}
/*
 */
int usage(char* pn){
    fprintf(stderr,"Synopsis\n\t%s enc <int>\n\t%s dec <hex>\n\t%s val <int>\n\t%s cnt <int>\n\nDescription\n\n\tTest LEB functions.\n\n",pn,pn,pn,pn);

    return 1;
}
int main_dec(char *in){

    bix* bin = bix_decode(in,bix_count(in,strlen(in)));
    if (null != bin){
        leb* li = leb_decode(bin->content,bin->size);
        if (null != li){
            fprintf(stdout,"%lx\n",li->value);

            leb_destroy(li);
            bix_destroy(bin);
            return 0;
        }
        else {
            leb_destroy(li);
            bix_destroy(bin);
            return 1;
        }
    }
    else {
        return 1;
    }
}
int main_enc(char *in){

    size_t in_len = strlen(in);
    char *in_end = (in+in_len);
    uint64_t in_bint = strtoul(in,&in_end,0);

    char *leb_buf = calloc(1,0x20);
    if (null != leb_buf){
        size_t leb_len = leb_encode(in_bint,leb_buf,0x20);
        if (0 != leb_len){
            bix *out = bix_encode(leb_buf,leb_len);
            if (null != out){
                char *hex = out->content;

                printf("%s\n",hex);

                bix_destroy(out);
                return 0;
            }
            else {
                free(leb_buf);
                return 1;
            }
        }
        else {
            free(leb_buf);
            return 1;
        }
    }
    else {
        return 1;
    }
}
int main_cnt(char *in){

    size_t in_len = strlen(in);
    char *in_end = (in+in_len);
    uint64_t value = strtoul(in,&in_end,0);

    size_t count = leb_length(value);

    fprintf(stdout,"%zu\n",count);
    return 0;
}
int main_val(char *in){

    size_t in_len = strlen(in);
    char *in_end = (in+in_len);
    uint64_t value = strtoul(in,&in_end,0);

    printf("%lu\n",value);

    return 0;
}
/*
 */
int main(int argc, char** argv){
    char* pn = argv[0];

    if (3 == argc){
        proc_kind proc = proc_decode(argv[1]);
        char *in = argv[2];
        switch(proc){
        case proc_cnt:
            return main_cnt(in);
        case proc_dec:
            return main_dec(in);
        case proc_enc:
            return main_enc(in);
        case proc_val:
            return main_val(in);
        default:
            return usage(pn);
        }
    }
    else {
        return usage(pn);
    }
}
