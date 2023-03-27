#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE] = {0};

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		if (write(STDOUT_FILENO, buf, n) != n){
			err_sys("write error");
		}

		/*count how many characters there are in stdin */
		int i = 0;
		while(buf[i] != '\n'){
			i++;
		}
		/*print the count to stderr*/
		fprintf(stderr, "%d bytes\n", i++);

	}


	if (n < 0)
		err_sys("read error");

	exit(0);
}
