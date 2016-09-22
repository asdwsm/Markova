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

struct associatedWord {
	char *word;
	int numCount;
};

struct Entry {
	char *word;
	struct associatedWord *a[100];
};

struct Bucket {
	struct Entry **entries;
};

struct HashTable {
	struct Bucket **buckets;
};

struct HashTable *create_hash_table(void);
void hash_insert(struct HashTable *table, char *key, char *data);
int hash_retrieve(struct HashTable *table, char *key);


#endif /* hash_table_h */
