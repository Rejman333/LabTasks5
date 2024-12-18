#pragma once //This prevents circular imports
/*
#ifndef My_Header_h
#define My_Header_h
#endif

We can use this structure instead if the compiler does not support #pragma once
*/

//This flag controls in witch mode we use this program
#pragma warning (disable : 4996)
//#define SAFE_MODE 

//We can add function prototypes, but I was too lazy to do so.
#ifdef SAFE_MODE

#else
#endif

void stdin_clear();