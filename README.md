KRC
===

My solutions to exercises from Kernighan & Richie "The C Programming Language" (Second Edition).

I'm using the exercises as an opportunity to explore various features of the C language and also elements of C++.  So the solutions I provide here:

a) May be massively over-engineered simply to try out something that I find interesting.
b) May not be completely idiomatic in any single version of C/C++.
c) May contain rookie errors (although hopefully I will be clearing these up as I go!)

As of now, all non-trivial code examples are under the "ProcessLine" subfolder - https://github.com/alexdgarland/KRC/tree/master/Ch1/ProcessLine

Basically, I've taken the various string-manipulation exercises from Chapter 1 and combined them into a single command-line application, using a linked-list structure to hold a lookup of function pointers and information about the various modes the app can be run in.

Upon completion, the goal is for the source to be fully and automatically compilable for Windows and Linux, including unit and integration tests in a cleaner / more complete  form than is currently present.


AG 19/07/2014
