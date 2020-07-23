#include <string.h>
#include "xu_ly_btree.h"
#include "main.h"
#include "string_deal.h"
#include "giao_dien.h"


void them_tu(dict_t * dict,char * word,char * meaning){
	btins(dict->dict,word,meaning,sizeof(char)*strlen(meaning));
}

void tao_dict_t(dict_t * dict,char * textName,char * dictName,char * dbName){
	strcpy(dict->name,dictName);
	strcpy(dict->path,dbName);
	dict->dict = btopn(dbName,0,1);
	btcls(dict->dict);
	mo_file(dict);
}

void mo_file(dict_t * dict){
	dict->dict = btopn(dict->path,0,1);
}


/* DELETE BUTTON ********/
void dictionary_delete_word(BTA *dict, char *word, GtkTextBuffer *buffer){
	char word_chuan_delete[WORD_MAX];
	//make_string_lower(word_chuan_delete,word);
	//trim_string(word_chuan_delete);
	strcpy(word_chuan_delete,word);
	chuanhoa(word_chuan_delete);

	BTint value;
	int check = bfndky(dict,word_chuan_delete,&value);
	if(check!= 0){
		gtk_text_buffer_set_text(buffer,"This word has never existed! Cannot delete!", -1);
		return;
	}

	btdel(dict,word_chuan_delete); 
	//xóa theo khóa của btree  

	gtk_text_buffer_set_text(buffer,"Deletion, done!:  ", -1);
	//xóa hết nội dung ở buffer cũ, show ra toàn bộ xâu "Deletion, done!" (do có -1)
	gtk_text_buffer_insert_at_cursor(buffer,word_chuan_delete,-1);
	//in ra ở ngay vị trí con trỏ màn hình hiện tại toàn bộ nội dung biến word_return (do có -1)
	//(cursor (n): con trỏ màn hình, DIFFERENT FROM pointer)
	delete_store_entry_completion(word_chuan_delete);
	//DONE
}
/* DELETE BUTTON ********/

/* ADD BUTTON ***********/

void dictionary_add_word(BTA *dict, char *word, char *meaning, GtkTextBuffer *buffer){
	char word_chuan_add[WORD_MAX];
	strcpy(word_chuan_add,word);
	chuanhoa(word_chuan_add);
	
	// make_string_lower(word_chuan_add,word);
	// trim_string(word_chuan_add);

	if(strlen(word_chuan_add) <=0 ) return;
	BTint value;
	int exist = bfndky(dict,word_chuan_add,&value);
	//the "value" variable contains the value of key "word_chuan_add"
	if(exist == 0) {
		//it means the word EXISTED in the tree.
		//we need to add the meaning as value;
		btdel(dict,word_chuan_add);
		delete_store_entry_completion(word_chuan_add);
		btins(dict,word_chuan_add,meaning,sizeof(char)*WORD_MAX);
	}else{
		btins(dict,word_chuan_add,meaning,sizeof(char)*WORD_MAX);
	}
	add_store_entry_completion(word_chuan_add);
}
/* ADD BUTTON ***********/
