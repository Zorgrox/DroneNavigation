DEP_DIR=/project/grades/Spring-2021/csci3081/dependencies
ifeq ($(USE_REPO_DIR),1)
ROOT_DIR := /home/user/repo
else
ROOT_DIR := $(shell git rev-parse --show-toplevel)
endif
BUILD_DIR=${ROOT_DIR}-build
CXX = g++
CXXFLAGS = -std=c++11 -g -fPIC 

-include $(DEP_DIR)/env

##### EDIT ME!!! #####################
MAINDATEFILE = date.cc
######################################
LABTESTEXE = date_unittest
LABEXE = date

all: ${LABEXE} 

${LABTESTEXE}: 
	$(CXX) $(CXXFLAGS) -Wl,-rpath,$(BUILD_DIR)/lib -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib date_unittest.cc $(MAINDATEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

${LABEXE}: ${LABTESTEXE}
	$(CXX) $(CXXFLAGS) -Wl,-rpath,$(BUILD_DIR)/lib -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib main.cc $(MAINDATEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

test: ${LABTESTEXE}

clean:
	rm -rf ${BUILD_DIR}
	rm -f ${LABEXE}
	rm -f ${LABTESTEXE}
