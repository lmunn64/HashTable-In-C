#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#define PRIME1 151
#define PRIME2 163

hash_table_t* ht_new(){

    hash_table_t* ht = malloc(sizeof(hash_table_t));
    ht->size = 55;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(item_t*));
    return ht;
}
static void ht_del_item(item_t* i){
    free(i->key);
    free(i->value);
    free(i);
}
void ht_del_hash_table(hash_table_t* ht){
    for(int i = 0; i < ht->size; i++){
        item_t* item = ht->items[i];
        if(item){
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}
static item_t* ht_new_item(const char* k, const char* v){
    item_t* i = malloc(sizeof(item_t));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

int ht_hash(const char* str, int prime, int numBuckets){
    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        hash = hash * prime + c;
    }
    return hash % numBuckets;
}
