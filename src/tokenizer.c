#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int space_char(char c)
{
  return (c == ' ' || c == '\t') && c != '\0';
}

int non_space_char(char c)
{
  return c != ' ' && c != '\t' && c != '\0';
}

char *word_start(char *s)
{
  for(int i = 0; space_char(*s); s++)
    {
      
    }
  return s;
    }

char *word_terminator(char *word)
{
  int i = 0;
  while(*(word + i)){
    if(space_char(*(word + i))){
      return word + i;
    }
    i++;
  }
  return word + i;
}

int count_words(char *s)
{
  int inWord = 0;
  int count = 0;
  while(*s != '\0')
    {
      if(non_space_char(*s) && inWord == 0)
	{
	  count++;
	  inWord = 1;
	}
      else if(space_char(*s) == 1 && inWord == 1)
	{
	  inWord = 0;
	}
      s++;
    }
  return count;
}

char *copy_str(char *inStr, short len)
{
  //I allocate memory for the length of the string + 1 for the terminating character
  char *out_str = (char*) malloc(sizeof(char) * len + 1);
  //this causes an error if out_str is empty 
  if(!out_str)
    {
      fprintf(stderr, "copy_str: Memory allocation error!");
      exit(EXIT_FAILURE);
    }

  char *c = out_str;

  //iterates through in_str and copies it over to out_str using c as a temp variable
  for(short i = 0; i < len; i++)
    {
      *c = *inStr;

      if(*c == '\0')
	{
	  break;
	}
      c++;
      inStr++;
    }

  *c = '\0';

  return out_str;
}

char **tokenizer(char* str)
{
  //finding the number of words and allocating memory for tokens array
  int words = count_words(str);
  char **tokens = malloc(sizeof(char*) * (words + 1));

  //this causes an error if out_str is empty
  if(!tokens)
    {
      fprintf(stderr, "tokenize: Memory allocation error!");
      exit(EXIT_FAILURE);
    }

  //This loop popoulates the token array by using the methods we wrote previously 
  str = word_start(str);
  for(int i = 0; i < words; i++)
    {
      char* terminator = word_terminator(str);
      tokens[i] = copy_str(str, terminator - str);

      str = word_start(terminator);
    }

  // point the last pointer to 0
  char **terminator = tokens + words;
  *terminator = 0;

  return tokens;
}

void print_tokens(char ** tokens)
{
  printf("{\n");
  for(char** token = tokens; *token != 0; token++)
    printf("\t[%ld] '%s'\n", token - tokens, *token);
  printf("}\n\n");
}

void free_tokens(char **tokens)
{
  int i = 0;
  while(tokens[i]){
    free(tokens[i]);
    i++;
  }
  //free the pointer array
  free(tokens);
}
