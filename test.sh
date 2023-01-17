#!/bin/bash

for i in {1..49}
do
echo "**************** test${i} ****************"
echo
build/tigerc testcases/test$i.tig
echo
done