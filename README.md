# wavecatcher-analysis

To get started download repository and navigate to examples folder. Open CERN ROOT in examples folder and execute:
.x read_simple_exapledata.cc



You can speed up the analysis by compiling library. To compile it on linux or mac do: 
make -f makefile

Then add gSystem->Load("ReadRunLib.sl"); to macro or to rootlogon.C