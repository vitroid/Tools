# use gmake
BINTARGET=randomsearch
include $(HOME)/etc/Makefile
%: %.o
	$(CC) $^ -o $@ $(LOCALLDFLAGS) $(LDFLAGS)
randomsearch2: randomsearch.o
	$(CC) $^ -o $@ $(LOCALLDFLAGS) $(LDFLAGS)

# remove the following line.
PACKAGESRC	=graph2digraph.c randomsearch.c Makefile README
DEST		=Graph2digraph
