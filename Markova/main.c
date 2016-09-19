//
//  main.c
//  Markova
//
//  Created by Tom Zhu on 9/16/16.
//  Copyright © 2016 Tom Zhu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int bucketSize = 100;
const int bucketCount = 100;

struct Entry {
	char *word;
	void *pairs;
};

struct Bucket {
	struct Entry entries[bucketSize];
};

struct HashTable {
	struct Bucket buckets[bucketCount];
};

//return the size of the bucket;
int hash_size(struct HashTable table) {
	return bucketSize;
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
	
	struct Bucket bucket = table->buckets[hash];
	
	// insert entry into bucket where there is space
	int loc = 0;
	while (bucket.entries[loc].word != NULL && bucket.entries[loc].word != NULL) {
		loc++;
	}
	printf("%d\n",loc);
	bucket.entries[loc].word = key;
	bucket.entries[loc].pairs = entry;
	
//	
//	int position = hash(key);
//	int inserted = 0;
//	
//	while (position < hash_size(table)){
//		
//		if (table.bucket[position].word == NULL) {
//			table.bucket[position].word = key;
//			inserted = 1;
//		}
//		else {
//			position++;
//		}
//	}
//	//if not inserted create a new bucket
//	if (inserted == 0){
//		struct Bucket newBucket[bucketSize];
//		newBucket[position].word = key;
////		table.bucket[bucketSize].next = newBucket;
//	}
}

//retrieve function
void *hash_retrieve(struct HashTable *table, char *key) {
	
	int hash = hashKey(key);
	
	struct Bucket bucket = table->buckets[hash];
	
	// find entry in bucket which matches key = word
	int location = 0;
	for (int i = 0; i < bucketSize; i++) {
		if (key == bucket.entries[i].word) {
			location = i;
		}
	}
//	char *key;
//	if (table.bucket[position].word != NULL) {
//		key = table.bucket[position].word;
//	}
//	else if(table.bucket[bucketSize].next == NULL)
//		key = "Item does not exist";
//	else{
////		key = table.bucket[bucketSize].next->word;
//	}
//	return key;
	return NULL;
}

//Testing hashtable
int main(int argc, const char *argv[]) {
	char *key = "happy";
	struct HashTable *table = malloc(sizeof(struct HashTable));
	hash_insert(table, key, malloc(1));
	printf("%d\n", hashKey(key));
	printf(table->buckets[87].entries[0].word);
	
    return 0;
}
