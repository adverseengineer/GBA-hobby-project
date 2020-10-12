# GBA Hobby Project
This is a simple hobby project that I'm using to brush up on C.
This may grow into a full game, or it may get left as just a demo, who knows?

The makefile is the template one provided with DevKitAdv, but I'm going to try to write everything else myself

# Conventions
In `if` statements, always evaluate the condition most likely to be false first  
Always use `typedef` over `#define` when possible  
All `#define` identifiers must be in all caps  
All `#define`'s of hardware registers must use the same name as those on the Coranac GBA tutorial. (They just seem more professional)  
All header guard identifiers must be the full name of the file in all caps with the periods changed to underscores. (Example: `GBA_MACROS_H`)  
