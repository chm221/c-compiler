/*struct node_s {
    struct node_s *next;
    char *key;
    char *value;
};*/
typedef struct node_s node_t;

/* struct hashtable_s {
    int size;           // size of the pointer table 
    int n;              // number of elements stored 
    struct node_s **table;
};*/
typedef struct hashtable_s *hashtable_t;

hashtable_t table_create(void);

void insert(hashtable_t h, const char *key, int value, int type);

void add_value(hashtable_t h, const char *key, int value);

int search_hash(hashtable_t h, const char *key);

void print_hash(hashtable_t h, const char *key);