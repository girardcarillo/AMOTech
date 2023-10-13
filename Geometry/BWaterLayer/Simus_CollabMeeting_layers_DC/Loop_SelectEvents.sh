#!/bin/bash

# Define paths to the files to be removed if they exist
FILE1=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/TxtFiles_Thickness_vs_AttenuationAllPart/Thickness_vs_AttenuationAllPart.txt
FILE2=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/TxtFiles_Thickness_vs_Attenuation/Thickness_vs_Attenuation.txt
FILE3=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/TxtFiles_Thickness_vs_AttenuationNeutron/Thickness_vs_AttenuationNeutron.txt
FILE4=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/TxtFiles_Thickness_vs_AttenuationGamma/Thickness_vs_AttenuationGamma.txt
FILE5=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/TxtFiles_Thickness_vs_AttenuationGenerator/Thickness_vs_AttenuationGenerator.txt

# Check if any of the files exist
if test -f "$FILE1" || test -f "$FILE2" || test -f "$FILE3" || test -f "$FILE4" || test -f "$FILE5"; then
    # If files exist, prompt user to remove them
    echo "These files exist:"
    echo "$FILE1"
    echo "$FILE2"
    echo "$FILE3"
    echo "$FILE4"
    echo "$FILE5"
    read -p "Do you want to remove them? (y)" -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
	# If user confirms, remove files and Execution_time.txt
	echo "Removing files."
	rm $FILE1 $FILE2 $FILE3 $FILE4 $FILE5 $FILE6 $FILE7
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
    # SelectEvents(string partType, bool Armor = 0, bool Water = 0, bool Concrete = 0, bool Iron = 0, bool IronOnTop = 0)

    ########
    # Iron Top
    # ID SelectEvents("neutron")
    # ID Iron SelectEvents("neutron",0,0,0,1,1)
    # ID Concrete Iron SelectEvents("neutron",0,0,1,1,1)
    # ID Water Concrete Iron SelectEvents("neutron",0,1,1,1,1)
    # ID OV Water Concrete Iron SelectEvents("neutron",1,1,1,1,1)


    # Iron Below
    # ID SelectEvents("neutron")
    # ID Concrete SelectEvents("neutron",0,0,1,0,0)
    # ID Iron Concrete SelectEvents("neutron",0,0,1,1,0)
    # ID Water Iron Concrete SelectEvents("neutron",0,1,1,1,0)
    # ID OV Water Iron Concrete SelectEvents("neutron",1,1,1,1,0)

    # for Iron on top    
    restRoot -l  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/SelectEvents.cc
SelectEvents("neutron")
SelectEvents("neutron",0,0,0,1,1)
SelectEvents("neutron",0,0,1,1,1)
SelectEvents("neutron",0,1,1,1,1)
SelectEvents("neutron",1,1,1,1,1)
.q
EOC

    source mvTxtFilesNeutronIronTop.sh
    # for Iron below
    restRoot -l  <<EOC
    .L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/SelectEvents.cc
SelectEvents("neutron")
SelectEvents("neutron",0,0,1,0,0)
SelectEvents("neutron",0,0,1,1,0)
SelectEvents("neutron",0,1,1,1,0)
SelectEvents("neutron",1,1,1,1,0)
.q
EOC

    source mvTxtFilesNeutronIronBelow.sh

    ###############


    #     ######### for neutron simus with Concrete and Iron
    #     restRoot -l  <<EOC
    # .L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/SelectEvents.cc
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"20","neutron",1,0,1,1);}
    # .q
    # EOC

    #     source mvTxtFilesNeutronConcreteIron.sh 20

    #     restRoot -l  <<EOC
    # .L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/SelectEvents.cc
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"100","neutron",1,0,1,1);}
    # .q
    # EOC

    #     source mvTxtFilesNeutronConcreteIron.sh 100

    #     ###############

    
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"2.6","gamma",1);}
    
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"1","neutron",0,0,1);}
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"1","neutron",1,0,1);}
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"100","neutron",0,0,1);}
    # for (int i=100;i<600;i+=400){SelectEvents("or",i,"100","neutron",1,0,1);}
    
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"1","neutron",0,1);}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"1","neutron",1,1);}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"100","neutron");}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"100","neutron",1);}

    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"1","neutron");}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"1","neutron",1);}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"20","neutron");}
    # for (int i=100;i<600;i+=100){SelectEvents("or",i,"20","neutron",1);}

    # Print a blank line for formatting
    echo

}

# Define path to directory containing selected root files
DIR1=/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/Simus_CollabMeeting_layers_DC/RootFiles_SelectedEvents

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
