#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"
int find_idx(char table_name[]);
int make_number(char number[]);
int getcommand();
int check1=0;
bool hash_less(const struct hash_elem *a, const struct hash_elem *b,void *aux);
unsigned hash_int_2();
void about_list();
void about_hash();
void hash_create();
void about_bitmap();
void about_create();
void about_delete();
void about_dumpdata(char table_name[]);
struct list List[20];
struct hash Hash[20];
struct bitmap *Bitmap[20];
char list_Name[10][100];
char hash_Name[10][100];
char Bitmap_Name[10][100];
int list_cnt , hash_cnt , bitmap_cnt = 0;
char command[100],str1[100],str2[100],str3[100],str4[100],str5[100],str6[100];
int check;
hash_hash_func hash_func;
hash_action_func hash_action;
hash_action_func square;
hash_action_func triple;
unsigned hash_func(const struct hash_elem *e,void *aux);
struct hashnode{
	struct hash_elem elem;
	int data;
};
void hash_action(struct hash_elem *e, void *aux){
	free(e);
}
void square(struct hash_elem *e,void *aux){
	struct hashnode *f = hash_entry(e,struct hashnode,elem);
	f->data *= f->data;
}
void triple(struct hash_elem *e,void *aux){
	struct hashnode *f = hash_entry(e,struct hashnode,elem);
	f->data *= f->data * f->data;
}
int main(){
	while(1){
		fgets(command,100,stdin);
		int ret = getcommand();
		if(ret==1)
			return 0;
	}
}
int getcommand(){
	check = sscanf(command,"%s %s %s %s %s %s",str1,str2,str3,str4,str5,str6);
	if(!strcmp("quit",str1))
		return 1;
	else if(!strncmp("list",str1,4))
		about_list();
	else if(!strncmp("bitmap",str1,6))
		about_bitmap();
	else if(!strncmp("hash",str1,4))
		about_hash();
	else if(!strncmp("create",str1,6))
		about_create();
	else if(!strncmp("dumpdata",str1,8))
		about_dumpdata(str2);
	else if(!strncmp("delete",str1,6))
		about_delete(str2);
	else
		return 1;
}
void about_list(){
	char list_name[50];
	int num,num1,num2;
	int list_idx = find_idx(str2);
	int list_idx2;
	strcpy(list_name,str2);
	if(!strcmp("list_insert",str1)){
		struct linkedlist *node = (struct linkedlist *)malloc(sizeof(struct linkedlist));
		num = make_number(str3);
		num1 = make_number(str4);
		node->data = num1;
		struct list_elem * e = list_peek(&List[list_idx],num);
		list_insert(e,&(node->elem));
	}
	else if(!strcmp("list_splice",str1)){
		list_idx2 = find_idx(str4);
		num = make_number(str3);
		num1 = make_number(str5);
		num2 = make_number(str6);
		struct list_elem *before = list_peek(&List[list_idx],num);
		struct list_elem *first = list_peek(&List[list_idx2],num1); 
		struct list_elem *last = list_peek(&List[list_idx2],num2);
		list_splice(before,first,last);
	}
	else if(!strcmp("list_push_front",str1)){
		struct linkedlist *node = (struct linkedlist *)malloc(sizeof(struct linkedlist));
		num = make_number(str3);
		node->data = num;
		list_push_front(&(List[list_idx]),&(node->elem));
	}
	else if(!strcmp("list_push_back",str1)){
		struct linkedlist *node = (struct linkedlist *)malloc(sizeof(struct linkedlist));
		num = make_number(str3);
		node->data = num;
	int num,num1,num2;
	int list_idx = find_idx(str2);
		list_push_back(&(List[list_idx]),&(node->elem));
	}
	else if(!strcmp("list_remove",str1)){
		num = make_number(str3);
		struct list_elem *remove = list_peek(&List[list_idx],num);
		list_remove(remove); // free?
	}
	else if(!strcmp("list_pop_front",str1))
		list_pop_front(&List[list_idx]);
	else if(!strcmp("list_pop_back",str1))
		list_pop_back(&List[list_idx]);
	else if(!strcmp("list_front",str1)){
	int list_idx = find_idx(str2);
		struct list_elem * e = list_front(&List[list_idx]);
		struct linkedlist *f = list_entry(e,struct linkedlist,elem);
		printf("%d\n",f->data);
	}
	else if(!strcmp("list_back",str1)){
		struct list_elem *e = list_back(&List[list_idx]);
		struct linkedlist *f = list_entry(e,struct linkedlist,elem);
		printf("%d\n",f->data);
	}
	else if(!strcmp("list_size",str1))
		printf("%u\n",list_size(&List[list_idx]));
	else if(!strcmp("list_empty",str1)){
		if(list_empty(&List[list_idx]))
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("list_reverse",str1))
		list_reverse(&(List[list_idx]));
	else if(!strcmp("list_sort",str1))
		list_sort(&List[list_idx],less_func,NULL);
	else if(!strcmp("list_insert_ordered",str1)){
		num = make_number(str3);
		struct linkedlist *node = (struct linkedlist *)malloc(sizeof(struct linkedlist));
		node->data = num;
		list_insert_ordered(&List[list_idx],&(node->elem),less_func,NULL);
	}
	else if(!strcmp("list_unique",str1)){
		if(check==3){
			list_idx2 = find_idx(str3);
			list_unique(&List[list_idx],&List[list_idx2],less_func,NULL);
		}
		else
			list_unique(&List[list_idx],NULL,less_func,NULL);
	}
	else if(!strcmp("list_max",str1)){
		struct list_elem *e = list_max(&List[list_idx],less_func,NULL);
		struct linkedlist *f = list_entry(e,struct linkedlist,elem);
		printf("%d\n",f->data);
	}
	else if(!strcmp("list_min",str1)){
		struct list_elem *e = list_min(&List[list_idx],less_func,NULL);
		struct linkedlist *f = list_entry(e,struct linkedlist,elem);
		printf("%d\n",f->data);
	}
	else if(!strcmp("list_swap",str1)){
		num = make_number(str3);
		num1 = make_number(str4);
		struct list_elem *r = list_peek(&List[list_idx],num);
		struct list_elem *l = list_peek(&List[list_idx],num1);
	int list_idx = find_idx(str2);
		list_swap(r,l);
	}
	else if(!strcmp("list_shuffle",str1))
		list_shuffle(&List[list_idx]);
	else
		return;
}
void about_hash(){
	char hash_name[50];
	int hash_idx = find_idx(str2);
	int num;
	if(!strcmp("hash_insert",str1)){
		struct hashnode *node = (struct hashnode *)malloc(sizeof(struct hashnode));
	int num,num1,num2;
	int list_idx = find_idx(str2);
		num = make_number(str3);
		node->data = num;
		hash_insert(&Hash[hash_idx],&node->elem);
	}
	else if(!strcmp("hash_replace",str1)){
		struct hashnode *node = (struct hashnode *)malloc(sizeof(struct hashnode));
		num = make_number(str3);
		node->data = num;
		hash_replace(&Hash[hash_idx],&node->elem);
	}
	else if(!strcmp("hash_find",str1)){
		struct hashnode *node = (struct hashnode *)malloc(sizeof(struct hashnode));
		struct hash_elem *e = NULL;
		num = make_number(str3);
		node -> data = num;
		e = hash_find(&Hash[hash_idx],&node->elem);
		if(e==NULL)
			return;
		struct hashnode *f = hash_entry(e,struct hashnode,elem);
		printf("%d\n",f->data);
	}
	else if(!strcmp("hash_delete",str1)){
		struct hashnode *node = (struct hashnode *)malloc(sizeof(struct hashnode));
	int num,num1,num2;
	int list_idx = find_idx(str2);
		num = make_number(str3);
		node->data = num;
		hash_delete(&Hash[hash_idx],&node->elem);
	}
	else if(!strcmp("hash_clear",str1))
		hash_clear(&Hash[hash_idx],hash_action);
	else if(!strcmp("hash_size",str1))
		printf("%u\n",hash_size(&Hash[hash_idx]));
	else if(!strcmp("hash_empty",str1)){
		if(hash_empty(&Hash[hash_idx]))
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("hash_apply",str1)){
		if(!strcmp(str3,"square"))
			hash_apply(&Hash[hash_idx],square);
		else if(!strcmp(str3,"triple"))
			hash_apply(&Hash[hash_idx],triple);
	}
	else
		return;
}
void about_bitmap(){
	int bitmap_idx = find_idx(str2);
	int num;
	if(!strcmp("bitmap_size",str1))
		printf("%d\n",bitmap_size(Bitmap[bitmap_idx]));
	else if(!strcmp("bitmap_set",str1)){
		if(!strcmp("true",str4))
			num = 1;
		else if(!strcmp("false",str4))
			num = 0 ;
		else
			num = atoi(str4);
		bitmap_set(Bitmap[bitmap_idx],atoi(str3),num);
	}
	else if(!strcmp("bitmap_mark",str1)){
		num = atoi(str3);
		bitmap_mark(Bitmap[bitmap_idx],num);
	}
	else if(!strcmp("bitmap_reset",str1))
		bitmap_reset(Bitmap[bitmap_idx],atoi(str3));
	else if(!strcmp("bitmap_flip",str1))
		bitmap_flip(Bitmap[bitmap_idx],atoi(str3));
	else if(!strcmp("bitmap_test",str1)){
		if(bitmap_test(Bitmap[bitmap_idx],atoi(str3)))
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("bitmap_set_all",str1)){
		int n;
		if(!strcmp("true",str3))
			n = 1;
		else if(!strcmp("false",str3))
			n = 0;
		else
			n = atoi(str3);
		bitmap_set_all(Bitmap[bitmap_idx],n);
	}

	else if(!strcmp("bitmap_set_multiple",str1) || !strcmp("bitmap_count",str1)){
		int n;
		if(!strcmp("true",str5))
			n = 1;
		else if(!strcmp("false",str5))
			n = 0;
		else
			n = atoi(str5);
		if(!strcmp("bitmap_set_multiple",str1))
			bitmap_set_multiple(Bitmap[bitmap_idx],atoi(str3),atoi(str4),n);
		else
			printf("%d\n",bitmap_count(Bitmap[bitmap_idx],atoi(str3),atoi(str4),n));
	}
	else if(!strcmp("bitmap_contains",str1)){
		int n;
		if(!strcmp("true",str5))
			n = 1;
		else if(!strcmp("false",str5))
			n = 0;
		else
			n = atoi(str5);
		bool check = bitmap_contains(Bitmap[bitmap_idx],atoi(str3),atoi(str4),n);
		if(check)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("bitmap_any",str1)){
		if(bitmap_any(Bitmap[bitmap_idx],atoi(str3),atoi(str4)))
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("bitmap_none",str1)){
		if(bitmap_none(Bitmap[bitmap_idx],atoi(str3),atoi(str4)))
			printf("true\n");
		else
			printf("false\n");
	}

	else if(!strcmp("bitmap_all",str1)){
		if(bitmap_all(Bitmap[bitmap_idx],atoi(str3),atoi(str4)))
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp("bitmap_scan",str1)){
		int n;
		if(!strcmp("true",str5))
			n = 1;
		else if(!strcmp("false",str5))
			n = 0;
		else
			n = atoi(str5);
		printf("%u\n",bitmap_scan(Bitmap[bitmap_idx],atoi(str3),atoi(str4),n));
		
	}

	else if(!strcmp("bitmap_scan_and_flip",str1)){
		int n;
		if(!strcmp("true",str5))
			n = 1;
		else if(!strcmp("false",str5))
			n = 0;
		else
			n = atoi(str5);
		printf("%u\n",bitmap_scan_and_flip(Bitmap[bitmap_idx],atoi(str3),atoi(str4),n));
		
	}
	else if(!strcmp("bitmap_dump",str1))
		bitmap_dump(Bitmap[bitmap_idx]);
	else if(!strcmp("bitmap_expand",str1))
			bitmap_expand(Bitmap[bitmap_idx],atoi(str3));
	else
		return;		
}
void about_create(){
	if(!strcmp("list",str2))
		list_create();
	else if(!strcmp("hashtable",str2))
		hash_create();
	else if(!strcmp("bitmap",str2)){
		Bitmap[bitmap_cnt] = bitmap_create(atoi(str4));
		strcpy(Bitmap_Name[bitmap_cnt++],str3);
	}
	else
		return;
}
void list_create(){
	list_init(&List[list_cnt]);
	int num,num1,num2;
	int list_idx = find_idx(str2);
	strcpy(list_Name[list_cnt++],str3);
	return;
}
void hash_create(){
	hash_init(&Hash[hash_cnt],hash_func,hash_less,NULL);
	strcpy(hash_Name[hash_cnt++],str3);
	return;
}
void about_dumpdata1(char table_name[]){
	int hash_idx = find_idx(table_name);
	if(hash_empty(&Hash[hash_idx]))
		return;
	struct hash_iterator i;
	hash_first(&i,&Hash[hash_idx]);
	while(hash_next(&i)){
		struct hashnode *f = hash_entry(hash_cur(&i), struct hashnode,elem);
		printf("%d ",f->data);
	}
	printf("\n");
}
void about_dumpdata2(char table_name[]){
	int bitmap_idx = find_idx(table_name);
	int size = bitmap_size(Bitmap[bitmap_idx]);
	if(size == 0)
		return;
	int i;
	for(i = 0 ; i < size ; i++)
		printf("%d",bitmap_test(Bitmap[bitmap_idx],i));
	printf("\n");
}

void about_dumpdata(char table_name[]){
	if(!strncmp(table_name,"hash",4)){
		about_dumpdata1(table_name);
		return;
	}
	else if(!strncmp(table_name,"bm",2)){
		about_dumpdata2(table_name);
		return;
	}
	int list_idx = find_idx(table_name);
	struct list_elem *e;
	if(list_empty(&List[list_idx]))
		return;
	for(e = list_begin(&List[list_idx]) ; e != list_end(&List[list_idx]) ; e = list_next(e)){
		struct linkedlist *f = list_entry(e,struct linkedlist,elem);
		printf("%d ",f->data);
	}
	printf("\n");
}
void about_delete(char table_name[]){
	if(!strncmp(table_name,"list",4))
		list_delete(&List[find_idx(table_name)]);
	else if(!strncmp(table_name,"hash",4))
		hash_destroy(&Hash[find_idx(table_name)],hash_action);
	else if(!strncmp(table_name,"bitmap",6))
		bitmap_destroy(Bitmap[find_idx(table_name)]);
}
int find_idx(char table_name[]){
	int i;
	for(i = 0 ; i < list_cnt ; i++){
		if(!strcmp(list_Name[i],table_name))
			return i;
	}
	for(i = 0 ; i < hash_cnt ; i++){
		if(!strcmp(hash_Name[i],table_name))
			return i;
	}
	for(i = 0 ; i< bitmap_cnt ; i++){
		if(!strcmp(Bitmap_Name[i],table_name))
			return i;
	}
	return -1;
}
int make_number(char number[]){
	return atoi(number);
}
bool hash_less(const struct hash_elem *a,const struct hash_elem *b,void *aux){
	struct hashnode *n1 = hash_entry(a,struct hashnode,elem);
	struct hashnode *n2 = hash_entry(b,struct hashnode,elem);

	if(n1->data < n2->data)
		return true;
	else
		return false;
}
unsigned hash_func(const struct hash_elem *e,void *aux){
	struct hashnode *f = hash_entry(e,struct hashnode,elem);
	return hash_int(f->data);
}
unsigned hash_int_2(int num){
	return num%11;
}
