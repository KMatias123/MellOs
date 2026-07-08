#!/bin/bash

export PREFIX="/usr/local/i386elfgcc"
export PREFIX_GRUB="/usr/local/grub-2_14"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

if [[ $1 == '--clean' ]]; then
    sudo rm -rf $PREFIX $PREFIX_GRUB /tmp/src
    exit 0
fi;

if [[ $1 == '-h' || $1 == '--help' ]]; then
    echo ''
    echo '  setup-gcc-suse.sh'
    echo ''
    echo '      --clean'
    echo '  remove all the directories and binaries created'
    echo '  and the sources downloaded'
    echo ''
    echo '      --help -h'
    echo '  prints this'
    echo ''
    exit 0
fi;

sudo zypper --non-interactive update

sudo zypper --non-interactive install make cmake qemu-x86 python315 bison flex curl mpc-devel mpfr-devel gmp-devel mtools xorriso

echo '=========================================='
echo '   COMPILING AND INSTALLING BINUTILS'
echo '=========================================='

mkdir /tmp/src
cd /tmp/src
curl -O 'http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz'
tar xf binutils-2.39.tar.gz 2>&1 > binutils-tar.log
cd binutils-2.39
echo '=========================================='
echo ''
bash -c "echo -n 'Configure: '
        while [ 1 ]; do echo -n ' .' && sleep 1; done" &

./configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 > binutils-configure.log
kill -n 15 $!
echo ''
sudo make all install 2>&1 | tee binutils-make.log

echo '=========================================='
echo '     COMPILING AND INSTALLING GCC'
echo '=========================================='

cd /tmp/src
curl -O 'https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz'
tar xf gcc-12.2.0.tar.gz 2>&1 | tee gcc-tar.log
cd gcc-12.2.0
echo '=========================================='
echo ''
bash -c "echo -n 'Configure: '
        while [ 1 ]; do echo -n ' .'; sleep 1; done" &

./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-language=c,c++ --without-headers 2>&1 > gcc-configure.log
kill -n 15 $!
echo ''
echo 'Running make for GCC...'
sudo make all-gcc install-gcc 2>&1 | tee gcc-make.log

cd /tmp/src

echo '=========================================='
echo '     COMPILING AND INSTALLING GRUB'
echo '=========================================='

curl -O 'https://ftp.gnu.org/gnu/grub/grub-2.14.tar.gz'
tar xf grub-2.14.tar.gz 2>&1 | tee gcc-tar.log
cd grub-2.14

bash -c "echo -n 'Configure: '
        while 1; do echo -n ' .'; sleep 1; done" &

./configure --prefix=$PREFIX_GRUB 2>&1 > grub-configure.log
kill -n 15 $!
echo ''
sudo make all install 2>&1 | tee grub-make.log

echo '=========================================='
echo ''
echo '        HERE U GO MAYBE:'
ls $PREFIX/bin
ls $PREFIX_GRUB
export PATH="$PATH:$PREFIX/bin"
