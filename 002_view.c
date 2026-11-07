#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include "view.h"
Status view(char *filename){
    // Declare file pointer and buffers
    FILE *fp;
    char header[10];
    char frame_header[10];
    // Declare variables for tag and frame sizes
    unsigned int tag_size;
    unsigned int frame_size;
    int bytes_read = 0;
    // Open the MP3 file in read mode
    fp = fopen(filename,"r");
    // Check if file opened successfully
    if(fp == NULL){
        printf("ERROR : Unable to Open %s File\n",filename);
        return e_failure;
    }
    printf("MP3 File Opened Successfully\n");
    // Read the 10-byte ID3 header
    if(fread(header,sizeof(char),10,fp) != 10){
        printf("Unable to Read ID3 Header\n");
        fclose(fp);
        return e_failure;
    }
    // Check for ID3 tag
    if(header[0] != 'I' || header[1] != 'D' || header[2] != '3'){
        printf("ERROR : ID3 TAG Not Found\n");
        fclose(fp);
        return e_failure;
    }
    printf("ID3 TAG FOUND\n");
    // Check whether the file uses ID3v2.3
    if(header[3] != 3){
        printf("ERROR : ID3v2.3 Required\n");
        fclose(fp);
        return e_failure;
    }
    printf("ID3 Version : 2.3\n");

    // Calculate the tag size
    tag_size = header[6] * 128 * 128 * 128 + header[7] * 128 * 128 + header[8] * 128 + header[9];
    printf("Tag Size : %u bytes\n", tag_size);

    printf("\n");
    printf("========================================\n");
    printf("          MP3 TAG INFORMATION\n");
    printf("========================================\n");

    // Read each ID3 frame until the tag size is reached
    while(bytes_read < tag_size){
    // Read the 10-byte frame header
    if(fread(frame_header,sizeof(char),10,fp) != 10){
        break;
    }
    char frame_id[5];
    char *frame_data;
    // Extract the 4-byte frame ID
    frame_id[0] = frame_header[0];
    frame_id[1] = frame_header[1];
    frame_id[2] = frame_header[2];
    frame_id[3] = frame_header[3];
    frame_id[4] = '\0';
    // Calculate the frame data size
    frame_size = frame_header[4] * 256 * 256 * 256 + frame_header[5] * 256 * 256 + frame_header[6] * 256 + frame_header[7];

    if(frame_size == 0){
        break;
    }
    frame_data = malloc(frame_size + 1);
    if(frame_data == NULL){
        printf("ERROR : Memory Allocation Failed\n");
        fclose(fp);
        return e_failure;
    }
    // Read the frame data
    if(fread(frame_data,1,frame_size,fp) != frame_size){
        printf("ERROR : Unable to Read Frame Data\n");
        free(frame_data);
        fclose(fp);
        return e_failure;
    }

    frame_data[frame_size] = '\0';
    // Display the song title
    if(strcmp(frame_id,"TIT2") == 0){
        printf("TITLE    : %s\n",frame_data + 1); // First bit is encoding bit
    }
    // Display the artist name
    else if(strcmp(frame_id,"TPE1") == 0){
        printf("Artist   : %s\n",frame_data + 1);
    }
    // Display the album name
    else if(strcmp(frame_id,"TALB") == 0){
        printf("Album    : %s\n",frame_data + 1);
    }
    // Display the year
    else if(strcmp(frame_id,"TYER") == 0){
        printf("YEAR     : %s\n",frame_data + 1);
    }
    // Display the genre
    else if(strcmp(frame_id,"TCON") == 0){
        printf("Genre    : %s\n",frame_data + 1);
    }
    // Display the composer name
    else if(strcmp(frame_id,"TCOM") == 0){
        printf("Composer : %s\n",frame_data + 1);
    }
    //free allocated memory
    free(frame_data);
    //update no of bytes processed
    bytes_read = bytes_read + 10 + frame_size;
}
    printf("========================================\n");
    fclose(fp);
    return e_success;
}