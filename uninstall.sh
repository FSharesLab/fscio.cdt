#! /bin/bash

binaries=(fscio-ranlib
          fscio-ar
          fscio-objdump
          fscio-readelf
          fscio-abigen
          fscio-wasm2wast
          fscio-wast2wasm
          fscio-pp
          fscio-cc
          fscio-cpp
          fscio-ld)

if [ -d "/usr/local/fscio.cdt" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            pushd /usr/local &> /dev/null
            rm -rf fscio.cdt
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            popd &> /dev/null
            pushd lib/cmake &> /dev/null
            rm -rf fscio.cdt
            popd &> /dev/null
            break;;
         [Nn]* ) 
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi

if [ -d "/usr/local/fscio.wasmsdk" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            pushd /usr/local &> /dev/null
            rm -rf fscio.wasmsdk
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            popd &> /dev/null
            break;;

         [Nn]* ) 
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
