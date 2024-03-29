#!/bin/bash

ARCH=$( uname )
EOSIO_CDT_VERSION=1.8.1
CDT_VERSION=3.1.0
if [ "$ARCH" == "Darwin" ] ; then
    OS_NAME=MacOSX
    OS_VER=$(sw_vers -productVersion)
else 
    OS_NAME=$( cat /etc/os-release | grep ^NAME | cut -d'=' -f2 | sed 's/\"//gI' )
    OS_VER=$( grep VERSION_ID /etc/os-release | cut -d'=' -f2 | sed 's/[^0-9\.]//gI' | cut -d'.' -f1 )
    OS_MAJ=$(echo "${OS_VER}" | cut -d'.' -f1)
fi
printf "\\nARCHITECTURE: %s" "${ARCH}"
printf "\\nOS NAME: %s" "${OS_NAME}"
printf "\\nOS VERSION: %s\\n" "${OS_VER}"

function install_deb {
    wget https://github.com/AntelopeIO/cdt/releases/download/v$1/cdt_$1_amd64.deb
    sudo apt install -y ./cdt_$1_amd64.deb
    rm ./cdt_$1_amd64.deb
    printf "\\neosio.cdt installed.\\n"
}

function install_rpm {
    wget https://github.com/eosnetworkfoundation/mandel.cdt/releases/download/v$1/cdt_$1_arm64.deb
    sudo yum install -y ./cdt_$1_arm64.deb
    rm ./cdt_$1_arm64.deb
    printf "\\neosio.cdt installed.\\n"
}

if [ "$ARCH" == "Linux" ]; then
    case "$OS_NAME" in
    "Amazon Linux AMI"|"Amazon Linux")
        if [[ "${OS_NAME}" == "Amazon Linux AMI" && "${OS_VER}" -lt 2017 ]]; then
        	printf "You must be running Amazon Linux 2017.09 or higher to install EOSIO.\\n"
        	printf "exiting now.\\n"
        	exit 1
    	elif [[ "${OS_NAME}" == "Amazon Linux AMI" && "${OS_VER}" = 2018 ]]; then
        	printf "\\nAmazon Linux AMI 2018 support is deprecated.  Please use Amazon Linux 2\\n"
        fi
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_rpm ${EOSIO_CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "CentOS Linux")
        if [ "${OS_VER}" -lt 7 ]; then
        	printf "\\nYou must be running Centos 7 or higher to install EOSIO.\\n"
        	printf "Exiting now.\\n\\n"
        	exit 1;
        fi
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_rpm ${EOSIO_CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "elementary OS")
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_deb ${CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "Fedora")
        if [ "${OS_VER}" -lt 25 ]; then
        	printf "You must be running Fedora 25 or higher to install EOSIO.\\n"
        	printf "Exiting now.\\n"
        	exit 1;
        fi
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_rpm ${EOSIO_CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "Linux Mint")
        if [ "${OS_MAJ}" -lt 18 ]; then
            printf "\\tYou must be running Linux Mint 18.x or higher to install EOSIO.\\n"
            printf "\\tExiting now.\\n"
            exit 1
        fi
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_deb ${CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "Ubuntu")
    	if [ "${OS_MAJ}" -lt 18 ] ; then
    		printf "You must be running Ubuntu 18.04.x or higher to install EOSIO.\\n"
    		printf "Exiting now.\\n"
    		exit 1
    	fi
        if ! [ -x "$(command -v cdt-cpp)" ] ; then
            install_deb ${CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    "Debian GNU/Linux")
    	if [ $OS_MAJ -lt 10 ]; then
    		printf "You must be running Debian 10 to install EOSIO.\n"
    		printf "Exiting now.\n"
    		exit 1
    	fi
        if ! [ -x "$(command -v eosio-cpp)" ] ; then
            install_deb ${CDT_VERSION}
        else 
            printf "\\neosio.cdt already installed.\\n"
        fi
    ;;
    *)
    printf "\\nUnsupported Linux Distribution. Exiting now.\\n\\n"
    exit 1
    esac
elif [ "$ARCH" == "Darwin" ] ; then
    if [ "${OS_MIN}" -lt 12 ]; then
    	echo "You must be running Mac OS 10.14.x or higher to install EOSIO."
    	echo "Exiting now."
    	exit 1
    fi
    if ! [ -x "$(command -v eosio-cpp)" ] ; then
        brew tap eosio/eosio.cdt
        brew install eosio.cdt
    else
        printf "\\neosio.cdt already installed.\\n"
    fi
else 
    printf "\\nUnsupported OS: %s\\n" "${ARCH}"
fi
