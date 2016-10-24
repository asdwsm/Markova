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

_Bool isWordTerminatingCharacter(char c) {
	switch (c) {
		case '?':
			return 1;
		case '.':
			return 1;
		case ' ':
			return 1;
		case '\t':
			return 1;
		case '\r':
			return 1;
		case '\n':
			return 1;
		case ',':
			return 1;
	}
	return 0;
}

char *getWordFromBufferAndRemove(char *buf) {
	
	/*
	 * Case: "  hello  how\t are    you"
	 * Only want: "hello"->"how", "how"->"are", "are"->"you", etc
	 */
	
	/*
	 * Use periods as associated words; Makes things easier.
	 * i.e. "How are you?" becomes "are"->"you" and "you"->"?"
	 */
	
	int goodLen = 0;
	int startIndex = 0;
	
	char *ret = NULL;
	
	for (int i = 0; i < strlen(buf); i++) {
		if (buf[i] == '\0') {
			return NULL;
		}
		
		if (!isWordTerminatingCharacter(buf[i])) {
			goodLen++;
		}
		else {
			if (goodLen > 0) {
				// this is a valid word.
				ret = malloc(sizeof(char) * goodLen);
				strncpy(ret, buf + startIndex, goodLen);
				
				memmove(buf, buf + goodLen + startIndex + 1, strlen(buf) - (goodLen + startIndex));
				break;
			} else {
				startIndex++;
			}
		}
	}
	
	return ret;
}

struct Entry *create_word_and_insert(char *word, struct HashTable *table) {
	// creates new Entry and inserts into hash table
	struct Entry *firstWordEntry = malloc(sizeof(struct Entry));
	firstWordEntry->word = word;
	hash_insert(table, firstWordEntry);
	return firstWordEntry;
}

void insert_associated_word(char *associatedWord, struct Entry *entry, struct HashTable *table) {
	// if entry doesn't have associatedWord yet, add it;
	// otherwise, increment the counter with it.
	struct associatedWord *newAssociatedWord = malloc(sizeof(struct associatedWord));
	newAssociatedWord->word = associatedWord;
	newAssociatedWord->numCount = 1;
	
	for (int i = 0; i < 100; i++) {
		if (entry->a[i] == NULL) {
			entry->a[i] = newAssociatedWord;
			break;
		}
	}
}

//open a file and load the hash table
void parseFile(char *fileName, struct HashTable *table){
	FILE *file = fopen(fileName, "r");
	
	if (file == NULL) {
		printf("Error\n");
		return;
	}
	
	unsigned int idx = 0;
	
	const int movingBufSize = 1024;;
	char *movingBuf = malloc(sizeof(char) * (movingBufSize + 1));
	
	movingBuf[movingBufSize + 1] = '\0';
	
	while (!feof(file)) {
		
		size_t read = fread(movingBuf + idx, sizeof(char), movingBufSize - idx, file);
		
		if (read == 0) {
			// no data read; i guess file is over;
			break;
		}
		
		char *firstWord = getWordFromBufferAndRemove(movingBuf);
		
		while ((firstWord)) {
			char *secondWord = getWordFromBufferAndRemove(movingBuf);
			if (!secondWord) break;
			
			struct Entry *firstWordEntry = hash_retrieve(table, firstWord);
			
			if (!firstWordEntry) {
				firstWordEntry = create_word_and_insert(firstWord, table);
			}
			
			insert_associated_word(secondWord, firstWordEntry, table);
			
			firstWord = secondWord;
		}
		
		idx = (unsigned int)strlen(movingBuf);
	}
	
	fclose(file);
}

//Load Data
void load_data(struct HashTable *table) {
	parseFile("/Users/max/Desktop/p/Markova/datas/data0", table);
}


char *randomString(int len) {
	char *buf = malloc(sizeof(char) * (len + 1));
	
	for (int i = 0; i < len; i++) {
		buf[i] = arc4random_uniform(25) + 0x41;
	}
	
	buf[len] = 0;
	return buf;
}

void test_hash_table() {
	
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

void generate_sentence_with_start(char *word, struct HashTable *table) {
	// Look up the starting word in the hash table
	// Generate a random number to pick an associated word based on how frequently
	// it occurs out of all of the associated words;
	// I.e. if you have "are" => 3, "you" => 5, "with" => 12,
	// and you generate a random number between [0, 3/(3 + 5 + 12)), then "are" is picked.
	// then you use "are" and repeat the process.
	// If you get a number between (3/(3+5+12), 3/(3+5+12) + 5/(3+5+12))], then "you" is picked
	// If you get a number between (3/(3+5+12) + 5/(3+5+12), 1], then "with" is picked.
	struct Entry *retrievedEntry;
	float randomNum = 0.0;
	int index = 0;
	float sum = 0.0;
	float associatedWordCount = 0.0;
	int insertCounting = 0;
	char *nextWord = word;
	
	while (nextWord != NULL) {
		retrievedEntry = hash_retrieve(table, nextWord);
		if (retrievedEntry == NULL) {
			break;
		}
		int frequency[100];
		char *allWords[100];
		index = 0;
		associatedWordCount = 0;
		sum = 0.0;
		insertCounting = 0;
		
		while (retrievedEntry->a[index] != NULL) {
			sum +=retrievedEntry->a[index]->numCount;
			associatedWordCount++;
			frequency[insertCounting] = retrievedEntry->a[index]->numCount;
			allWords[insertCounting] = retrievedEntry->a[index]->word;
			insertCounting++;
			index++;
		}
		
		randomNum = (float)rand()/(float)(RAND_MAX/(sum/associatedWordCount));
		
		int closeFrequencyIndex = 0;
		int closedFrequency = frequency[closeFrequencyIndex];
		
		for (int i = 0; i < associatedWordCount; i++){
			if (fabs((frequency[i]/associatedWordCount) - randomNum) == fabs((closedFrequency/associatedWordCount) - randomNum)) {
				int x = rand() % 2;
				//printf("Choose is: %d\n", x);
				if (x == 0) {
				} else {
					closedFrequency = frequency[i];
					closeFrequencyIndex = i;
				}
			} else if (fabs((frequency[i]/associatedWordCount) - randomNum) < fabs((closedFrequency/associatedWordCount) - randomNum)) {
				closedFrequency = frequency[i];
				closeFrequencyIndex = i;
			}
		}
		
		printf("%s ", allWords[closeFrequencyIndex]);
		nextWord = allWords[closeFrequencyIndex];
		
	}
	
	
}


int main(int argc, const char *argv[]) {
	//	test_hash_table();
	//	test_hash_function();
	
	struct HashTable *table = create_hash_table();
	load_data(table);
	hash_find_associated_word(table, "for");
	
	generate_sentence_with_start("the", table);
	
	return 0;
}
