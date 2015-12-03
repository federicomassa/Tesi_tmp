#!/bin/sh

tar -cf Presentation_25-11.tar Immagini/pi15_*
tar --append --file=Presentation_25-11.tar Immagini/pi50_*
tar --append --file=Presentation_25-11.tar Immagini/pi100_*
tar --append --file=Presentation_25-11.tar Immagini/mu15_*
tar --append --file=Presentation_25-11.tar Immagini/mu50_*
tar --append --file=Presentation_25-11.tar Immagini/mu100_*
tar --append --file=Presentation_25-11.tar Immagini/pi*mu*pu*
tar --append --file=Presentation_25-11.tar Immagini/pipu*
tar --append --file=Presentation_25-11.tar Immagini/mupu*
tar --append --file=Presentation_25-11.tar Immagini/*kin*

tar --list --file=Presentation_25-11.tar