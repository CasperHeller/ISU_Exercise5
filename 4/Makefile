SOURCES = vector.cpp ScopedLocker.cpp
DIR = target/
OBJECTS = ${SOURCES:%.cpp=${DIR}%.o}
EXECUTABLE = ${DIR}vector.target
CXX = arm-angstrom-linux-gnueabi-g++
LIBRARIES = -pthread

all: makedir ${OBJECTS}
	${CXX} -o ${EXECUTABLE} ${OBJECTS} $(LIBRARIES)
	
makedir: 
	@mkdir ${DIR}
	
${DIR}%.o: %.cpp
	${CXX} -c -o $@ $^

clean:
	@rm ${OBJECTS} ${EXECUTABLE}
	@rmdir ${DIR}

help:
	@echo all clean help