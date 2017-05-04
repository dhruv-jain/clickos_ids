#! /bin/sh
export XEN_ROOT=$(pwd)"/xen-4.4.1/" 
export MINIOS_ROOT=$XEN_ROOT"extras/mini-os/" 
export CLICKOS_ROOT=$(pwd)"/clickos/"
cd $CLICKOS_ROOT
 ./configure --enable-minios --with-xen=$XEN_ROOT --with-minios=$MINIOS_ROOT
make minios
