createBuildDir:
	mkdir build
	cd build;cmake -DLLVM_ENABLE_PROJECTS='clang;compiler-rt' -G "Unix Makefiles" ../llvm;make

buildProject:
	cd build; make