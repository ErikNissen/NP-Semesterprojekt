# Collect source files
file(GLOB SourceFiles *.*pp)
file(GLOB SourceFiles *.h)

# and add to the library
add_library(messagesLib ${SourceFiles} SegmentDataMessage.cpp SegmentDataMessage.h TimeSegmentMessage.cpp TimeSegmentMessage.h TransferMessage.cpp TransferMessage.h)