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

//retrive function
void *hash_retrive(struct HashTable *table, char *key) {
	
	int hash = hashKey(key);
	
	struct Bucket bucket = table->buckets[hash];
	
	// find entry in bucket which matches key = word
	
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
	hash_insert(table, key, NULL);
	
    return 0;
}
