#!/bin/sh

echo "Are you sure you want to remove all the samples?"
select yn in "Yes" "No"; do
    case $yn in
        Yes )
	    rm -r pi15;
	    rm -r pi50;
	    rm -r pi100;
	    rm -r mu15;
	    rm -r mu50;
	    rm -r mu100;
	    break;;
        No ) exit;;
    esac
done