gcc -c graph_jrb.c dllist.c fields.c jval.c jrb.c
ar cvr ~/Documents/Nam2/Graph-C-master/K57/libfdr.a jrb.o dllist.o jval.o fields.o graph_jrb.o
gcc main.c libfdr.a -o main
 

run $make
clear $make clean