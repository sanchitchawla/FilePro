/*
	So I implemented a Segregrated Free list malloc.
	Each block has a header and footer
	All free blocks contain pointers to prev and next free block
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "mm.h"
#include "memlib.h"


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
#define REALLOCBUFF  (1<<7)    
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


void* seglist[10];

void* extendheap(size_t size);
void* coalesce(void *ptr);
void* place(void *ptr, size_t blocksize);
void insert(void *ptr, size_t size);
void delete(void *ptr);

/* 
 * mm_init - initialize the malloc package.
 	Allocating the heap area
 */
int mm_init(void){

	char* first;

	// Initialize the list 
	for (int i = 0; i < 10; i++){
		seglist[i] = NULL;
	}

	if ((long)(first = mem_sbrk(WSIZE * 4)) == -1){
		return -1;
	}

	PUT_NOTAG(first, 0);
	PUT_NOTAG(first + WSIZE, PACK(DSIZE , 1));
	PUT_NOTAG(first + (2 * WSIZE), PACK(DSIZE , 1)); 
	PUT_NOTAG(first + (3 * WSIZE), PACK(0 , 1));

    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 	Returns pointer to an allocated area.
 */
void* mm_malloc(size_t size){

    size_t blocksize;    
    void* ptr = NULL;  
    int i = 0; 
    
    if (size <= DSIZE) {
        blocksize = 2 * DSIZE;
    }

    else {
        blocksize = ALIGN(size + DSIZE);
    }
    
    size_t searchsize = blocksize;

    while (i < 10) {

    	searchsize >>= 1;
        i++;

        if ((i == 9) || ((searchsize <= 1))) {

            ptr = seglist[i];

            while ((ptr != NULL) && ((blocksize > GET_SIZE(HDRP(ptr))))){
                ptr = PRED(ptr);
            }

            if (ptr != NULL){
                break;
            }
        }
        

    }
    
    // extend heap, if no free block
    if (ptr == NULL) {

        size_t extendsize = MAX(blocksize, CHUNKSIZE);
        
        if ((ptr = extendheap(extendsize)) == NULL){
            return NULL;
        }
    }
    
    ptr = place(ptr, blocksize);
    return ptr;

}

/*
 * mm_free - Frees the block given to it
 */
void mm_free(void* ptr){

    size_t size = GET_SIZE(HDRP(ptr));
    REMOVE_RATAG(HDRP(NEXT_BLKP(ptr)));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    insert(ptr, size);
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void* mm_realloc(void* ptr, size_t size){

    void* newPtr = ptr;
    size_t upSize = size;

    if (size <= 0) return NULL;
    
    if (upSize <= DSIZE) { upSize = DSIZE * 2; } 

    else { upSize = ALIGN(DSIZE + size); }

    upSize += REALLOCBUFF;
    
    int buffer = GET_SIZE(HDRP(ptr)) - upSize;

    if (buffer < 0){

        if (GET_SIZE(HDRP(NEXT_BLKP(ptr))) && GET_ALLOC(HDRP(NEXT_BLKP(ptr)))){

        	newPtr = mm_malloc(upSize - DSIZE);
            memcpy(newPtr, ptr, MIN(size, upSize));
            mm_free(ptr);

        } 

        else{
        	int r = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr))) - upSize;

        	if (r < 0){

        		int extra = MAX(r, CHUNKSIZE);

            	if (extendheap(extra) == NULL){
            		return NULL;	
            	} 

            	r += extra;
        	}

            
            delete(NEXT_BLKP(ptr));
            PUT_NOTAG(HDRP(ptr), PACK(upSize + r, 1)); 
            PUT_NOTAG(FTRP(ptr), PACK(upSize + r, 1)); 
        }

    	 buffer = GET_SIZE(HDRP(newPtr)) - upSize;
    }
    return newPtr;

}

void insert(void* ptr, size_t size){

	void* searchin = NULL;
	void* insertin = NULL;
	int each = 0;

	while ((each < 9) && (size > 1)){
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
		seglist[each] = ptr;
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
		seglist[each] = ptr;
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

	while ((each < 9) && (size > 1)){ 
		size >>= 1;
		each++;
	}

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

void* coalesce(void* ptr){
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(ptr)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    size_t size = GET_SIZE(HDRP(ptr));
    
    if (GET_TAG(HDRP(PREV_BLKP(ptr)))){
        prev_alloc = 1;
    }
    // if both allocated
    if (prev_alloc && next_alloc) {
        return ptr;
    }
    // if next one not allocated
    else if (prev_alloc && !next_alloc) {
        delete(ptr);
        delete(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    } 
    // if previouss one not allocated
    else if (!prev_alloc && next_alloc) {
        delete(ptr);
        delete(PREV_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr)));
        PUT(FTRP(ptr), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    } 
    // if both free 
    else {
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

	else if (alignedsize > DSIZE * 2){

		PUT(HDRP(ptr), PACK(r, 0));
		PUT(FTRP(ptr), PACK(r, 0));
		PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(alignedsize, 1));
		PUT_NOTAG(FTRP(NEXT_BLKP(ptr)), PACK(alignedsize, 1));
		insert(ptr, r);

		return NEXT_BLKP(ptr);
	}

	else {

		PUT(HDRP(ptr), PACK(alignedsize, 1));
		PUT(FTRP(ptr), PACK(alignedsize, 1));
		PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(r, 0));
		PUT_NOTAG(FTRP(NEXT_BLKP(ptr)), PACK(r, 0));
		insert(NEXT_BLKP(ptr), r);
	}

	return ptr;

}