#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Stego Image info */
    char *stego_image_fname;
    FILE *fptr_stego_image;
    char image_data[MAX_IMAGE_BUF_SIZE];

    /* output File Info */
    char *output_fname;
    FILE *fptr_output;
    int extn_size;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[MAX_SECRET_BUF_SIZE];
    long size_secret_file;

} DecodeInfo;


/* Decoding function prototype */

/* Read and validate Decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

Status decode_extn_size(DecodeInfo *decInfo);

int decode_int_from_image(DecodeInfo *decInfo);

Status decode_file_size(DecodeInfo *decInfo);

Status read_and_write(long size,DecodeInfo *decInfo);

Status decode_extn(char *extn,DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_Decode_files(DecodeInfo *decInfo);

Status decode_magic_string(char *magic_string, DecodeInfo *decInfo);

Status decode_data_from_image(char *data, int size,DecodeInfo *decInfo);

Status validate_magic_string(char data, char *image_buffer);

#endif
