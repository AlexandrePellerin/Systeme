#include <stdio.h>
#include "exo1.h"

int lire_deux_octets(int fd, uint16 *val)
{
	int n = read(fd, val, sizeof(uint16));
	return n;
}

