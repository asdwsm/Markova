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

int bufferSize = 128;

char *create_word(int *idx, char *oneLine){
	char *word = malloc(sizeof(char) * 50);
	int secondIdx = 0;
	while (*idx < bufferSize) {
		if (oneLine[*idx] == ' ') {
			(*idx)++;
			break;
		}
		else{
			word[secondIdx] = oneLine[*idx];
			secondIdx++;
		}
		(*idx)++;
	}
	printf("Word: %s\n", word);
	return word;
}

struct Entry *create_entry(char *word, char *assWord){
	struct Entry *entry = malloc(sizeof(struct Entry));
	struct associatedWord *aWord = malloc(sizeof(struct associatedWord));
	int hasPeriod = 0;
	for (int i = 0; i < 50; i++) {
		if (assWord[i] == '.') {
			assWord[i] = NULL;
			hasPeriod = 1;
		}
	}
	entry->word = word;
	aWord->word = assWord;
	aWord->numCount = 1;
	if (hasPeriod == 1) {
		aWord->periodCount = 1;
	}
	entry->a[0] = aWord;

	return entry;
}

//open a file and load the hash table
char parseFile(char *fileName, struct HashTable *table){
	FILE *file = fopen(fileName, "r");
	char buff[bufferSize];
	if (file == NULL) {
		printf("Error\n");
	}
	else{
		while (!feof(file)) {
			fread(buff, bufferSize, 1, file);
			//we get a buffer
			int idx = 0;
			while (idx < bufferSize) {
				struct Entry *entry1 = malloc(sizeof(struct Entry));
				struct Entry *entry2 = malloc(sizeof(struct Entry));
				
				char *word1 = create_word(&idx, buff);
				char *word2 = create_word(&idx, buff);
				
				entry1 = create_entry(word1, word2);
				entry2 = create_entry(word2, create_word(&idx, buff));
				if (strcmp(hash_retrieve(table, entry1->word)->word, "Error") != 0) {
					hash_readd(table, entry1);
				}
				else{
					hash_insert(table, entry1);
				}
				if (strcmp(hash_retrieve(table, entry2->word)->word, "Error") != 0) {
					hash_readd(table, entry2);
				}
				else{
					hash_insert(table, entry2);
				}

			}
		}
		fclose(file);
	}
	return buff;
}

//Load Data
void load_data(){

}


char *randomString(int len) {
	char *buf = malloc(sizeof(char) * (len + 1));
	
	for (int i = 0; i < len; i++) {
		buf[i] = arc4random_uniform(25) + 0x41;
	}
	
	buf[len] = 0;
	return buf;
}

void test_hash_table(){
	
//	struct HashTable *table = create_hash_table();
	
	//create one entry
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
	//struct Entry *find = malloc(sizeof(struct Entry));
//	
//	clock_t retrieveBegin = clock();
	//find = hash_retrieve(table, entryX->word);
//	clock_t retrieveEnd = clock();
//	
//	printf("%s %f\n","Retrieve an Entry:", (double)(retrieveEnd - retrieveBegin)/CLOCKS_PER_SEC);
	
	//printf("%s\n", find->a[2]->word);
	//hash_find_associated_word(table, entryX->word);
	
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
	
	struct HashTable *table = create_hash_table();
	parseFile("/Users/Tom/Desktop/Test.txt", table);
	hash_find_associated_word(table, "large");
	return 0;
}
