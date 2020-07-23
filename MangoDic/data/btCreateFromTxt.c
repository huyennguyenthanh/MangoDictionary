#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cmake-btree/inc/btree.h"

#define TMP_MAX_LEN 100000
#define WORD_MAX_LEN 100000
#define MEANING_MAX_LEN 100000

void wordExtract(char word[], char meaning[], char tmp[], const char tok) {
  int len = strlen(tmp);
    
  for (int i = 0; i < strlen(tmp); i++) {
    if (tmp[i] == tok) {
      strcpy(meaning, tmp + i);
      tmp[i] = '\0';
      strcpy(word, tmp + 1); // skip '@' at the start of tmp
      word[strlen(word) - 1] = '\0'; // remove trailing space
      return;
    }
  }
}

void test()
{
  char word[] = "a";
  char meaning[WORD_MAX_LEN];
  BTA *dict = btopn("../BTree_dict.dat", 0, FALSE);
  btpos(dict, ZSTART);
  int rsize = 0;
	btsel(dict,word,meaning,sizeof(char)*WORD_MAX_LEN,&rsize);
  printf("%s",meaning);
  btcls(dict);
}

int main() {
  // FILE *inp = fopen("../short_demo.txt", "r");
  // BTA *dict = btcrt("../BTree_dict.dat", 0, FALSE);

  // if (!inp) {
  //   printf("ERR - can not open file\n");
  //   return 0;
  // }

  // if (!dict) {
  //   printf("ERR - can not create btree file\n");
  //   return 0;
  // }
    
  // btdups(dict, FALSE); // no duplication allowed
    
  // char tmp[TMP_MAX_LEN];
  // char word[WORD_MAX_LEN], meaning[MEANING_MAX_LEN];
  // int ready = 0, num = 0;

  // word[0] = '\0'; meaning[0] = '\0';
  
  // while(!feof(inp)) {
  //   fgets(tmp, TMP_MAX_LEN, inp);

  //   // tmp[0] != '@' -> get meaning
  //   while(tmp[0] != '@') {
  //     strcat(meaning, tmp);
  //     if(feof(inp)) break;
  //     fgets(tmp, TMP_MAX_LEN, inp);
  //     if(!ready) ready = 1;
  //   }

  //   // insert into btree when word and meaning are ready
  //   if (ready) {
  //     btins(dict, word, meaning, strlen(meaning) + 1);
  //     printf("\n**%s**\n_%s_\n", word, meaning);
  //     // put word n meaning in not ready state again
  //     word[0] = '\0'; meaning[0] = '\0';
  //     ready = 0; num++;
  //   }
    
  //   // tmp[0] == '@' -> get word
  //   if(tmp[0] == '@') {
  //     wordExtract(word, meaning, tmp, '/');
  //   }
  // }

  // printf("Created words.data with %d words\n", num);

	// btpos(dict, ZSTART);
  // BTint value;
  // while(bnxtky(dict, word, &value) == 0) {
  //  //printf("\n%s\n",word);
  // }
  
  // fclose(inp);
  // btcls(dict);
  test();

  return 0;
}
