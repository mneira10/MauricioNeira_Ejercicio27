#!/bin/bash
#PBS -l nodes=1:ppn=4,mem=1gb,walltime=00:10:00
#PBS -M m.neira10@uniandes.edu.co
#PBS -m abe
#PBS -N mneira10_listing12_2
#PBS -j oe


cd /hpcfs/home/fisi4028/m.neira10/MauricioNeira_Ejercicio27/listing12_2
make
