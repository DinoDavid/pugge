/* This code is licensed under the Unlicense; see LICENSE for details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pugge.h"
#include "util.h"

struct question *parse_file(char *filename, struct question *q);
struct question *parse_line(char *line, struct question *q);

struct question *
parse_all_files(char **files)
{
	int i;
	struct question *first, *last;

	first = last = calloc(1, sizeof(first));
	if (!first)
		kill_program("parse_all_files: calloc failed\n");

	for (i = 0; files[i]; i++)
		last = parse_file(files[i], last);

	return first;
}

struct question *
parse_file(char *filename, struct question *q)
{
	FILE *file;
	char *buffer;

	file = fopen(filename, "r");
	if (!file)
		kill_program("file not found: %s\n", filename);

	buffer = calloc(MAX_LEN, sizeof(char));
	while (fgets(buffer, MAX_LEN, file))
		q = parse_line(buffer, q);

	free(buffer);
	return (void*)0;
}

struct question *
parse_line(char *line, struct question *q)
{
	size_t len;

	if(line[0] == '#')
		return q;

	if(line[0] == '\n' && !q->text)
		return q;

	if(!q->text){
		len = strlen(line);
		q->text = calloc(len+1, sizeof(char));
		/*TODO test calloc*/
		strncpy(q->text, line, len);
		return q;
	}

	printf("TODO parse: %s", line);

	return q;
}
