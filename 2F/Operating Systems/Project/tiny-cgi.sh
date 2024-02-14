#!/usr/bin/bash
## Minimal cgi demo wrapper to show how the CGI environment works.

## Header should be in child program, but this is a simple demo
echo "Content-type: text/plain";
echo;

## dump the env as if it were a shell.
## Human: Look for URL parameters in the output
env

