# Basic_NN2SPECTRE
---

## Data reference
- https://www.diodes.com/products/discrete/mosfets/mosfet-master-table/#collection-8360=~(Polarity~(~'N*2bP)) BSS8402DW 

## Structure
- ANN training
- .so(or .dll) script for libtorch in C++
- Sample netlist script

## Requirements
- python
```
pytorch
numpy
matplotlib
pandas
```

- C++
```
libtorch
(optional) json
```

- (Plus) SPECTRE and Verilog-A

## Environment setting(Linux)
- libtorch
```
export LD_LIBRARY_PATH={foo.dir}/libtorch:$LD_LIBRARY_PATH 
```