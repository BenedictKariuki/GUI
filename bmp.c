/* bmp.c */

#include <bmp.h>
#include <omnistd.h>

int8 *addbmp(int8 *file)
{
	int8 *ret, *p;
	int16 size;

	if (!file)
		return $1 0;
	size = stringlen(file);
	if (!size)
		return $1 0;
	ret = $1 alloc(16);
	ZERO($1 ret, 16);
	STRINGCOPY($1 ret, $1 file, size);
	p = ret + size;
	STRINGCOPY($1 p, $1 ".bmp", 4);

	return ret;
}

boolean drawbmp(bitmap *bmp, int16 x, int16 y)
{
	int16 size;
	int16 width, fd;
	int8 *file;
	point *pptr;
	int8 byte, bit_high, bit_low;
	int16 n, line, col;

	if (!bmp)
		return false;

	file = bmp->filename;

	fd = open(file, bmp->hdr->offset);
	if (!fd)
		return false;

	size = (bmp->info_hdr->height * bmp->info_hdr->width) / 2;
	if ((bmp->info_hdr->height * bmp->info_hdr->width) % 2)
		size++;

	width = (bmp->info_hdr->width / 2);

	line = bmp->info_hdr->height;
	col = 0;

	for (n = size; n; n--)
	{

		if (!(n % width))
		{
			line--;
			col = 0;
		}
		byte = read(fd);

		bit_low = (byte & 0x0f);
		bit_high = (byte & 0xf0) >> 4;

		pptr = mkpoint((col + x), (line + y), GETCOLOR(bmp, bit_high));

		if (pptr)
		{
			drawpoint(pptr);
		}
		col++;
		pptr = mkpoint((col + x), (line + y), GETCOLOR(bmp, bit_low));

		if (pptr)
		{
			drawpoint(pptr);
		}
		freeall();
		col++;
	}
	close(fd);
	return true;
}

bitmap *parsebmp(int8 *bmp_file)
{
	bitmap *bm;
	bmp_header *hdr;
	info_header *info_hdr;
	color_table *colors;
	int16 size, n, fd;
	int8 *filename;
	int8 *file, *p;

	if (!bmp_file)
		return (bitmap *)0;

	filename = addbmp(bmp_file);
	fd = open(filename, 0);
	// PRINTF($1 "File descriptor: %x\n", fd);
	if (!fd)
		return (bitmap *)0;

	file = (int8 *)alloc(128); // hdr + info_hdr + color_table = 118
	if (!file)
	{
		close(fd);
		return (bitmap *)0;
	}
	ZERO(file, 128);

	for (n = 118, p = file; n; n--, p++)
	{
		*p = read(fd);
	}

	// for (int8 i = 14; i < 54; i++)
	// {
	// 	if (!(i % 4))
	// 		print($1 "\r\n");
	// 	PRINTF($1 "Byte %x: %x  ", i, file[i]);
	// }
	// print($1 "\n");

	close(fd);

	hdr = (bmp_header *)file;

	size = sizeof(struct s_bmp_header);
	info_hdr = (info_header *)(file + size);
	// print the raw bytes
	// print($1 "INFO HEADER:\r\n");
	// int8 *bytes;
	// bytes = (int8 *)info_hdr;
	// for (int8 i = 0; i < 40; i++)
	// {
	// 	if (!(i % 4))
	// 		print($1 "\r\n");
	// 	PRINTF($1 "Byte %x: %x  ", i, bytes[i]);
	// }

	size = sizeof(color_table);
	colors = (color_table *)alloc(size);
	if (!colors)
		return (bitmap *)0;

	n = sizeof(struct s_bmp_header) + sizeof(struct s_info_header);

	COPY($1 colors, $1(file + n), size);

	size = sizeof(struct s_bitmap);
	bm = (bitmap *)alloc(size);
	if (!bm)
		return (bitmap *)0;

	bm->hdr = hdr;
	bm->info_hdr = info_hdr;
	bm->colors = colors;
	bm->filename = filename;

	return bm;
}
