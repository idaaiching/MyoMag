###################
#
# PyMyomag_main.py 
#
# This file imports the PyMyomag module and presents how it can be used. Basically
# it calcualtes the magnitude of a signal (time, x, y, z acceleration)
# by reading in a csv file of its values.
#
# magnitude_arr = PyMyomag.PyMyomag( DataFile, nlines, nsplits)
# arg: 
#  - DataFile: String of the csv file name
#  - nlines: integer of number of lines in csv
#  - nsplits: integer in how many parts the csv file is splitted to read in  (for memory optimization)
# result: 
#  - magnitude_arr: an array with the magnitude of each csv line

import os
import PyMyomag

DataFile = "AccData.csv"
nlines = 7024
nsplits = 5

magnitude_arr = PyMyomag.PyMyomag( DataFile, nlines, nsplits)
print("Magnitude in line 0,100, 6000 and 7023:",
	magnitude_arr[0], magnitude_arr[100], magnitude_arr[6000], magnitude_arr[7023]
	)