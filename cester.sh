#!/bin/bash

NAME=cester
DOWNLOAD_PATH=https://raw.githubusercontent.com/exoticlibraries/libcester/master/include/exotic/cester.h
INSTALL_PATH=/usr/include/exotic/
AFTER_INSTALL_TEXT="compile your test like 'gcc -I. test.c', don't forget the -I. option"

main() {
	check_if_is_sudo $@
	if [ "$1" == "uninstall" ]; then 
		if [ "$2" != "" ]; then
			INSTALL_PATH=$2
	        fi
		rm -R $INSTALL_PATH/*$NAME.*
		echo "Done uninstalling $NAME"
		return	
	fi
	if [ "$1" != "" ]; then
		INSTALL_PATH=$1
	fi
	echo "Downloading $NAME ..."
	wget -O "./$NAME.h"  $DOWNLOAD_PATH -q
	echo "Installing libcester into $INSTALL_PATH"
	mkdir -p $INSTALL_PATH
	mv "./$NAME.h" $INSTALL_PATH
	echo $AFTER_INSTALL_TEXT
	echo "Done installing $NAME."
}

check_if_is_sudo() {
	if [ "$(id -u)" -ne 0 ]; then 
		if [ "$PREFIX" != "" ]; then 
			INSTALL_PATH=$PREFIX/include/exotic/
		else
			echo "it appear you are not running the script as root"
			echo "the script is reinitiated as root"
			echo "manually restart the script as sudo it this fails 'sudo bash $NAME.sh"
			sudo bash "$NAME.sh" $@
			exit 0
		fi	
	fi
}

main $@
exit 0
