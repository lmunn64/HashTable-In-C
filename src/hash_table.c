#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define PRIME1 151
#define PRIME2 163

static item_t TOMBSTONE = {NULL, NULL};

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

static int ht_get_hash(const char* s, const int num_buckets, const int attempt){
    const int hash_a = ht_hash(s, PRIME1, num_buckets);

    const int hash_b = ht_hash(s, PRIME2, num_buckets);

    return (hash_a + (attempt *(hash_b + 1))) % num_buckets;
}

void ht_insert(hash_table_t* ht, const char* key, const char* value){
    item_t* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    item_t* curr_item = ht->items[index];
    int i = 1;
    while(curr_item){
        //Updating if key already in hashtable
        if(curr_item != &TOMBSTONE){
            if(strcmp(curr_item->key, key) == 0){
                ht_del_item(curr_item);
                ht->items[index] = item;   
                return;                
            }
        }
        index = ht_get_hash(item->key, ht->size, i);
        curr_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char* ht_search(hash_table_t* ht, const char* key){
    int index = ht_get_hash(key, ht->size, 0);
    item_t* item = ht->items[index];
    int i = 1;
    while(item){
        if(item != &TOMBSTONE){
            if(strcmp(item->key, key) == 0){
                return item->value;
            }
        }
        
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void ht_delete(hash_table_t* ht, const char* key){
    int index = ht_get_hash(key, ht->count, 0);
    item_t* item = ht->items[index];
    int i = 1;
    while(item){
        if(item != &TOMBSTONE){
            if(strcmp(item->key, key) == 0){
                ht_del_item(item);
                ht->items[index] = &TOMBSTONE;ht->count--;                       
            }
        }
        index = ht_get_hash(key, ht->count, i);
        item = ht->items[index];
        i++;
    }
    
}