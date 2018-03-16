#!/bin/bash

wget http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp
for i in `cat tsp | grep \<A | cut -d '"' -f2 | grep tsp$`; do  wget http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/$i; done;

echo -n "Total files EUC_2D... :"
find . | grep tsp$ | xargs cat | grep EUC_2D | wc -l

rm *tsp

