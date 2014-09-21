/*
 * Copyright (c) 2014 Jeff Boody
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "libmd5/md5.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE* f = fopen(argv[1], "r");
	if(f == NULL)
	{
		printf("fopen %s failed\n", argv[1]);
		return EXIT_FAILURE;
	}

	// initialize the md5 sum
	struct MD5Context ctx;
	MD5Init(&ctx);

	// compute the md5 sum
	unsigned char buf[4096];
	unsigned int  len = fread(buf, sizeof(unsigned char), 4096, f);
	while(len > 0)
	{
		MD5Update(&ctx, buf, len);
		len = fread(buf, sizeof(unsigned char), 4096, f);
	}

	// check for errors
	int errno = ferror(f);
	if(errno)
	{
		printf("fread failed errno=%i\n", errno);
		fclose(f);
		return EXIT_FAILURE;
	}
	fclose(f);

	// compute final md5 sum
	unsigned char d[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
	                        0, 0, 0, 0, 0, 0, 0, 0 };
	MD5Final(d, &ctx);

	printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x  %s\n",
	       d[0],  d[1],  d[2],  d[3],
	       d[4],  d[5],  d[6],  d[7],
	       d[8],  d[9],  d[10], d[11],
	       d[12], d[13], d[14], d[15], argv[1]);

	return EXIT_SUCCESS;
}
