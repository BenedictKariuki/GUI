/* bmp.c */

#include <bmp.h>
#include <images.h>

bmp_line* bmppixeldata(int8* data, int16 size, color_table* colors, int16 width, int16 height){
	int8* ptr;
	point* pptr;
	int8 byte, bit_high, bit_low;
	int16 n, line, cols, sz;
	bmp_line* ret;

	line = cols = 0;
	sz = sizeof(bmp_line) * height;
	ret = (bmp_line*)alloc(sz);
	if(!ret)
		return (bmp_line*)0;
	for(n=size, ptr=data; n; n--, ptr++){
		if(!(n % width)){
			line++;
			cols = 0;
		}
		byte = *ptr;
		bit_low = (byte & 0x0f);
		bit_high = (byte & 0xf0) >> 4;

		pptr = mkpoint(cols, line, bit_high);
		if(!pptr)
			return (bmp_line*)0;
		
		ret[line][cols++] = pptr;

		pptr = mkpoint(cols, line, bit_low);
		if(!pptr)
			return (bmp_line*)0;
		
		ret[line][cols++] = pptr;
	}
	return ret;
}

bitmap* parsebmp(int8* file){
    bitmap* bm;
    bmp_header* hdr;
    info_header* info_hdr;
    color_table* colors;
	bmp_line* lines;
    int16 size, n;

    if(!file)
        return (bitmap*)0;

    hdr = (bmp_header*)file;
    size = sizeof(struct s_bmp_header);
    info_hdr = (info_header*)(file + size);
    size = sizeof(color_table);
    colors = (color_table*)alloc(size);
    if(!colors)
        return (bitmap*)0;
    
    n = sizeof(struct s_bmp_header) + sizeof(struct s_info_header);
	size = sizeof(colors) * 4;
    copy($1 colors, file + n, size);

	n = (sizeof(bmp_line)) * info_hdr->height;
	size = sizeof(struct s_bitmap);
	size += n;
	bm = (struct s_bitmap*)alloc(size);
	if(!bm)
		return (bitmap*)0;

    bm->hdr = hdr;
    bm->info_hdr = info_hdr;
	bm->colors = colors;

	size = (bm->info_hdr->height * bm->info_hdr->width) / 2;
	if((bm->info_hdr->height * bm->info_hdr->width) % 2)
		size++;
	lines = bmppixeldata($1 hdr->offset, size, colors, info_hdr->width, info_hdr->height);
	// file+bm->hdr->offset
	if(!lines)
		return (bitmap*)0;
	copy($1 &bm->lines, $1 lines, n);

    return bm;
}


