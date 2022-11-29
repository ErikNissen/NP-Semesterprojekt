# Collect source files
file(GLOB SourceFiles *.*pp)
file(GLOB SourceFiles *.h)

# and add to the library
add_library(itemLib ${SourceFiles} Item.cpp Item.h Priority.cpp Priority.h)