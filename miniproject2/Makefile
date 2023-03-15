# Headers in INC_DIR
INC_DIR=./lib
# graph library source in $SRC_DIR
SRC_DIR=./lib
# BT archive in LIB_DIR
LIB_DIR=./lib
LIB_NAME=fdr
LIB_FILE=${LIB_DIR}/lib${LIB_NAME}.a

ifeq (${LFS},1)
LFSFLAG=-D_FILE_OFFSET_BITS=64
endif

# is readline available?
RDLINE := ${wildcard /usr/include/readline/*}
ifdef RDLINE
RDLINEFLAG=-DREADLINE
RDLINELIB=-lreadline
endif
# -w ngăn chặn các thông báo cảnh báo
# -pedantic Đưa ra tất cả các cảnh báo theo yêu cầu của ANSI tiêu chuẩn C 
#            từ chối tất cả các chương trình sử dụng phần mở rộng bị cấm.
CFLAGS= -w -I${INC_DIR} \
	${LFSFLAG} ${RDLINEFLAG}

LIBS=-L${LIB_DIR} -l${LIB_NAME}

SRC := ${wildcard ${SRC_DIR}/*.c}

all: main
${LIB_FILE}: ${SRC} 
	${CC} -c ${CFLAGS} $?
	${AR} ${ARFLAGS} $@ *.o
	rm -f *.o

main: main.c $(LIB_FILE)
	${CC} $(CFLAGS) ${LDFLAGS} -o $@ main.c $(LIBS)
	
clean:
	rm -f main $(LIB_FILE)