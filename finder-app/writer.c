#include <fcntl.h>
#include <libgen.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	openlog(NULL, 0, LOG_USER);	

	if (argc != 3) {
		syslog(LOG_ERR, "Incorrect number of arguments: %d", argc);
		return 1;
	}

	char *filename = malloc(sizeof(char) * strlen(argv[1]));
	if (filename == NULL) {
		syslog(LOG_ERR, "Unable to allocate memory: %s", strerror(errno));
	}
	strcpy(filename, argv[1]);

	char *directory = dirname(argv[1]);
	char *text = argv[2];
	strcat(text, "\n");

	struct stat file_stat;
	if (stat(directory, &file_stat) == -1) {
		syslog(LOG_ERR, "Unable verify directory %s: %s", directory, strerror(errno));
		return 1;
	}

	int fd = open(filename, O_CREAT | O_WRONLY, 0755);
	if (write(fd, text, strlen(text)) == -1) {
		syslog(LOG_ERR, "Uable to write text to file %s: %s", filename, strerror(errno));
		return 1;
	}

	if (close(fd) == -1) {
		syslog(LOG_ERR, "Unable to close file %s: %s", filename, strerror(errno));
		return 1;
	}

	free(filename);
	closelog();

	return 0;
}
