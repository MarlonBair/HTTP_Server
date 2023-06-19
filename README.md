# HTTP Server

This is an HTTP Server that is written in C for Linux Systems. It allows for the hosting of websites and client GET requests. The server uses concurrency and currently allows for up to 32 connections (more connections can be allowed by changing the maximum length in the server.h file).
 
# Implementation

* The server utilizes the epoll system call to allow for the efficient handling of a multitude of connections
* Consistent error checking and handling is written throughout the server process, and messages are output to stdout.
* The server exercises a graceful shutdown when a kill command is received

# Installation

```sh
$ git clone https://github.com/MarlonBair/HTTP_Server.git
$ cd HTTP_Server/src
$ make
```
# Usage 

1. Upload site files into static folder
2. ```$ ./server [-p INSERT_PORT_HERE] ```
    * Left blank the port will be set to 8080

# Supported Browsers

 * Safari
 * Firefox

# Supported File Types

* .bin (default)
* .html
* .js
* .css
* .xml
* .txt
* .json
* .pdf
* .doc
* .xls
* .ppt
* .zip
* .ttf
* .woff
* .wot
* .png
* .gif
* .jpg
* .jpeg
* .ico
* .mp3
* .wav
* .mp4
* .mpeg

# Questions?

Contact:
* marlonbair1@gmail.com
