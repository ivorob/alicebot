CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ../src)
SET (SOURCES 
        AliceBotTestsSuite.cpp
        UserTest.cpp
        MessageTest.cpp
        ${SRC_DIR}/User.cpp
        ${SRC_DIR}/Message.cpp)

INCLUDE_DIRECTORIES (../include)

FIND_LIBRARY (JSON_LIBRARY
    NAME jsoncpp
    PATHS /usr/lib /usr/local/lib)

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests cppunit ${JSON_LIBRARY})
