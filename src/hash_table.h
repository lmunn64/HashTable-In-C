#ifndef HASH_TABLE
#define HASH_TABLE

typedef struct item {
    char* key;
    char* value;
} item_t;

typedef struct hash_table {
    int size;
    int count;
    item_t** items;
} hash_table_t;

//Creates and allocates empty hashtable
hash_table_t* ht_new();

//deletes an item
static void ht_del_item(item_t* i);

//Deletes a HashTable
void ht_del_hash_table(hash_table_t* ht);

//Creates new item for a HashTable
static item_t* ht_new_item(const char* k, const char* v);

//Modified djb2 hashing algorithm
int ht_hash(const char* str, int prime, int numBuckets);

static int ht_get_hash(const char * s, const int num_buckets, const int attempt);

// METHODS

void ht_insert(hash_table_t* ht, const char* key, const char* value);

char* ht_search(hash_table_t* t, const char* key);

void ht_delete(hash_table_t* t, const char* key);
#endif