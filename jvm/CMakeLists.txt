include_directories("${PROJECT_SOURCE_DIR}/jvm")

SET(SRC_LIST main.cpp 
    src/ClassFileReader.cpp
    src/ClassPrinter.cpp
    src/ClassUtil.cpp
    src/DataInputStream.cpp
    src/Heap.cpp
    src/Instance.cpp
)

ADD_EXECUTABLE(
    tjvm ${SRC_LIST}    
)