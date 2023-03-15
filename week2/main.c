
void sort2way(void* a, int l, int r, size_t size, int (*compare)(void*, void*)) {

    if(l >= r) return;

    int i = l, j = r;

    void* tmp = malloc(size);

    void* pivot = a + i * size;

    for(;;) {

        while(compare(a + i * size, pivot) < 0) i++;

        while(compare(a + j * size, pivot) < 0) j--;

        if(i >= j) break;

        memcpy(tmp, a + i * size, size);

        memcpy(a + i * size, a + j * size, size); 

        memcpy(a + j * size, tmp, size);

        i++; j--;

    }

    sort2way(a, l, i-1, size, compare);

    sort2way(a, j+1, r, size, compare);

}
