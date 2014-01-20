include ../Makefile.common

ifdef WIN
  PYTHON_NAMETAG_LIB=$(call lib,../../src/libnametag)
  PYTHON_MORPHODITA_LIB=$(call lib,../../morphodita/src/libmorphodita)
  PYTHON_C_FLAGS=-DNAMETAG_STATIC
else
  PYTHON_NAMETAG_LIB=$(call lib,../../src/libnametag.dyn)
  PYTHON_MORPHODITA_LIB=$(call lib,../../morphodita/src/libmorphodita.dyn)
endif

TARGETS = $(call dynlib,nametag_python)

all: $(TARGETS)

include ../Makefile.rules

$(call dynlib,nametag_python): nametag_python.cpp $(PYTHON_NAMETAG_LIB) $(PYTHON_MORPHODITA_LIB)
	@$(if $(PYTHON_INCLUDE),,$(error PYTHON_INCLUDE must be set to the directory containing Python.h))
	$(CXX) -I../../src/include -I$(PYTHON_INCLUDE) $(DYN_C_FLAGS) $(DYN_LD_FLAGS) $(PYTHON_C_FLAGS) $(PYTHON_LD_FLAGS) -Wl,--version-script=nametag_python.map $^ -o $@

nametag_python.cpp: nametag_python.i ../nametag.i
	@$(call mkdir,ufal)
	@$(call touch,ufal/__init__.py)
	swig $(SWIG_FLAGS) -python -outdir ufal -o $@ -interface nametag_python $<

.PHONY: clean
clean:
	@$(call rmdir,ufal) $(call rm,$(TARGETS) $(wildcard *.cpp))