
#include <stdio.h>
#include <dirent.h>

int main(void)
{
	struct dirent *de;

	DIR *dr = opendir(".");
	while ((de = readdir(dr)) != NULL)
			printf("%s\n", de->d_name);

	closedir(dr);	
	return 0;
}
