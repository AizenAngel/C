#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{ //NODE of the list and it's fields
  char tag[20];
  int br;
  struct Node*next;
}NODE;

void error(){     //if something goes wrong, this function gives user a message
  fprintf(stderr,"-1\n");
  exit(EXIT_FAILURE);
}

NODE* make_new(char *s){ //creates a new NODE, for new html tag
  NODE*new = malloc(sizeof(NODE));
  if(new == NULL){
    error();
  }
  strcpy(new->tag, s);
  new->br = 1;
  new->next = NULL;

  return new;
}

void add_new(NODE **list, char *a){ //adds new NODE to the list (adds new tag)
  NODE *new = make_new(a);
  new->next = *list;
  *list = new;
}


void print(NODE*list){ //prints all the tags and how many times they appear in .txt file
  if(list == NULL){
    return;
  }

  printf("%s: %d\n", (list)->tag, (list)->br);
  print(list->next);
}

NODE* inside(NODE*list, char*a){ //function that determines if the tag is already in the list or not.
  NODE* none = make_new("-1");   // If it is, we verify that by returning it's address in memory.
  while(list != NULL){           // Otherwise we return NODE with tag = "-1".
    if(strcmp(list->tag, a) == 0)
      return list;
    list = list->next;
  }
  return none;
}

int main(int argc, char**argv){

  if(argc != 2) // We read the file with html tags from command line. It has to be in the same
    error();   // folder as our program and it has to have extension .txt

  //char a[20];
  NODE*list = NULL;

  FILE *in;
  in = fopen(argv[1],"r");
  if(in == NULL)
    error();


  int flag = 0,check = 0, i = 0;
  char *tag1, *empty;

  tag1 = malloc(20*sizeof(char));
  empty = malloc(20*sizeof(char));
  char ch;

  while((ch = fgetc(in))!= EOF){
    if(ch == '<')
      flag = 1;

    if(ch == '>' && flag == 0)
      continue;

    if(ch == '>' || (ch == ' ' && flag == 1)){
      flag = 0;
      check = 1;
    }

    if(flag == 1){
      if(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('1' <= ch && ch <= '9')){
        tag1[i] = ch;
        //printf("%c",ch);
        i++;
      }
    }

    if(check){
    //  printf("%s\n",tag1);
      NODE*check1 = inside(list,tag1);
      if(strcmp((check1->tag),"-1") == 0)
        add_new(&list,tag1);
      else (check1->br) = (check1->br) + 1;
      free(tag1);
      check = 0;
      flag = 0;
      i = 0;
      tag1 = malloc(20*sizeof(char));
    }
  }

  print(list);

  return 0;
}
