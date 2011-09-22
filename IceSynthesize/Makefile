####Make executables
CC=gcc
LDFLAGS=-lm
BIN=waterconfig2 IceRandomize3 makebonds
all: $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
waterconfig2: waterconfig2.o Rotmx2.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
IceRandomize3: IceRandomize3.o Ice.o Ice2.o SparseMatrix.o IntHash.o Int64Hash.o
	$(CC) $^ -o $@ $(LDFLAGS)


test: @ice1h.0.92.ngph @ice1h.0.92.ice.ngph @ice1h.0.92.dep.ngph @ice1h.0.92.ice.nx4a

clean:
	-rm $(BIN) *~ *.o @*
tarball: clean
	tar -h -C .. -zcf /tmp/icesynthesize.tar.gz IceSynthesize


####Sample data: Make proton-disordered ice from given configuration
sample: ice1h.0.92.ar3a

#Make (undirected) graph from center-of-mass positions; Bond threshold is 3AA
@%.ngph: %.ar3a makebonds
	./makebonds 3 < $< > $@

#Make the graph to obey ice rule. It often cause stack overflow error when the system size is too large.
%.ice.ngph: %.ngph IceRandomize3
	./IceRandomize3 < $< > $@

#Depolarize
@%.dep.ngph: @%.ice.ngph %.ar3a
	cat $^ | python zerodipole.py > $@

#Reconfigure water molecules with given center-of-mass position and connectivity
@%.ice.nx4a: @%.dep.ngph %.ar3a waterconfig2
	cat @$*.dep.ngph $*.ar3a | ./waterconfig2 > $@
