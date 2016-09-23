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
#include "hash_table.h"

char *randomString(int len) {
	char *buf = malloc(sizeof(char) * (len + 1));
	
	for (int i = 0; i < len; i++) {
		buf[i] = arc4random_uniform(25) + 0x41;
	}
	
	buf[len] = 0;
	return buf;
}

void test_hash_table(){
	
	struct HashTable *table = create_hash_table();
	struct Entry *entry = malloc(sizeof(struct Entry));
	entry->word = "hello";
	struct associatedWord *aWord = malloc(sizeof(struct associatedWord));
	aWord->word = "Max";
	aWord->numCount = 2;
	entry->a[0] = aWord;
	
	
	hash_insert(table, entry);
	struct Entry *find = malloc(sizeof(struct Entry));
	find = hash_retrieve(table, "hello");
	printf("%s\n", find->a[0]->word);
	
}

void test_hash_function() {
	int sum = 0;
	
	for (int i = 0; i < 1000; i++) {
		char *randString = randomString(arc4random_uniform(15));
		sum += hashKey(randString);
		free(randString);
	
	}
	
	//printf("avg: %d\r\n", sum / 1000);
	//should be around 50, which is pretty good.
}


int main(int argc, const char *argv[]) {
	test_hash_table();
//	test_hash_function();
	
	return 0;
}
