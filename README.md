# HTTP Server

This is an HTTP Server that is built in C for Linux Systems. It allows for the hosting of websites and client GET requests. The server uses concurrency and currently allows for up to 32 connections (more connections can be allowed by changing the maximum length in the server.h file).
 
# Implementation

* The server utilizes the epoll system call to allow for the efficeint handling of a multitude of connections
* Consistent error checking and handling is written throughout the server process, and messages are output to stdout.
* The server exercises a graceful shutdown when a kill command is sent

# Supported Browsers

 * Safari
 * Firefox

# Supported File Types

* .html (Default)
* .js
* .css
* .xml
* .ttf
* .woff
* .wot
* .png
* .jpg
* .ico

# Questions?

Contact:
* marlonbair1@gmail.com
