# Demo_tiny
This example project demonstrates the basics of working of a C++ program with the
embedded Transd. The C++ program here creates a graph of a math function, repeatedly 
calling a procedure defined in an external Transd program. The graph is outputted into a
PPM image file.

The notable thing that this demo project demonstrates is the speed of interaction between
C++ and Transd programs. Within the double for-loop the external Transd function, defined
in a Transd source file, is called 1 million times:

```
int width = 1000;
int height = 1000;
transd::TDType* func = transd::getProc( prog, L"tst::getShade" );
...
for( int i = 0; i < width; ++i ) {
    for( int k = 0; k < height; ++k ) {
        *x = (double)i - width / 2;
        *y = (double)k;

        int res = *(int*)transd::execute( func );
```


### How to build

#### Windows

1. Place the files 'asm.td' and 'getshade.td' from the repository 'src' directory
to some writable directory. (Or leave them in place if their current directory is
writable.) Into this directory the output file of the program will be written.

2. Edit the 'asm.td' file and specify the path to the 'getshade.td' file.

3. Edit the 'main.cpp' file: locate the following line at the top of the file:

`std::string workingDir = "Y:\\your\\working\\directory\\"`

and change it by specifying your output directory (with trailing backslash).

4. Build the solution and run the executable. Check the image in the output "graph.ppm"
file. PPM image files can be opened e.g. with LibreOffice, GIMP, etc. Report of any
issues here: https://github.com/transd-lang/Demo_tiny/issues

#### Linux

To be written...
