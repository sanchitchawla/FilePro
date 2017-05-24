	void* newPtr = ptr;
    size_t upSize = size;

    int buffer;
    int remainder;
    int extendSize;
    
    if (size <= 0) return NULL;
    
    if (upSize <= DSIZE) { upSize = DSIZE * 2; } 

    else { upSize = ALIGN(DSIZE + size); }

    upSize += REALLOCBUFF;
    
    buffer = GET_SIZE(HDRP(ptr)) - upSize;
    
    if (buffer < 0) {

        if (GET_SIZE(HDRP(NEXT_BLKP(ptr))) && GET_ALLOC(HDRP(NEXT_BLKP(ptr)))){

        	newPtr = mm_malloc(upSize - DSIZE);
            memcpy(newPtr, ptr, MIN(size, upSize));
            mm_free(ptr);
        } 
        
        else {
            remainder = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr))) - upSize;

            if (remainder < 0) {
                extendSize = MAX(-remainder, CHUNKSIZE);

                if (extendheap(extendSize) == NULL){
                	return NULL;	
                } 

                remainder += extendSize;
            }
            
            delete(NEXT_BLKP(ptr));
            
            PUT_NOTAG(HDRP(ptr), PACK(upSize + remainder, 1)); 
            PUT_NOTAG(FTRP(ptr), PACK(upSize + remainder, 1)); 

        }

        buffer = GET_SIZE(HDRP(newPtr)) - upSize;
    }

    if (REALLOCBUFF * 2 > buffer) { SET_RATAG(HDRP(NEXT_BLKP(newPtr))); }

    return newPtr;