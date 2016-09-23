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
	
	struct associatedWord *newWord = malloc(sizeof(struct associatedWord));
	newWord->word = "Max";
	newWord->numCount = 1;
	
	struct associatedWord *newWord1 = malloc(sizeof(struct associatedWord));
	newWord1->word = "Tom";
	newWord1->numCount = 1;
	
	struct associatedWord *newWord2 = malloc(sizeof(struct associatedWord));
	newWord2->word = "morning";
	newWord2->numCount = 1;

	struct associatedWord *newWord3 = malloc(sizeof(struct associatedWord));
	newWord3->word = "afternoon";
	newWord3->numCount = 2;
	
	struct associatedWord *newWord4 = malloc(sizeof(struct associatedWord));
	newWord4->word = "night";
	newWord4->numCount = 5;
	
	
	hash_insert(table, "hello", newWord);
	hash_insert(table, "hello", newWord1);
	hash_insert(table, "hello", newWord);
	hash_insert(table, "good", newWord2);
	hash_insert(table, "good", newWord3);
	hash_insert(table, "good", newWord4);
	
//	for (int i = 0; i < 1000; i++) {
//		hash_insert(table, randomString(i), malloc(1));
//	}
//	printf("%d\n", hashKey("good"));
	
	hash_find_associated_word(table, "hello");
	hash_find_associated_word(table, "good");
	
//	printf("%s\n", table->buckets[37]->entries[0]->a[0]->word);
//	printf("%s\n", table->buckets[37]->entries[0]->a[1]->word);
//	printf("%s\n", table->buckets[58]->entries[0]->a[0]->word);
//	printf("%s\n", table->buckets[58]->entries[0]->a[1]->word);

//	printf("%d\n", hash_retrieve(table, "hello"));
	
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
