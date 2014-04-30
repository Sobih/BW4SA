BW4SA
============

Generic library for biosequence analysis based on the Burrows-Wheeler transform

Contributors: 
*  Topi Paavilainen
*  Paula Lehtola
*  Max Sandberg
*  Lassi Vapaakallio

Project Structure:

	project
	\conf\   --> configuration files (Unix/Linux projects might prefer an 'etc' folder)
	\src\    --> main source (for C++ projects, headers and sources go along, but if 
        	      your project is a library then separating include files for others 
        	      is a better practice)
	\src\module1\ --> for each sub module (for multiple files having related contents,
	                   it is better to separate them to their own subfolders)
	\doc\    --> documentation 
	\include\ --> (for library projects, the distributable include files)
	\os\     --> OS (platform dependent) files (uch as makefiles, package building
        	      scripts..)
	\res\    --> resources required for compilation but not source files (icons, etc.)
	\tests\  --> tests for source-files
	\tests\module1\ --> tests for individual modules
	\MAKEFILE --> makefile script for building the project
	\README   --> introductory document (might refer to doc\README)
	\INSTALL  --> Installation document (might refer to doc\INSTALL)
