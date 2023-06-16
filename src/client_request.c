#include "server.h"

// Trim string from whitespace characters
void trim(char* str) {
    while(*str) {
        if(*str == 13) {
                *str = '\0';
                break;
        }
        str++;
    }
}

// Return content type extension
char* add_extension(char* input) {

    char* fileExt = strrchr(input, '.');

    if(strcmp(fileExt, ".css") == 0) {
        return "text/css";
    } else if(strcmp(fileExt, ".js") == 0) {
        return "text/js";
    } else if(strcmp(fileExt, ".html") == 0) {
        return "text/html";
    } else if(strcmp(fileExt, ".txt") == 0) {
        return "text/plain";
    } else if(strcmp(fileExt, ".xml") == 0) {
        return "application/xml";
    } else if(strcmp(fileExt, ".json") == 0) {
        return "application/json";
    } else if(strcmp(fileExt, ".pdf") == 0) {
        return "application/pdf";
    } else if(strcmp(fileExt, ".doc") == 0) {
        return "application/msword";
    } else if(strcmp(fileExt, ".xls") == 0) {
        return "application/vnd.ms-excel";
    } else if(strcmp(fileExt, ".ppt") == 0) {
        return "application/vnd.ms-powerpoint";
    } else if(strcmp(fileExt, ".zip") == 0) {
        return "application/zip";
    } else if(strcmp(fileExt, ".ttf") == 0) {
        return "font/ttf";
    } else if(strcmp(fileExt, ".woff") == 0) {
        return "font/woff";
    } else if(strcmp(fileExt, ".eot") == 0) {
        return "font/otf";
    } else if(strcmp(fileExt, ".png") == 0) {
        return "image/png";
    } else if(strcmp(fileExt, ".gif") == 0) {
        return "image/gif";
    } else if(strcmp(fileExt, ".jpg") == 0 || strcmp(fileExt, ".jpeg") == 0) {
        return "image/jpeg";
    } else if(strcmp(fileExt, ".ico") == 0) {
        return "image/vnd.microsoft.icon";
    } else if(strcmp(fileExt, ".mp3") == 0) {
        return "audio/mpeg";
    } else if(strcmp(fileExt, ".wav") == 0) {
        return "audio/wav";
    } else if(strcmp(fileExt, ".mp4") == 0) {
        return "video/mp4";
    } else if(strcmp(fileExt, ".mpeg") == 0) {
        return "video/mpeg";
    } else {
        return "application/octet-stream";
    }
}
// Allow GET requests and send back relevant file data
void client_request(int fd){
	
    // Client answer to server
    char request[500];

    // Bad file request
    char *badReq = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\n<!DOCTYPE html>\n<html>\n<body>\n Not found\n</body>\n</html>";

    //Read client response to answer
    int e = recv(fd, request, MAX_ANSWER, 0);
    if(e == 0) { return; }

    //Trim answer
    char *s = request;
    trim(s);

    char *url;
    url = strsep(&s, " ");
    // If a GET request wasn't received
   	if(strcmp(url, "GET") != 0) { return;}
   	url = strsep(&s, " ");

    // If invalid GET request
    if(url == NULL) { return;}

    // User-requested file path
    char path[MAX_ANSWER+9] = "./static";
    strncat(path, url, strlen(url) + 1);

    // If accessing index
    if(strcmp(path, "./static/") == 0) { strncat(path, "index.html", 11); }

    FILE* fp = fopen(path, "r");

    // If file path doesnt exist
    if(!fp) {
        int sendErr = send(fd, badReq, strlen(badReq), 0);
        if(sendErr == -1) { error("Send ERROR"); }
        return;
    }

    // Get file size
    struct stat fileStat;
    fstat(fileno(fp), &fileStat);

    // Get file data
    char fileData[fileStat.st_size + 1];
    fread(fileData, sizeof(fileData), 1, fp);
    fileData[fileStat.st_size] = '\0';

    // Get HTTP header
    char header[95] = "HTTP/1.1 200 OK\r\nContent-Type: ";
    char* ext = add_extension(path);
    strncat(header, ext, strlen(ext));

    int file_size = strlen(fileData) - 1;
    char content_length[30];
    sprintf(content_length, "\r\nContent Length: %d\r\n\n", file_size);
    strncat(header, content_length, strlen(content_length));

    // Send header and file data to client
    send(fd, header, strlen(header), 0);
    send(fd, fileData, fileStat.st_size + 1, 0);

    fclose(fp);

}
