#!/bin/bash

# Define paths to the files to be removed if they exist
FILE1=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/MainGeom/RootAnalysis/EventSelection/Threshold_vs_Rate_files/Threshold_vs_Rate.txt
FILE2=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/MainGeom/RootAnalysis/EventSelection/Thickness_vs_Energy_files/Thickness_vs_Energy.txt
FILE3=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/MainGeom/RootAnalysis/EventSelection/Thickness_vs_Rate_files/Thickness_vs_Rate.txt

# Check if any of the files exist
if test -f "$FILE1" || test -f "$FILE2" || test -f "$FILE3"; then
    # If files exist, prompt user to remove them
    echo "These files exist:"
    echo "$FILE1"
    echo "$FILE2"
    echo "$FILE3"
    read -p "Do you want to remove them? (y)" -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
	# If user confirms, remove files and Execution_time.txt
	echo "Removing files."
	rm $FILE1 $FILE2 $FILE3
	rm Execution_time.txt
	echo
    else
	# If user declines, continue without removing files
	echo "Continuing without removing files..."
	echo
    fi
fi

# Define function to execute root macro
Execute_RootMacro(){

    # Print a blank line for formatting
    echo

    # Execute the root macro using restRoot
    restRoot -l  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/MainGeom/RootAnalysis/EventSelection/SelectEvents.cc
for (int i=0;i<10;i+=1){SelectEvents("ID",200);}
.q
EOC

    # Print a blank line for formatting
    echo

}

# Define path to directory containing selected root files
DIR1=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/MainGeom/RootAnalysis/EventSelection/RootFiles_SelectedEvents

# Check if the directory is empty
if [ -z "$(ls -A $DIR1)" ]; then

    # If the directory is empty, execute the root macro
    echo "No Root files in $DIR1/"
    Execute_RootMacro
    
else
    
    # If the directory is not empty, prompt user before potentially overwriting files
    echo "There are Root files in $DIR1/"
    read -p "Are you sure you want to continue and potentially overwrite those files? (y)" -n 1 -r
    echo

    if [[ $REPLY =~ ^[Yy]$ ]]
    then

	# If user confirms, execute the root macro
	echo
	echo "Entering macro loop..."
	Execute_RootMacro
	echo "End of loop."

    else
	# If user declines, abort
	echo
	echo "Aborting"
    fi
    
    
fi
