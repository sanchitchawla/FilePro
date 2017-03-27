/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "SunnyisKewl",
    /* First member's full name */
    "Sanchit Chawla",
    /* First member's email address */
    "sanchit_sid@hotmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/* Mine */
#define WSIZE     4          
#define DSIZE     8          
#define INITCHUNKSIZE (1<<6)
#define CHUNKSIZE (1<<12)
#define REALLOC_BUFFER  (1<<7)    
#define MAX(x, y) ((x) > (y) ? (x) : (y)) 
#define MIN(x, y) ((x) < (y) ? (x) : (y)) 
#define PACK(size, alloc) ((size) | (alloc))
#define GET(p)            (*(unsigned int *)(p))
#define PUT(p, val)       (*(unsigned int *)(p) = (val) | GET_TAG(p))
#define PUT_NOTAG(p, val) (*(unsigned int *)(p) = (val))
#define SET_PTR(p, ptr) (*(unsigned int *)(p) = (unsigned int)(ptr))
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_TAG(p)   (GET(p) & 0x2)
#define SET_RATAG(p)   (GET(p) |= 0x2)
#define REMOVE_RATAG(p) (GET(p) &= ~0x2)
#define HDRP(ptr) ((char *)(ptr) - WSIZE)
#define FTRP(ptr) ((char *)(ptr) + GET_SIZE(HDRP(ptr)) - DSIZE)
#define NEXT_BLKP(ptr) ((char *)(ptr) + GET_SIZE((char *)(ptr) - WSIZE))
#define PREV_BLKP(ptr) ((char *)(ptr) - GET_SIZE((char *)(ptr) - DSIZE))
#define PRED_PTR(ptr) ((char *)(ptr))
#define SUCC_PTR(ptr) ((char *)(ptr) + WSIZE)
#define PRED(ptr) (*(char **)(ptr))
#define SUCC(ptr) (*(char **)(SUCC_PTR(ptr)))


void* seglist[20];

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void){

	char* start;

	for (int i = 0; i < 20; i++){
		seglist[i] = NULL;
	}

	if ((long)(start = mem_sbrk(WSIZE * 4)) == -1){
		return -1;
	}

	PUT_NOTAG(start, 0);
	PUT_NOTAG(start + WSIZE, PACK(DSIZE , 1));
	PUT_NOTAG(start + (2 * WSIZE), PACK(DSIZE , 1)); 
	PUT_NOTAG(start + (3 * WSIZE), PACK(0 , 1));

    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
 //    int newsize = ALIGN(size + SIZE_T_SIZE);
 //    void *p = mem_sbrk(newsize);
 //    if (p == (void *)-1)
	// return NULL;
 //    else {
 //        *(size_t *)p = size;
 //        return (void *)((char *)p + SIZE_T_SIZE);
 //    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    // void *oldptr = ptr;
    // void *newptr;
    // size_t copySize;
    
    // newptr = mm_malloc(size);
    // if (newptr == NULL)
    //   return NULL;
    // copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    // if (size < copySize)
    //   copySize = size;
    // memcpy(newptr, oldptr, copySize);
    // mm_free(oldptr);
    // return newptr;
}

void insert(void* ptr, size_t size){
	void* searchin = NULL; // Might need to set to ptr !!!
	void* insertin = NULL;
	int each = 0;

	while ((each < 19) && (size > 1)){ /* 19 comes from sizeof(list) -1 */
		size >>= 1;
		each++;
	} 
	searchin = seglist[each];

	while((searchin != NULL) && (size > GET_SIZE(HDRP(searchin)))){
		insertin = searchin;
		searchin = PRED(searchin);
	}

	if ((searchin != NULL) && (insertin!= NULL)){
		SET_PTR(PRED_PTR(ptr), searchin);
		SET_PTR(SUCC_PTR(searchin), ptr);	
		SET_PTR(SUCC_PTR(ptr), insertin);
		SET_PTR(PRED_PTR(insertin), ptr);
	}
	else if ((searchin != NULL) && (insertin == NULL)){
		SET_PTR(PRED_PTR(ptr), searchin);
		SET_PTR(SUCC_PTR(searchin), ptr);	
		SET_PTR(SUCC_PTR(ptr), insertin);
		seglist[each] = ptr;
	}
	else if ((searchin == NULL) && (insertin != NULL)){
		SET_PTR(PRED_PTR(ptr), searchin);
		SET_PTR(SUCC_PTR(ptr), insertin);
		SET_PTR(PRED_PTR(insertin), ptr);
	}
	else{
		SET_PTR(PRED_PTR(ptr), NULL);
		SET_PTR(SUCC_PTR(ptr), NULL);
		seglist[each] = ptr;
	}


}


void delete(void* ptr){

	size_t size = GET_SIZE(HDRP(ptr));
	int each = 0;

	while ((each < 19) && (size > 1)){ /* 19 comes from sizeof(list) -1 */
		size >>= 1;
		each++;
	}

	/* If there's something before and after */
	if ((PRED(ptr) != NULL) && (SUCC(ptr) != NULL)){
		SET_PTR(SUCC_PTR(PRED(ptr)), SUCC(ptr));
		SET_PTR(PRED_PTR(SUCC(ptr)), PRED(ptr));
	}
	else if ((PRED(ptr) != NULL) && (SUCC(ptr) == NULL)){
		SET_PTR(SUCC_PTR(PRED(ptr)), NULL);
		seglist[each] = PRED(ptr);
	}
	else if ((PRED(ptr) == NULL) && (SUCC(ptr) != NULL)){
		SET_PTR(PRED_PTR(SUCC(ptr)), NULL);
	} 
	else{
		seglist[each] = NULL;
	}

}

void* coalesce(void *ptr){
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(ptr)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    size_t size = GET_SIZE(HDRP(ptr));
    
    if (GET_TAG(HDRP(PREV_BLKP(ptr))))
        prev_alloc = 1;

    if (prev_alloc && next_alloc) {
        return ptr;
    }
    else if (prev_alloc && !next_alloc) {
        delete(ptr);
        delete(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    } else if (!prev_alloc && next_alloc) {
        delete(ptr);
        delete(PREV_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr)));
        PUT(FTRP(ptr), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    } else {
        delete(ptr);
        delete(PREV_BLKP(ptr));
        delete(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr))) + GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    }
    
    insert(ptr, size);
    
    return ptr;
}

void* extendheap(size_t size){
	void* ptr;
	size_t alignedsize = ALIGN(size);

	if ((ptr = mem_sbrk(alignedsize)) == (void*) -1){
		return NULL;
	}

	PUT_NOTAG(HDRP(ptr), PACK(alignedsize, 0));
	PUT_NOTAG(FTRP(ptr), PACK(alignedsize, 0));
	PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(alignedsize, 1));
	insert(ptr, alignedsize);

	return coalesce(ptr);
}

void* place(void* ptr, size_t alignedsize){

	size_t psize = GET_SIZE(HDRP(ptr));
	size_t r     = psize - alignedsize;

	delete(ptr);

	if (r <= DSIZE * 2){

		PUT(HDRP(ptr), PACK(psize, 1));
		PUT(FTRP(ptr), PACK(psize, 1));
	}
	else if (alignedsize >= 100){

		PUT(HDRP(ptr), PACK(r, 0));
		PUT(FTRP(ptr), PACK(r, 0));
		PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(alignedsize, 1));
		PUT_NOTAG(FTRP(NEXT_BLKP(ptr)), PACK(alignedsize, 1));
		insert(ptr, r);

		return NEXT_BLKP(ptr);
	}
	else{

		PUT(HDRP(ptr), PACK(alignedsize, 1));
		PUT(FTRP(ptr), PACK(alignedsize, 1));
		PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(r, 0));
		PUT_NOTAG(FTRP(NEXT_BLKP(ptr)), PACK(r, 0));
		insert(NEXT_BLKP(ptr), r);
	}

	return ptr;

}