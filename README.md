# GL Doc Generator
### Automatic OpenGL Documentation Generation

---
Have you ever used an OpenGL bindings library and thought 
"Wow this is great, but it could use some inline documentation!"? 
Well this tool is for you! This C++ / Python program automatically scans, and parses C/C++
header files and generates C style block comments from the online OpenGL Reference. The
comments this program generates should work in most IDEs however it currently has only been tested on CLion.

## How To Use
### Requirements
CMake is required to build the C++ side, along with a compiler capable of C++17 or newer. 
You also require a Python3 Interpreter. This has only been tested on Debian Stable with `GCC-12.2`
but should work as far back as `GCC-8.5` on any Linux distro. Windows is supported but not tested for.
(Please make an issue!)
### Building
Clone the repository:
```shell
git clone --recursive https://github.com/Tri11Paragon/OpenGL-Doc-Generator.git
cd OpenGL-Doc-Generator
```
Make a build directory:
```shell
mkdir build && cd build
```
Run CMake:
```shell
cmake ../ && make -j 16
```
You will now have an executable `gl_doc_generator`
### Usage
Assuming you have python in your path the program only requires one argument,
the path to the header file you want to generate for. You can specify the comment generator,
python path, output location along with level of detail via flags passed to the command line.
```
--generator     # The python script used to generate the comments (Defaults to the one included in this project)
--python        # Path to your python interpreter (Defaults to the python3 in your path)
--output, -o    # Sets the path to the output file. By default this is the input file with _doc added 
```
You can also specify detail flags which will cause certain sections to be removed from the comments.
This is useful because this program can easily bloat the file size to be tens of thousands of lines which some
IDEs do not like. 
```
--no-see, -s    # Don't include @see sections
--no-desc, -d   # Don't include the @descrition section
--brief         # Only include the @name and @code sections 
```
#### Examples:
Generates a commented file at `../gl_doc.h`
```shell
./gl_doc_generator ../gl.h
```
---
Generates a commented file in the local directory called `gl.h` from a file of the same name in the parent directory.
```shell
./gl_doc_generator --output ./gl.h ../gl.h
```
---
Generates a commented file where comments are of the style:
```
/**
 * @name glInvalidateTexSubImage - invalidate a region of a texture image
 * @usage
 * @code void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth); @endcode
 */
```
in the local directory called `gl.h` from a file of the same name in the parent directory.
```shell
./gl_doc_generator -b --output ./gl.h ../gl.h
```