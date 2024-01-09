#include "fibheap.h"

int main(){
    struct fibheap *heap = malloc(sizeof(struct fibheap));
    struct fibheap *heap2 = malloc(sizeof(struct fibheap));
    printf("Первая куча:\n");
    heap = fibheap_insert(heap, 35, "Value 35");
    heap = fibheap_insert(heap, 10, "Value 10");
    heap = fibheap_insert(heap, 18, "Value 18");
    print_heap(heap->min);
    printf("\nВторая куча:\n");
    heap2 = fibheap_insert(heap2, 7, "Value 7");
    heap2 = fibheap_insert(heap2, 52, "Value 52");
    heap2 = fibheap_insert(heap2, 30, "Value 30");
    print_heap(heap2->min);

    printf("\nСлияние куч:\n");
    heap = fibheap_union(heap, heap2);
    print_heap(heap->min);
    printf("Min: %d\n", fibheap_min(heap)->key);
    printf("\nУдаление минимального:\n");
    fibheap_delete_min(heap);
    print_heap(heap->min);
    printf("Min: %d\n", fibheap_min(heap)->key);
    printf("\nУдаление узла(key=30):\n");
    fibheap_delete(heap, 30);
    print_heap(heap->min);
    printf("Min: %d\n", fibheap_min(heap)->key);
    printf("\nУдаление узла(key=18):\n");
    fibheap_delete(heap, 18);
    print_heap(heap->min);
    printf("Min: %d\n", fibheap_min(heap)->key);
    return 0;
}