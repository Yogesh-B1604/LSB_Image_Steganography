#include <stdio.h>
#include "decode.h"
#include "types.h"
#include "string.h"
#include "common.h"

Status open_Decode_files(DecodeInfo *decInfo)
{
    // Stego Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);

    	return e_failure;
    }

    // Output text file
    decInfo->fptr_output = fopen(decInfo->output_fname, "w");
    // Do Error handling
    if (decInfo->fptr_output == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->output_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
    if(strstr(argv[2],".bmp")!= NULL){
        decInfo->stego_image_fname=argv[2];
        
    }
    else{
        printf("Invalid Input file.\n");
        return e_failure;
    }
    if(argv[3]==NULL){
        decInfo->output_fname="output.txt";
    }
    else{
        if(strstr(argv[3],".txt")!=NULL){
            decInfo->output_fname=argv[3];
        }
        else{
            printf("Invalid Input file.\n");
            return e_failure;
        }
    }
    return e_success;
}
Status decode_magic_string(char *magic_string, DecodeInfo *decInfo){
    fseek(decInfo->fptr_stego_image,54,SEEK_SET);
    if(decode_data_from_image(magic_string,strlen(magic_string),decInfo)==e_success){
        return e_success;
    }
    return e_failure;
}
Status decode_extn(char *extn,DecodeInfo *decInfo){
    if(decode_data_from_image(extn,decInfo->extn_size,decInfo)==e_success){
        return e_success;
    }
    return e_failure;
}
Status validate_data(char data, char *image_buffer){
    for(int i=0;i<8;i++){
        int image_bit=image_buffer[i]&1;
        int data_bit=(data>>i)&1;
        if(image_bit!=data_bit){
            return e_failure;
        }
    }
    return e_success;
}
Status decode_data_from_image(char *data, int size, DecodeInfo *decInfo){
    int ret,count=0;
        
    for(int i=0;i<size;i++){
            fread(decInfo->image_data,8,1,decInfo->fptr_stego_image);
            ret=validate_data(data[i],decInfo->image_data);
            if(ret==e_success){
                count++;
            }
        }
        if(count==size){
            return e_success;
        }
        return e_failure;
}
int decode_int_from_image(DecodeInfo *decInfo)
{
    int result = 0;
    unsigned char buffer[32];

    fread(buffer, 32, 1,decInfo->fptr_stego_image);

    for(int i = 0; i < 32; i++)
    {
        int bit = buffer[i] & 1;   
        result = result | (bit << i);      
    }
    return result;
    
}
Status decode_extn_size(DecodeInfo *decInfo){
    decInfo->extn_size=decode_int_from_image(decInfo);
    //printf("%d\n",decInfo->extn_size);
    if(decInfo->extn_size==4){
        return e_success;
    }
    return e_failure;
}
Status decode_file_size(DecodeInfo *decInfo){
    decInfo->size_secret_file=decode_int_from_image(decInfo);
    //printf("%ld\n",decInfo->size_secret_file);
    if(decInfo->extn_size==4){
        return e_success;
    }
    return e_failure;
}

Status read_and_write(long size,DecodeInfo *decInfo){
    char image_buffer[8];
    char ch;

    for(long i = 0; i < size; i++)
    {
        ch = 0;
        fread(image_buffer, 8, 1, decInfo->fptr_stego_image); // Read 8 bytes from stego image
        for(int j = 0; j < 8; j++)
        {
            int bit=(image_buffer[j] & 1);
            ch = ch | (bit << j);
        }
        fwrite(&ch, 1, 1, decInfo->fptr_output); // Write reconstructed byte to output file
    }
    return e_success;
}
Status do_decoding(DecodeInfo *decInfo){
    if(open_Decode_files(decInfo)==e_success){
        printf("File opened successfully \n");
        if(decode_magic_string(MAGIC_STRING,decInfo)==e_success){
            printf("Magic string is decoded and validated successfully.\n");
            if(decode_extn_size(decInfo)==e_success){
                printf("Extention size decoded successfully.\n");
                strcpy(decInfo->extn_secret_file, ".txt");
                if(decode_extn(decInfo->extn_secret_file,decInfo)==e_success){
                    printf("Extention is decoded and validated successfully.\n");
                    if(decode_file_size(decInfo)==e_success){
                        printf("File size is decoded successfully.\n");
                        if(read_and_write(decInfo->size_secret_file,decInfo)==e_success){
                            printf("Data is decoded and written to output file.\n");
                        }
                        else{
                            printf("failed to decode and write the encoded data to output file !\n");
                        }
                    }
                    else{
                        printf("failed to decode File size !\n");
                    }
                }
                else{
                    printf("failed to decoded and validate Extention.\n");
                }
            }
            else{
                printf("Failed to decode Extention size !\n");
            }
        }
        else{
            printf("Failed to decode magic string !\n");
        }
    }
    else{
        printf("Failed to open file !\n");
        return e_failure;
    }
    return e_success;

}