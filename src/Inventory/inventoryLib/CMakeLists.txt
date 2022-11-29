# Collect source files
file(GLOB SourceFiles *.*pp)
file(GLOB SourceFiles *.h)

# and add to the library
add_library(inventoryLib ${SourceFiles} Inventory.cpp Inventory.h ShelfPair.cpp ShelfPair.h Shelf.cpp Shelf.h Container.cpp Container.h)