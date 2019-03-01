CC=arm-linux-gcc
AR=arm-linux-ar

CUR_DIR = ${shell pwd}

LIBPATH = ${CUR_DIR}/lib

COMMON_DIR = ${CUR_DIR}/common
BASE_DIR   = ${CUR_DIR}/base
ZLOG_DIR   = ${CUR_DIR}/zlog
CGI_DIR    = ${CUR_DIR}/web/cgi

INCLUDE_DIR  = -I ${CUR_DIR}/include
BASE_INC_DIR = -I ${BASE_DIR}
ZLOG_INC_DIR = -I ${ZLOG_DIR}
CGI_INC_DIR  = -I ${CGI_DIR} 

COMMON_SRC = ${wildcard ${COMMON_DIR}/*.c}
COMMON_OBJ = ${patsubst %.c, %.o, ${COMMON_SRC}}

BASE_SRC = ${wildcard ${BASE_DIR}/*.c}
BASE_OBJ = ${patsubst %.c, %.o, ${BASE_SRC}}

ZLOG_SRC = ${wildcard ${ZLOG_DIR}/*.c}
ZLOG_OBJ = ${patsubst %.c, %.o, ${ZLOG_SRC}}

CGI_SRC = ${wildcard ${CGI_DIR}/*.c}
CGI_OBJ = ${patsubst %.c, %.o, ${CGI_SRC}}
CGI_BIN_DIRS = ${CUR_DIR}/web/target/cgi-bin

ZLOGLIB = -L$(LIBPATH) -lzlog

ZLOG_CCFLAGS   = -Wall -lrt -lm -lpthread ${ZLOG_INC_DIR}
COMMON_CCFLAGS = -Wall -lrt ${INCLUDE_DIR}
BASE_CCFLAGS   = -Wall -lrt -lm -lpthread ${INCLUDE_DIR} ${BASE_INC_DIR} ${ZLOGLIB}
CGI_CCFLAGS    = -Wall -lrt -lm -lpthread ${INCLUDE_DIR} ${CGI_INC_DIR} ${ZLOGLIB}

TARGET_ZLOGLIB = libzlog.a
TARGET_MAIN = monitor
TARGET_CGI = ${CUR_DIR}/web/cgi/set_user.cgi      \
             ${CUR_DIR}/web/cgi/index.cgi         \
             ${CUR_DIR}/web/cgi/ioseting.cgi      \
             ${CUR_DIR}/web/cgi/netsetting.cgi    \
             ${CUR_DIR}/web/cgi/advancefun.cgi    \
             ${CUR_DIR}/web/cgi/routsetting.cgi   \
             ${CUR_DIR}/web/cgi/upgrade.cgi       \
             ${CUR_DIR}/web/cgi/device.cgi        \
             ${CUR_DIR}/web/cgi/dataAnalysis.cgi

all: ${TARGET_ZLOGLIB} ${TARGET_MAIN}
#all: ${TARGET_ZLOGLIB} ${TARGET_MAIN} ${TARGET_CGI}

${TARGET_ZLOGLIB}: $(ZLOG_OBJ)
	$(AR) rc $(LIBPATH)/$@ $^
	@echo "Lib: libzlog.a Compile done."

${ZLOG_OBJ}:%.o:%.c
	${CC} ${ZLOG_CCFLAGS} -c $< -o $@

${TARGET_MAIN}: ${BASE_OBJ} ${COMMON_OBJ}
	${CC} ${BASE_OBJ} ${COMMON_OBJ} ${BASE_CCFLAGS} -o $@
	@echo "Target Compile done."

${BASE_OBJ}:%.o:%.c
	${CC} ${BASE_CCFLAGS} -c $< -o $@

${COMMON_OBJ}:%.o:%.c
	${CC} ${COMMON_CCFLAGS} -c $< -o $@

${TARGET_CGI}:%.cgi:%.c
	${CC} -o $@ $^ ${CUR_DIR}/web/cgi/cgic.c ${CUR_DIR}/web/cgi/cJSON.c ${CUR_DIR}/web/cgi/json_fun.c  ${COMMON_OBJ} ${CGI_CCFLAGS}
	mv $@ ${CGI_BIN_DIRS}
	@echo "CGI Compile done."

clean:
	rm -f ${BASE_OBJ}
	rm -f ${COMMON_OBJ}
	@echo "Clean object files done."
	rm -f ${CGI_BIN_DIRS}/*.cgi
	rm -f ${TARGET_MAIN}
	@echo "Clean target files done."

