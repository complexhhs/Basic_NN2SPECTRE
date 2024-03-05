# Basic_NN2SPECTRE
---

## Data reference + info
- Data source
    - wget https://analogicdesign.com/Files/p045.zip 
- width, length, temperature: {70nm, 2um}, {45nm, 1.5um}, {75}
- Data columns order
    - Vds, Vgs, Vbs, Ids, Qd, Qg, Qb

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
