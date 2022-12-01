# Collect source files
#file(GLOB SourceFiles *.*pp)
#file(GLOB SourceFiles *.h)

# and add to the library
#add_library(Messages ${SourceFiles} SegmentDataMessage.cpp SegmentDataMessage.h TimeSegmentMessage.cpp TimeSegmentMessage.h TransferMessage.cpp TransferMessage.h)

add_library(Messages
        SegmentDataMessage.cpp
        TimeSegmentMessage.cpp
        TransferMessage.cpp
        )

target_include_directories(Messages
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})