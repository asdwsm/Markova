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
#include <time.h>
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
	
	//create one entry
	struct Entry *entryX = malloc(sizeof(struct Entry));
	entryX->word = "hello";
	struct associatedWord *aWord = malloc(sizeof(struct associatedWord));
	aWord->word = "Max";
	aWord->numCount = 2;
	entryX->a[0] = aWord;
	
	struct Entry *entryY = malloc(sizeof(struct Entry));
	entryY->word = "hello";
	struct associatedWord *aWord1 = malloc(sizeof(struct associatedWord));
	aWord1->word = "Tom";
	aWord1->numCount = 2;
	entryY->a[0] = aWord1;
	struct associatedWord *aWord2 = malloc(sizeof(struct associatedWord));
	aWord2->word = "Taylor";
	aWord2->numCount = 2;
	entryY->a[1] = aWord2;
	
	
	hash_insert(table, entryX);
	hash_readd(table, entryY);
	
//	//create ramdom entries
//	clock_t begin = clock();
//	for (int i = 0 ; i < 10000; i++) {
//		struct Entry *entry = malloc(sizeof(struct Entry));
//		entry->word = randomString(5);
//		struct associatedWord *newWord = malloc(sizeof(struct associatedWord));
//		newWord->word = randomString(5);
//		newWord->numCount = 1;
//		entry->a[0] = newWord;
//		hash_insert(table, entry);
//	}
//	clock_t end = clock();
//	
//	printf("%s %f\n","Inserting a lot of entries:", (double)(end - begin)/CLOCKS_PER_SEC);
//	
//	clock_t nextInsertBegin = clock();
//	hash_insert(table, entryX);
//	clock_t nextInsertEnd = clock();
//	
//	printf("%s %f\n","Inserting one entry:", (double)(nextInsertEnd - nextInsertBegin)/CLOCKS_PER_SEC);
//	
	struct Entry *find = malloc(sizeof(struct Entry));
//	
//	clock_t retrieveBegin = clock();
	find = hash_retrieve(table, entryX->word);
//	clock_t retrieveEnd = clock();
//	
//	printf("%s %f\n","Retrieve an Entry:", (double)(retrieveEnd - retrieveBegin)/CLOCKS_PER_SEC);
	
	printf("%s\n", find->a[2]->word);
	hash_find_associated_word(table, entryX->word);
	
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
//	test_hash_table();
//	test_hash_function();
	
	parseFile("/Users/Tom/Desktop/Test.txt");
	return 0;
}
