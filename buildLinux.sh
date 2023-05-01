#!/bin/bash

export PWD=`pwd`
if [ -z "$HT" ] ; then
	HT=LINUX-x86_64
fi


RESTVARCMAKE=()
RESTVARMAKE=()
getmake=false
while [ $# -gt 0 ]
do
  case $1 in
	-source         ) shift ; if [ $# -gt 0 ] ; then SOURCE="$1" ; fi ;;
    -build          ) shift ; if [ $# -gt 0 ] ; then BUILD="$1/$HT" ; fi ;;
    -generator      ) shift ; if [ $# -gt 0 ] ; then GENERATOR="$1" ; fi ;;
    -compiler       ) shift ; if [ $# -gt 0 ] ; then COMPILER="$1" ; fi ;;
    -make           ) shift ; if [ $# -gt 0 ] ; then MAKE="$1" ; fi ;;
    --              ) getmake=true ;;
    *               )
        if [ $getmake = true ] ; then
            RESTVARMAKE=("${RESTVARMAKE[@]}" "$1")
        else
            RESTVARCMAKE=("${RESTVARCMAKE[@]}" "$1")
        fi
        ;;
  esac
  shift
done

if [ -z "$SOURCE" ] ; then SOURCE=. ; fi
if [ -z "$BUILD" ] ; then BUILD=build/$HT ; fi

# Clean-up workspace
if [ -d "$BUILD" ] ; then
	rm -rf "$BUILD"
fi
mkdir -p "$BUILD"

echo ::::::::::::::::::::: call cmake ::::::::::::::::::::
if [ -z "$COMPILER" ] ; then
    if (( ${#RESTVARCMAKE[@]} == 0 )); then
        if [ -z "$GENERATOR" ] ; then
            cmake -S "$SOURCE" -B "$BUILD"
        else
            cmake -G "$GENERATOR" -S "$SOURCE" -B "$BUILD"
        fi
    else
        if [ -z "$GENERATOR" ] ; then
            cmake "${RESTVARCMAKE[@]}" -S "$SOURCE" -B "$BUILD"
        else
            cmake "${RESTVARCMAKE[@]}" -G "$GENERATOR" -S "$SOURCE" -B "$BUILD"
        fi
    fi
else
    if (( ${#RESTVARCMAKE[@]} == 0 )); then
        if [ -z "$GENERATOR" ] ; then
            cmake -DCMAKE_CXX_COMPILER="$COMPILER" -S "$SOURCE" -B "$BUILD"
        else
            cmake -DCMAKE_CXX_COMPILER="$COMPILER" -G "$GENERATOR" -S "$SOURCE" -B "$BUILD"
        fi
    else
        if [ -z "$GENERATOR" ] ; then
            cmake "${RESTVARCMAKE[@]}" -DCMAKE_CXX_COMPILER="$COMPILER" -S "$SOURCE" -B "$BUILD"
        else
            cmake "${RESTVARCMAKE[@]}" -DCMAKE_CXX_COMPILER="$COMPILER" -G "$GENERATOR" -S "$SOURCE" -B "$BUILD"
        fi
    fi
fi

echo ::::::::::::::::::::: call make :::::::::::::::::::::
cd "$BUILD"
if [ -z "$MAKE" ] ; then MAKE=make ; fi
if (( ${#RESTVARMAKE[@]} == 0 )); then
    "$MAKE"
else
    "$MAKE" "${RESTVARCMAKE[@]}"
fi