#!/bin/sh


echo "Are you sure you want to re-run all the samples? It could take some time..."
select yn in "Yes" "No"; do
    case $yn in
        Yes ) 
	    rm -r pi15;
	    rm -r pi50;
	    rm -r pi100;

	    rm -r mu15;
	    rm -r mu50;
	    rm -r mu100;

	    ITkRun pi15 datasetPi_15GeV 211 15000;
	    ITkRun pi50 datasetPi_50GeV 211 50000;
	    ITkRun pi100 datasetPi_100GeV 211 100000;

	    ITkRun mu15 datasetMu_15GeV 13 15000;
	    ITkRun mu50 datasetMu_50GeV 13 50000;
	    ITkRun mu100 datasetMu_100GeV 13 100000; 
	    break;;
        No ) exit;;
    esac
done