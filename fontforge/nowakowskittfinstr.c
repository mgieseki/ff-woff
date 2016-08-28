/* Copyright (C) 2000-2012 by
   George Williams, Michal Nowakowski & Alexey Kryukov */

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.

 * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fontforgevw.h"

#include "ttf.h"

extern int autohint_before_generate;

/* non-optimized instructions will be using a stack of depth 6, allowing
 * for easy testing whether the code leaves trash on the stack or not.
 */
#define OPTIMIZE_TTF_INSTRS 1
#if OPTIMIZE_TTF_INSTRS
#define STACK_DEPTH 256
#else
#define STACK_DEPTH 6
#endif


/******************************************************************************
 *
 * Low-level routines for getting a cvt index for a stem width, assuming there
 * are any numbers in cvt. Includes legacy code for importing PS Private into
 * CVT.
 *
 ******************************************************************************/

struct ttf_table *SFFindTable(SplineFont *sf,uint32 tag) {
    struct ttf_table *tab;

    for ( tab=sf->ttf_tables; tab!=NULL && tab->tag!=tag; tab=tab->next );
return( tab );
}

int TTF__getcvtval(SplineFont *sf,int val) {
    int i;
    struct ttf_table *cvt_tab = SFFindTable(sf,CHR('c','v','t',' '));

    if ( cvt_tab==NULL ) {
        cvt_tab = chunkalloc(sizeof(struct ttf_table));
        cvt_tab->tag = CHR('c','v','t',' ');
        cvt_tab->maxlen = 200;
        cvt_tab->data = malloc(100*sizeof(short));
        cvt_tab->next = sf->ttf_tables;
        sf->ttf_tables = cvt_tab;
    }
    for ( i=0; (int)sizeof(uint16)*i<cvt_tab->len; ++i ) {
        int tval = (int16) memushort(cvt_tab->data,cvt_tab->len, sizeof(uint16)*i);
        if ( val>=tval-1 && val<=tval+1 )
return( i );
    }
    if ( (int)sizeof(uint16)*i>=cvt_tab->maxlen ) {
        if ( cvt_tab->maxlen==0 ) cvt_tab->maxlen = cvt_tab->len;
        cvt_tab->maxlen += 200;
        cvt_tab->data = realloc(cvt_tab->data,cvt_tab->maxlen);
    }
    memputshort(cvt_tab->data,sizeof(uint16)*i,val);
    cvt_tab->len += sizeof(uint16);
return( i );
}

/* by default sign is unimportant in the cvt
 * For some instructions anyway, but not for MIAP so this routine has
 *  been broken in two.
 */
int TTF_getcvtval(SplineFont *sf,int val) {
    if ( val<0 ) val = -val;
return( TTF__getcvtval(sf,val));
}
