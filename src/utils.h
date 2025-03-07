#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

// Checks if a string has a suffix, case-sensitive.
#define HAS_SUFFIX(str, ext, extLen) (strncmp(str + (strlen(str) - extLen), ext, extLen) == 0)

// Checks if a string has a suffix, case-insensitive.
#define HAS_SUFFIX_CI(str, ext, extLen) (strncmpci(str + (strlen(str) - extLen), ext, extLen) == 0)

#ifdef __cplusplus
extern "C" {
#endif

int StringToInt(int *out, char *s);
int ColorEqual(unsigned char *a, unsigned char *b);
unsigned char* GetCharData(unsigned char *data, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
char* ReadTextFile(const char* path);
bool StringStartsWith(const char* prefix, const char* str);
uint8_t* ScalePixelArray(uint8_t* src, uint32_t src_w, uint32_t src_h, uint32_t target_w, uint32_t target_h);
int strncmpci(const char* s1, const char* s2, size_t n); // Case insensitive string compare upto n, returns 0 if true

#ifdef __cplusplus
}
#endif

#ifdef UTILS_IMPLEMENTATION

int strncmpci(const char* s1, const char* s2, size_t n) {
	while (n && *s1 && ( tolower(*s1) == tolower(*s2) )) {
		++s1;
		++s2;
		--n;
	}
	if (n == 0) return 0;
	else return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

// https://stackoverflow.com/a/299305/14516016
uint8_t* ScalePixelArray(uint8_t* src, uint32_t src_w, uint32_t src_h, uint32_t target_w, uint32_t target_h) {
	uint8_t* dest = (uint8_t*) malloc(target_w * target_h * 4 * sizeof(uint8_t));
	for (uint32_t x = 0; x < target_w; ++x) {
		for (uint32_t y = 0; y < target_h; ++y) {
			uint8_t* srcPixel = GetCharData(src, x * src_w / target_w, y * src_h / target_h, src_w, src_h);
			uint8_t* destPixel = GetCharData(dest, x, y, target_w, target_h);
			*(destPixel + 0) = srcPixel[0];
			*(destPixel + 1) = srcPixel[1];
			*(destPixel + 2) = srcPixel[2];
			*(destPixel + 3) = srcPixel[3];
		}
	}
	return dest;
}

bool StringStartsWith(const char* prefix, const char* str) {
	return (prefix != NULL && str != NULL && strncmp(prefix, str, strlen(prefix)) == 0);
}

int StringToInt(int *out, char *s) {
	char *end;
	if (s[0] == '\0') return -1;
	long l = strtol(s, &end, 10);
	if (l > INT_MAX) return -2;
	if (l < INT_MIN) return -3;
	if (*end != '\0') return -1;
	*out = l;
	return 0;
}

int ColorEqual(unsigned char *a, unsigned char *b) {
	if (
		a != NULL            &&
		b != NULL            &&
		*(a + 0) == *(b + 0) &&
		*(a + 1) == *(b + 1) &&
		*(a + 2) == *(b + 2) &&
		*(a + 3) == *(b + 3)
	) {
		return 1;
	}
	return 0;
}

unsigned char* GetCharData(unsigned char *data, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	if (x < w && y < h) {
		return data + ((y * w + x) * 4);
	}
	return NULL;
}

char* ReadTextFile(const char* path) {
	size_t fsize = 0;
	char* str = NULL;

	FILE* file = fopen(path, "rb");
	if (file == NULL) goto onEnd;

	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	str = (char *)malloc(fsize + 1);
	if (str == NULL) goto onEnd;

	fread(str, 1, fsize, file);
	str[fsize] = 0;

onEnd:
	fclose(file);
	return str;
}

#endif // UTILS_IMPLEMENTATION
