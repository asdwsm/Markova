//
//  hash_table.h
//  Markova
//
//  Created by Tom Zhu on 9/19/16.
//  Copyright © 2016 Tom Zhu. All rights reserved.
//

#ifndef hash_table_h
#define hash_table_h

#include <stdio.h>

const int bucketSize = 100;
const int bucketCount = 100;

struct Entry {
	char *word;
	void *pairs;
};

struct Bucket {
	struct Entry *entries;
};

struct HashTable {
	struct Bucket *buckets;
};

struct HashTable *create_hash_table(void) {
	struct HashTable *table = malloc(sizeof(struct HashTable));
	
	table->buckets = malloc(sizeof(struct Bucket) * bucketCount);
	
	for (int i = 0; i < bucketCount; i++) {
		struct Bucket *bucket = &table->buckets[i];
		bucket->entries = malloc(sizeof(struct Entry) * bucketSize);
	}
	
	return table;
}

void hash_insert(struct HashTable *table, char *key, void *entry);
void *hash_retrieve(struct HashTable *table, char *key);


#endif /* hash_table_h */
