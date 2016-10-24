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


const int bucketSize = 200;
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
void hash_insert(struct HashTable *table, struct Entry *entry) {
	
	int hash = hashKey(entry->word);
	
	struct Bucket *bucket = table->buckets[hash];
	
	//insert entry into bucket where there is space
	int loc = 0;
	while (bucket->entries[loc] != NULL) {
		if (strcmp(bucket->entries[loc]->word, entry->word) == 0) {
			break;
		}
		loc++;
	}

	if (bucket->entries[loc] == NULL || strcmp(bucket->entries[loc]->word, entry->word) == 0) {
		bucket->entries[loc] = entry;
	
	}
}

//retrieve function
struct Entry *hash_retrieve(struct HashTable *table, char *key){
	
	//struct Entry *entry = malloc(sizeof(struct Entry));
	
	int hash = hashKey(key);
	
	struct Bucket *bucket = table->buckets[hash];
	
	for (int idx = 0; idx < bucketCount; idx++) {
		if (bucket->entries[idx] != NULL) {
			if (strcmp(bucket->entries[idx]->word, key) == 0) {
				return bucket->entries[idx];
			}
		}
	}
	return NULL;
}

//add pairs to a current entry then readd it to the hash table
void hash_readd(struct HashTable *table, struct Entry *entry){
	
	struct Entry *findEntry = hash_retrieve(table, entry->word);
	int idx = 0;
	while (entry->a[idx] != NULL) {
		for (int loc = 0; loc < associatedWordCount; loc++) {
			if (findEntry->a[loc] == NULL) {
				findEntry->a[loc] = entry->a[idx];
				break;
			}
			else {
				if (strcmp(findEntry->a[loc]->word, entry->a[idx]->word) == 0) {
					findEntry->a[loc]->numCount++;
					int hasPeriod = 0;
					for (int i = 0; i < 50; i++) {
						if (entry->a[idx]->word[i] == '.') {
							entry->a[idx]->word[i] = NULL;
							hasPeriod = 1;
						}
						if (hasPeriod == 1) {
							findEntry->a[loc]->periodCount++;
						}

					}
					break;
				}
			}
		}
		idx++;
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
						printf("%s%s%s%d%s%d\n", "Word: ", bucket->entries[i]->a[j]->word, "; Frequency: ", bucket->entries[i]->a[j]->numCount, "; Periods: ", bucket->entries[i]->a[j]->periodCount);
					}
				}
				
			}
		}
	}
	printf("\n");
}
