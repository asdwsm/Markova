//
//  hash_table.c
//  Markova
//
//  Created by Tom Zhu on 9/19/16.
//  Copyright © 2016 Tom Zhu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

const int bucketSize = 100;
const int bucketCount = 100;


struct HashTable *create_hash_table(void) {
	struct HashTable *table = malloc(sizeof(struct HashTable));
	
	table->buckets = malloc(sizeof(struct Bucket) * bucketCount);
	
	for (int i = 0; i < bucketCount; i++) {
		struct Bucket *bucket = &table->buckets[i];
		bucket->entries = malloc(sizeof(struct Entry) * bucketSize);
	}
	
	return table;
}


//hash fucntion
int hashKey(char *key) {
	
	int sum = 5381;
	
	for (int idx = 0; idx < strlen(key); idx++) {
		sum = ((sum << 5) + sum) + key[idx];
	}
	
	// probably bad hash function
	
	return (sum % bucketCount);
}

//insert function
void hash_insert(struct HashTable *table, char *key, void *entry) {
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = &table->buckets[hash];
	
	// insert entry into bucket where there is space
	int loc = 0;
	while (bucket->entries[loc].word != NULL && bucket->entries[loc].word != NULL) {
		loc++;
	}
	bucket->entries[loc].word = key;
	bucket->entries[loc].pairs = entry;
}

//retrieve function
void *hash_retrieve(struct HashTable *table, char *key) {
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = &table->buckets[hash];
	
	// find entry in bucket which matches key = word
	void *find = NULL;
	for (int i = 0; i < bucketSize; i++) {
		if (strcmp(key, bucket->entries[i].word) == 0) {
			find = bucket->entries[i].word;
		}
	}
	return find;
}
