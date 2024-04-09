# Author           : Kamil Cwynar ( kamilcwynar2003@gmail.com )
# Created On       : 05/05/2023 
# Last modified by : Kamil Cwynar ( kamilcwynar2003@gmail.com )
# Last Modified On : 15/05/2023 
# Version          : 1.2
#
# Description      :
# Compression/decompression scripts for .zip, .tar and .tar.gz extensions. includes split files archives and split assembly.
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)

#!/bin/bash
function file_choice { #lets user choose input file, and splits it into two variables for later usage
FILE_ARG=`zenity --file-selection --title "Name location of file/directory: IN CASE OF SPLIT ASSEMBLY CHOOSE ONE OF THE SPLITS"`
case $? in
         0)
                zenity --info \
	--text="\"$FILE_ARG\" selected.";;
         1)
                zenity --info \
	--text="No file selected.";;
        -1)
                 zenity --info \
	--text="An unexpected error has occurred.";;
esac
INPUT_DIR="$(dirname -- $FILE_ARG)"
INPUT_BASENAME="$(basename -- $FILE_ARG)"
cd ~
cd "$INPUT_DIR" #moves into parent directory of the file
}

function catalog_choice { #lets user choose output dir
CATALOG_ARG=`zenity --file-selection --directory --title "Name compressed/decompressed file output location: "`
case $? in
         0)
                zenity --info \
	--text="\"$CATALOG_ARG\" selected.";;
         1)
                zenity --info \
	--text="No file selected.";;
        -1)
                 zenity --info \
	--text="An unexpected error has occurred.";;
esac
}

function mode_choice { #defines variables to use in Compress_Decompress function
COMP_ARG=`zenity --entry --text "choose mode: zip, unzip, tar, untar, tar.gz, untar.gz, split" `
if [ $COMP_ARG = "zip" ] ; then
	COMP_VIEW="zip compression"
elif [ $COMP_ARG = "unzip" ] ; then
	COMP_VIEW="zip decompression"
elif [ $COMP_ARG = "tar" ] ; then
	COMP_VIEW="tar compression"
	TAR_ARG="-cvf"
elif [ $COMP_ARG = "untar" ] ; then
	COMP_VIEW="tar decompression"
	TAR_ARG="-xvf"
elif [ $COMP_ARG = "tar.gz" ] ; then
	COMP_VIEW="tar.gz compression"
	TAR_ARG="-czvf"
elif [ $COMP_ARG = "untar.gz" ] ; then
	COMP_VIEW="tar.gz decompression"
	TAR_ARG="-xf"
elif [ $COMP_ARG = "split" ] ; then
	COMP_VIEW="split assembly"
else `zenity --info \
	--text="wrong input" \
	--title="error"`
	COMP_VIEW="error"
fi
}

function split_command { 
if [ $SPLIT_BOOL_ARG = "e" ] ; then
	cd ~
	cd "$CATALOG_ARG"
	mkdir "Splits" #makes a dir for split directories,
	mkdir "Splits"/$NAME_ARG"."$COMP_ARG #makes a dir for input file's splits,
	split -d $SPLIT_SIZE_ARG $NAME_ARG".$COMP_ARG" "Splits"/$NAME_ARG"."$COMP_ARG/$NAME_ARG"."$COMP_ARG"_" #splits a given file into $SPLIT_SIZE_ARG sized bits and gives them prefixes according to the output name given
 	rm  $NAME_ARG".$COMP_ARG" #removes unneccessary non-split file
fi
}

function move_c { #moves compressed file to given catalog
mv "$INPUT_DIR/$NAME_ARG.$COMP_ARG" "$CATALOG_ARG"
}

function Compress_Decompress { #depending on the user's input, compresses or decompresses a given file, moves it elsewhere, and splits it if desired
	if   [ -d "$FILE_ARG" ] ; then
		R_ARG="-r"
	else R_ARG=""
	fi
	if [ $COMP_ARG = "zip" ] ; then
		$COMP_ARG -v $R_ARG $NAME_ARG $INPUT_BASENAME | zenity --text-info --width 500 --height 400
		move_c
		split_command
	elif [ $COMP_ARG = "unzip" ] ; then
		mv $INPUT_BASENAME $CATALOG_ARG
		cd ~
		cd $CATALOG_ARG
		$COMP_ARG $INPUT_BASENAME | zenity --text-info --width 500 --height 400
		mv $INPUT_BASENAME $INPUT_DIR
	elif [ $COMP_ARG = "tar" ] ; then
		tar $TAR_ARG $NAME_ARG".tar" $INPUT_BASENAME
		move_c
		split_command
	elif [ $COMP_ARG = "untar" ] ; then
		tar $TAR_ARG $INPUT_BASENAME -C $CATALOG_ARG
	elif [ $COMP_ARG = "tar.gz" ] ; then
		tar $TAR_ARG $NAME_ARG".tar.gz" $INPUT_BASENAME
		move_c
		split_command
	elif [ $COMP_ARG = "untar.gz" ] ; then
		tar $TAR_ARG $INPUT_BASENAME -C $CATALOG_ARG
	elif [ $COMP_ARG = "split" ] ; then
		INPUT_DIR_BASENAME="$(basename -- $INPUT_DIR)"
		cd ..
		touch "Assembled_"$INPUT_DIR_BASENAME
		cat $INPUT_DIR_BASENAME/* > "Assembled_"$INPUT_DIR_BASENAME
		mv "Assembled_"$INPUT_DIR_BASENAME "$CATALOG_ARG"
	else
		`zenity --info \
		--text="wrong input, check for errors in menu" \
		--title="error"`
	fi 
}

function Split_menu {
option2(){
menu=("Split enabled: $SPLIT_BOOL_ARG" "Max size per split: $SPLIT_SIZE" "Go back")
OPTION=$(zenity --list --column=Menu "${menu[@]}" --width 600 --height 450)
}

while [ "$OPTION" != "Go back" ] ; do

option2
case $OPTION in

"Split enabled: "*)
SPLIT_BOOL_ARG=`zenity --entry --text "e - split enabled  d - split disabled"`
;;

"Max size per split: "*)
SPLIT_SIZE=`zenity --entry --text "Name max size of each split"`
if [ $SPLIT_SIZE ] ; then
	SPLIT_SIZE_ARG="-b $SPLIT_SIZE"
fi
;;

"Go back"*)
;;
esac

done
}

option(){
menu=("To be compressed/decompressed location: $FILE_ARG" "Output file name: $NAME_ARG" "Compressed/decompressed file output location: $CATALOG_ARG" "Split archives menu" "Compress/decompress mode: $COMP_VIEW" "Compress/decompress" "About" "Help" "Quit")
OPTION=$(zenity --list --column=Menu "${menu[@]}" --width 600 --height 450)
}

SPLIT_BOOL_ARG="d"
SPLIT_SIZE="1K"
SPLIT_SIZE_ARG="-b 1K"
CATALOG_ARG="$HOME"
COMP_VIEW="zip compression"
COMP_ARG="zip"
NAME_ARG="New_file"
while [ "$OPTION" != "Quit" ] ; do

option
case $OPTION in

"To be compressed/decompressed location: "*)
file_choice
;;

"Output file name: "*)
NAME_ARG=`zenity --entry --text "Give output file name/Split prefix to assembly"`
;;

"Compressed/decompressed file output location: "*)
catalog_choice
;;

"Split archives menu"*)
Split_menu
;;

"Compress/decompress mode: "*)
mode_choice
;;

"Compress/decompress"*)
Compress_Decompress
;;

"About"*)
`zenity --info \
	--text="Author           : Kamil Cwynar ( kamilcwynar2003@gmail.com )
Created On       : 05/05/2023 
Last modified by : Kamil Cwynar ( kamilcwynar2003@gmail.com )
Last Modified On : 15/05/2023 
Version          : 1.2

Description      :
Compression/decompression scripts for .zip, .tar and .tar.gz extensions. includes split files archives and split assembly.

Licensed under GPL (see /usr/share/common-licenses/GPL for more details
or contact # the Free Software Foundation for a copy)" \
	--title="About"`
;;

"Help"*)
`zenity --info \
	--text="To be compressed/decompressed location: lets you choose the file/directory for the script to work on. Chosen location will be shown in the menu 

Output file name:  lets you name the file/files that will be created upon pressing compress/decompress option. Extension is given automatically during the script's work 

Compressed/decompressed file output location: lets you choose the firectory to which output file/files will be moved upon completion of the script's work 

Split archives menu: opens menu for split making, which contains two new options: 

Split enabled: input e to enable, d to disable - disabled by default
Max size per split: let's you choose how big each split can be: can be inputed with numbers alone (for bits) or K for kilobits, M for megabits acvordingly. 1K by default. Only taken into consideration when splits enabled. 

Compress/decompress mode:
Lets you choose what the scripts should do with the given file/files. Options given when the options is chosen. Chosen mode will be displayed in the menu. Error in case of incorrect input.
Compress/decompress: takes the input file/files and turns them into desired output file/files, accordingly to previous option choices 

About: shows information panel about the script and its author 

Help: shows this information panel 

Quit: concludes the scripts work, closing it. Previous choices are not saved and are returned to deafult" \
	--title="Help"`
;;

"Quit"*)
;;
esac

done
