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
	
	table->buckets = malloc(sizeof(struct Bucket *) * bucketCount);
	
	for (int i = 0; i < bucketCount; i++) {
		
		table->buckets[i] = malloc(sizeof(struct Bucket));
		
		struct Bucket *bucket = table->buckets[i];
		bucket->entries = malloc(sizeof(struct Entry *) * bucketSize);
	}
	
	return table;
}

//hash fucntion
int hashKey(char *key) {
	
	unsigned int sum = 5381;
	
	for (int idx = 0; idx < strlen(key); idx++) {
		sum = ((sum << 5) + sum) + key[idx];
	}
	
	// probably bad hash function
	
	return (sum % bucketCount);
}

//insert function
void hash_insert(struct HashTable *table, char *key, char *data) {
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = table->buckets[hash];
	
	//insert entry into bucket where there is space
	int loc = 0;
	while (bucket->entries[loc] != NULL) {
		if (strcmp(bucket->entries[loc]->word, key) == 0) {
			break;
		}
		loc++;
	}
	//insert condition: no current entry exist, create a new one
	if (bucket->entries[loc] == NULL) {
		struct Entry *entry = malloc(sizeof(struct Entry));
		entry->word = key;
		//check if the data already exist
		int find = 0;
		for (int i = 0; i < 100; i++) {
			if (entry->a[i] != NULL){
				if (strcmp(entry->a[i]->word, data) == 0) {
					entry->a[i]->numCount++;
					find = 1;
				}
			}
		}
		
		//if not find
		if (find == 0) {
			for (int i = 0; i < 100; i++) {
				if (entry->a[i] == NULL) {
					struct associatedWord *ass = malloc(sizeof(struct associatedWord));
					entry->a[i] = ass;
					entry->a[i]->word = data;
					entry->a[i]->numCount++;
					i = 100;
				}
			}
		}
		bucket->entries[loc] = entry;
		
	}
	//insert condition: there is already an entry exist
	else {
		bucket->entries[loc]->word = key;
		//check if the data already exist
		int find = 0;
		for (int i = 0; i < 100; i++) {
			if (bucket->entries[loc]->a[i] != NULL){
				if (strcmp(bucket->entries[loc]->a[i]->word, data) == 0) {
					bucket->entries[loc]->a[i]->numCount++;
					find = 1;
				}
			}
		}
		
		//if not find
		if (find == 0) {
			for (int i = 0; i < 100; i++) {
				if (bucket->entries[loc]->a[i] == NULL) {
					struct associatedWord *ass = malloc(sizeof(struct associatedWord));
					bucket->entries[loc]->a[i] = ass;
					bucket->entries[loc]->a[i]->word = data;
					bucket->entries[loc]->a[i]->numCount++;
					i = 100;
				}
			}
		}
	}
}

//retrieve function
int hash_retrieve(struct HashTable *table, char *key) {
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = table->buckets[hash];
	
	// find entry in bucket which matches key = word
	
	void *find = NULL;
	int result = 0;
	for (int i = 0; i < bucketSize; i++) {
		if(bucket->entries[i] != NULL){
			if (strcmp(key, bucket->entries[i]->word) == 0) {
				find = bucket->entries[i]->word;
				result = 1;
			}
		}
	}
	return result;
	//return find;
}
