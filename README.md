Glfbabot-BWT
============

Generic library for biosequence analysis based on the Burrows-Wheeler transform

Definition of Done:

	Analyzed, Designed, Programmed, Tested, Tests automated,
	Documented and Integrated into the rest of the software.

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
	\MAKEFILE --> makefile script for building the project
	\README   --> introductory document (might refer to doc\README)
	\INSTALL  --> Installation document (might refer to doc\INSTALL)
