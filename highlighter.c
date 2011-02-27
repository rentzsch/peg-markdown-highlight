#include <stdio.h>
#include <string.h>
#include "markdown_parser.h"


#define READ_BUFFER_LEN 1024
char *getUTF8FromStdin()
{
	char buffer[READ_BUFFER_LEN];
	size_t content_len = 1;
	char *content = malloc(sizeof(char) * READ_BUFFER_LEN);
	content[0] = '\0';
	
	while (fgets(buffer, READ_BUFFER_LEN, stdin))
	{
		content_len += strlen(buffer);
		content = realloc(content, content_len);
		strcat(content, buffer);
	}
	
	return content;
}


void outputResult(element *elem[])
{
	element *cursor;
	bool firstType = true;
	int i;
	for (i = 0; i < NUM_TYPES; i++)
	{
		cursor = elem[i];
		if (cursor == NULL)
			continue;
		
		if (!firstType)
			printf("|");
		printf("%i:", i);
		
		bool firstSpan = true;
		while (cursor != NULL)
		{
			if (!firstSpan)
				printf(",");
			printf("%ld-%ld", cursor->pos, cursor->end);
			cursor = cursor->next;
			firstSpan = false;
		}
		firstType = false;
	}
}


int main(int argc, char * argv[])
{
	int extensions = 0;
	element **result;
	
	char *md_source = getUTF8FromStdin();
	markdown_to_elements(md_source, extensions, &result);
	outputResult(result);
	
    return(0);
}