#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include "string.h"

int main(int argc,char *argv[])
{
    EncodeInfo E1;
    DecodeInfo D1;
    printf("cla count : %d\n",argc);
    if(argc < 3){
        printf("please enter atleast 3 arguments.\n");
    }
    int res = check_operation_type(argv);
    if(res==e_encode){
        printf("encode is selected\n");
        if(read_and_validate_encode_args(argv,&E1)==e_success){
            printf("Read and validate encode args is success.\n");
            if(do_encoding(&E1)==e_success){
                printf("Encoding is success.\n");
            }
            else{
                printf("Encoding is failure !\n");
                return 0;
            }
        }
        else{
            printf("Read and validate encode args is failure !\n");
            return 0;
        }
    }
    else if(res==e_decode){
        printf("Decode is selected\n");
        if(read_and_validate_decode_args(argv,&D1)==e_success){
            printf("Read and validate decode args is success.\n");
            if(do_decoding(&D1)==e_success){
                printf("Decoding is success.\n");
            }
            else{
                printf("Decoding is failure !\n");
                return 0;
            }
        }
        else{
            printf("Read and validate decode args is failure !\n");
            return 0;
        }

    }
    else{
        printf("Invalid Input!\n");
        printf("Usage: For encoding: ./a.out -e beautiful.bmp secret.txt [stego.bmp]\n");
        printf("For Decoding:./a.out -d stego.bmp [output.txt]\n");
    }

    return 0;
}
OperationType check_operation_type(char *argv[]){
    if(strcmp(argv[1],"-e")==0){
        return e_encode;
    }
    else if(strcmp(argv[1],"-d")==0){
        return e_decode;
    }
    else
        return e_unsupported;

}
