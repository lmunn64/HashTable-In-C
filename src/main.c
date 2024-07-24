#include "hash_table.h"
#include <stdio.h>

int main(){
    hash_table_t* ht = ht_new();
    ht_del_hash_table(ht);
    int d = ht_hash("arasdfa", 53);
    printf("%d", d);
}