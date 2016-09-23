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
const int associatedWordCount = 100;


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
void hash_insert(struct HashTable *table, char *key, struct associatedWord *assW) {
	
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
			for (int i = 0; i < 100; i++) {
				if (entry->a[i] == NULL || strcmp(bucket->entries[loc]->a[i]->word, assW->word) == 0) {
					entry->a[i] = assW;
					i = 100;
				}
			}
		bucket->entries[loc] = entry;
		
	}
	//insert condition: there is already an entry exist
	else {
		bucket->entries[loc]->word = key;
		//check if the data already exist
			for (int i = 0; i < 100; i++) {
				if (bucket->entries[loc]->a[i] == NULL || strcmp(bucket->entries[loc]->a[i]->word, assW->word) == 0) {
					bucket->entries[loc]->a[i] = assW;
					i = 100;
				}
			}
		}
}

//diaplay assocaited word function
void hash_find_associated_word(struct HashTable *table, char *key) {
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = table->buckets[hash];
	
	// find entry in bucket which matches key = word
	printf("%s%s\n", "associated word for: ", key);
	
	for (int i = 0; i < bucketSize; i++) {
		if (bucket->entries[i] != NULL) {
			if (strcmp(bucket->entries[i]->word, key) == 0) {
				for (int j = 0; j < associatedWordCount; j++) {
					if (bucket->entries[i]->a[j] != NULL) {
						printf("%s%s%s%d\n", "Word: ", bucket->entries[i]->a[j]->word, "; Frequency: ", bucket->entries[i]->a[j]->numCount);
					}
				}
				
			}
		}
	}
	printf("\n");
}

struct Entry *hash_retrieve(struct HashTable *table, char *key) {
	
	struct Entry *entry = NULL;
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = table->buckets[hash];
	
	int idx = 0;
	while (bucket->entries[idx] != NULL) {
		if (strcmp(bucket->entries[idx]->word, key) == 0) {
			entry = bucket->entries[idx];
		}
	}

	return entry;
}

