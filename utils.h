/*
***************************************************************************
*
* Author: Teunis van Beelen
*
* Copyright (C) 2009 - 2023 Teunis van Beelen
*
* Email: teuniz@protonmail.com
*
***************************************************************************
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************
*/



#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


void remove_trailing_spaces(char *);
void remove_leading_spaces(char *);
void trim_spaces(char *);
/* removes trailing zero's from one or more occurrences of a decimal fraction in a string */
void remove_trailing_zeros(char *);
void convert_trailing_zeros_to_spaces(char *);
void remove_leading_chars(char *, int);
void remove_trailing_chars(char *, int);

/* Inserts a copy of substr into str. The substring is the portion of substr that begins at */
/* the character position subpos and spans sublen characters (or until the end of substr */
/* if substr is too short). */
void str_insert_substr(char *str, int pos, int len, const char *substr, int subpos, int sublen);

/* Replaces the nth occurrence of dest_substr in str with src_substr. */
/* If n = -1, all occurrences will be replaced. */
/* len is the buffer length, not the string length! */
/* Returns the number of substrings replaced. */
int str_replace_substr(char *str, int len, int n, const char *dest_substr, const char *src_substr);

/* converts non-readable non-ascii characters in "<0xhh>" */
/* arguments: destination string, source string, maximum destination length including the terminating null byte */
int convert_non_ascii_to_hex(char *,  const char *, int);

void remove_extension_from_filename(char *);  /* removes extension including the dot */
int get_filename_from_path(char *dest, const char *src, int size);  /* size is size of destination, returns length of filename */
int get_directory_from_path(char *dest, const char *src, int size);  /* size is size of destination, returns length of directory */
void get_relative_path_from_absolut_paths(char *dest, const char *src1, const char *src2, int size);  /* size is size of destination, dest points to src2 relative to src1 */
void sanitize_path(char *path);  /* removes double dot entries */
void sanitize_ascii(char *);  /* replaces all non-ascii characters with a dot */
/* replaces all control chars (decimal values < 32 and decimal value == 127 (DEL)) */
/* works also with UTF-8 and Latin-1 */
void str_replace_ctrl_chars(char *, char);
void ascii_toupper(char *);
void latin1_to_ascii(char *, int);
void latin1_to_utf8(char *, int);
void utf8_to_latin1(char *);
int utf8_strlen(const char *);  /* returns the number of utf8 characters in the string */
int utf8_idx(const char *, int);  /* returns the byte offset of the nth utf8 character */
/* limits the length in bytes of the string while avoiding creating an illegal utf8 character at the end of the string */
/* returns the new byte length */
int utf8_set_byte_len(char *, int);
/* limits the length in utf8 chars of the string */
/* returns the new utf8 char length */
int utf8_set_char_len(char *, int);
int antoi(const char *, int);
int atoi_nonlocalized(const char *);
double atof_nonlocalized(const char *);
//int sprint_number_nonlocalized(char *, double);
long long atoll_x(const char *, int);
void strntolower(char *, int);

/* returns also empty tokens */
char * strtok_r_e(char *, const char *, char **);

/* 3th argument is the minimum digits that will be printed (minus sign not included), leading zero's will be added if necessary */
/* if 4th argument is zero, only negative numbers will have the sign '-' character */
/* if 4th argument is one, the sign '+' or '-' character will always be printed */
/* returns the amount of characters printed */
//int sprint_int_number_nonlocalized(char *, int, int, int);
int sprint_ll_number_nonlocalized(char *, long long, int, int);
int fprint_int_number_nonlocalized(FILE *, int, int, int);
int fprint_ll_number_nonlocalized(FILE *, long long, int, int);

/* returns 1 in case the string is not a number */
int is_integer_number(const char *);
int is_number(const char *);

int round_125_cat(double);  /* returns 10, 20 or 50, depending on the value */

void hextoascii(char *);  /* inline copy */
void bintoascii(char *);  /* inline copy */
void bintohex(char *);    /* inline copy */
void asciitohex(char *, const char *);  /* destination must have double the size of source! */
void asciitobin(char *, const char *);  /* destination must have eight times the size of source! */
void hextobin(char *, const char *);    /* destination must have four times the size of source! */

/* Converts a double to Giga/Mega/Kilo/milli/micro/etc. */
/* int is number of decimals and size of destination. Result is written into the string argument */
int convert_to_metric_suffix(char *, double, int, int);

double round_up_step125(double, double *);      /* Rounds the value up to 1-2-5 steps */
double round_down_step125(double, double *);    /* Rounds the value down to 1-2-5 steps */
double round_to_3digits(double);   /* Rounds the value to max 3 digits */

int strtoipaddr(unsigned int *, const char *);  /* convert a string "192.168.1.12" to an integer */

int dblcmp(double, double);  /* returns 0 when equal */

int base64_dec(const void *, void *, int);

int t_gcd(int, int);  /* returns greatest common divisor */
int t_lcm(int, int);  /* returns least common multiple */

/* sz is size of destination, returns length of string in dest.
 * This is different than the official BSD implementation!
 * From the BSD man-page:
 * "The strlcpy() and strlcat() functions return the total length of
 * the string they tried to create. For strlcpy() that means the
 * length of src. For strlcat() that means the initial length of dst
 * plus the length of src. While this may seem somewhat confusing,
 * it was done to make truncation detection simple."
 */
#if defined(__APPLE__) || defined(__MACH__) || defined(__APPLE_CC__) || defined(__FreeBSD__) || defined(__HAIKU__) || ((__GLIBC__ >= 2) && (__GLIBC_MINOR__ >= 38)) || (__GLIBC__ >= 3)
/* nothing here */
#else
#define HAS_NO_STRLC
int strlcpy(char *, const char *, int);
int strlcat(char *, const char *, int);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


