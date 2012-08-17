#!/usr/bin/python

import sys
import os

filelist = sys.argv[1:]

#replace every instance of GasCherenkov with WaterCherenkov:
replace = '"s/GasCherenkov/WaterCherenkov/g"'

#set the prefix of the new file name:
prefix = 'WaterCherenkov'

print 'you just performed the following commands:'

for file in filelist:
    suffix = (file[file.find('GasCherenkov')+12:file.rfind('.hh')])
    os.system('sed ' + replace + ' ' + file + ' > include/' + prefix + suffix + '.hh')
    print 'sed ' + replace + ' ' + file + ' > include/' + prefix + suffix + '.hh'
    
