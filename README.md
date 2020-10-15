# GBA Hobby Project
This is a simple hobby project that I'm using to brush up on C.
This may grow into a full game, or it may get left as just a demo, who knows?

The makefile is the template one provided with DevKitAdv

# Conventions
Put all opening curly braces at the end of the line preceding it  
Omit curly braces when they only enclose one line  
In `if` statements, always evaluate the condition most likely to be false first  
Use `const` on all function parameters that are not intended to be changed  
Any function that takes zero parameters must be fed `void` anyway. (Example: `int main(void){}`)  
Make funcions `inline` whenever possible    
Always use the shorthand types in `gba_macros.h`  
All `#define` identifiers must be in all caps  
All `#define`'s of hardware registers must use the same name as those on the Coranac GBA tutorial. (They just seem more professional)  
All `define`'s of hardware registers must be sorted in ascending order by address  
All header guard identifiers must be the full name of the file in all caps with the periods changed to underscores. (Example: `GBA_MACROS_H`)  
Declare any variables that belong in ROM as `const`  
