#include "hash_table.h"
#include <stdio.h>

int main(){
    hash_table_t* ht = ht_new();

    ht_insert(ht, "Hello", "Goodbye");
    ht_insert(ht, "Goodbye", "Hello");

    printf("%s", ht_search(ht, "Hello"));
}