//
//  main.c
//  Markova
//
//  Created by Tom Zhu on 9/16/16.
//  Copyright © 2016 Tom Zhu. All rights reserved.
//

#include <stdio.h>

const int bucketSize = 100;

struct Bucket
{
	char *word;
	struct bucket *next;
	
};

struct HashTable
{
	struct Bucket bucket[bucketSize];
};

//return the size of the bucket;
int hash_size(struct HashTable table){
	return bucketSize;
}

//hash fucntion
int hash(char *key){
	return 0;
}

//insert function
void hash_insert(struct HashTable table, char* key){
	
	int position = hash(key);
	int inserted = 0;
	
	while (position < hash_size(table)){
		
		if (table.bucket[position].word == NULL) {
			table.bucket[position].word = key;
			inserted = 1;
		}
		else {
			position++;
		}
	}
	//if not inserted create a new bucket
	if(inserted == 0){
		struct Bucket newBucket[bucketSize];
		newBucket[position].word = key;
		table.bucket[bucketSize].next = newBucket;
	}
}

//retrive function
char* hash_retrive(struct HashTable table, int position){
	char *key;
	if (table.bucket[position].word != NULL) {
		key = table.bucket[position].word;
	}
	else if(table.bucket[bucketSize].next == NULL)
		key = "Item does not exist";
	else{
		key = table.bucket[bucketSize].next->word;
	}
	return key;
}

//Testing hashtable
int main(int argc, const char * argv[]) {
	char *key = "happy";
	struct HashTable table;
	hash_insert(table, key);
	
	
    return 0;
}
