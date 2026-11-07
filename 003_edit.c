#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include "edit.h"

// Get the corresponding frame ID for the given option
void get_target_frame(char *option, char *target_frame){
    // Check for title option
    if(strcmp(option,"-t") ==0){
        strcpy(target_frame,"TIT2");
    }
    // Check for artist option
    else if(strcmp(option,"-a") ==0){
        strcpy(target_frame, "TPE1");
    }
    // Check for Album option
    else if(strcmp(option,"-A") ==0){
        strcpy(target_frame,"TALB");
    }
    // Check for year option
    else if(strcmp(option,"-y") == 0){
        strcpy(target_frame, "TYER");
    }
    // Check for genre option
    else if(strcmp(option,"-g") ==0){
        strcpy(target_frame, "TCON");
    }
    // Check for composer option
    else if(strcmp(option, "-c")== 0){
        strcpy(target_frame, "TCOM");
    }
}
Status edit(char* option,char *new_value,char *filename){
    // Store target frame ID
    char target_frame[5];
    // Get frame ID from option
    get_target_frame(option,target_frame);
    printf("\n");
    printf("========================================\n");
    printf("          MP3 TAG EDITOR\n");
    printf("========================================\n");
    // Display frame being edited
    printf("Editing Frame : %s\n",target_frame);
    // Display new value
    printf("New Value     : %s\n\n",new_value);

    char header[10];
    unsigned int tag_size;
    char frame_header[10];
    int bytes_read = 0;
    unsigned int frame_size;

    // Open MP3 file for reading and writing
    FILE *fp;
    fp = fopen(filename,"r+");
    if(fp == NULL){
        printf("ERROR : Unable to Open %s File\n",filename);
        return e_failure;
    }
    // Read 10-byte ID3 header
    if(fread(header,sizeof(char),10,fp) != 10){
        printf("ERROR : Unable to Read ID3 Header\n");
        fclose(fp);
        return e_failure;
    }
    // Check for ID3 signature
    if(header[0] != 'I' || header[1] != 'D' || header[2] != '3'){
        printf("ERROR : ID3 TAG Not Found\n");
        fclose(fp);
        return e_failure;
    }
    printf("ID3 TAG FOUND\n");
    // Check for ID3 version 2.3
    if(header[3] != 3){
        printf("ERROR : ID3v2.3 Required\n");
        fclose(fp);
        return e_failure;
    }
    printf("ID3 Version : 2.3\n");
    // Calculate tag size
    tag_size = header[6] * 128 * 128 * 128 + header[7] * 128 * 128 + header[8] * 128 + header[9];
    printf("Tag Size : %u bytes\n", tag_size);
    printf("\n");

    // Read each frame until the tag ends
    while(bytes_read < tag_size){
        // Read 10-byte frame header
        if(fread(frame_header,sizeof(char),10,fp) != 10){
            break;
        }
        // Store 4-character frame ID
        char frame_id[5];
        char *frame_data;
        frame_id[0] = frame_header[0];
        frame_id[1] = frame_header[1];
        frame_id[2] = frame_header[2];
        frame_id[3] = frame_header[3];
        frame_id[4] = '\0';

        // Calculate frame data size from 4 bytes
        frame_size = frame_header[4] * 256 * 256 * 256 + frame_header[5] * 256 * 256 + frame_header[6] * 256 + frame_header[7];
        if(frame_size == 0){
            printf("ERROR : Frame Size is Zero\n");
            return e_failure;
        }

        // Check if required frame is found
        if(strcmp(frame_id,target_frame) == 0){
            printf("Required Frame Found : %s\n",frame_id);
            if(strlen(new_value) + 1 > frame_size){
                printf("ERROR : New Value is Too Long\n");
                return e_failure;
            }
            // Write text encoding byte
            fputc(0,fp);
            // Write new value
            fwrite(new_value,sizeof(char),strlen(new_value),fp);
            // Calculate remaining space
            int remaining = frame_size - strlen(new_value) - 1;
            // Fill remaining space with zeros
            for(int i=0;i<remaining;i++){
                fputc('\0',fp);
            }
            printf("MP3 File Edited Successfully\n");
            // Close MP3 file
            fclose(fp);
            // Return success
            return e_success;
        }
        fseek(fp,frame_size,SEEK_CUR); //Skip current frame data
        bytes_read = bytes_read + 10 + frame_size; // Update bytes processed
    }
    printf("ERROR : Required Frame Not Found\n");
    // Close MP3 file
    fclose(fp);
    // Return failure
    return e_failure;
}