# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import os
import subprocess

def simulate( simulationName ):
	
	#
	# INITIALIZING
	#
	
	# The "Folder" suffix indicates that a variable holds a folder name, as in simulationFolder = "../simulation/"
	# The "Path" suffix means that a variable holds a full file path, as in outputPath = "../simulation/output.txt"
	# The "File" suffix is used to indicate that a variable is a file object, as in outputFile = open("../simulation/output.txt")
	# In general, let X be a token. Then we should be able to write XFile = fopen(XPath) 
	# The "Name" suffix, when applied in the context of files, is a filename, as in programName = "spyder.exe"
	
	print( "> Initializing Program" )
	print( "==== ", simulationName, " ====" )
	
	simulationInputPath = "../_input/input.txt"
	simulationOutputFolder = "../_output/" + simulationName + "/"
	pythonOutputFolder = "../_output/" + simulationName + "/Python_output/"
	programFolder = "../_tests/"
	programName = "collidingspheres_x64.exe"
	
	simulationInputFileString = "<simulationName> " + simulationName
	simulationInputFile = open(simulationInputPath, 'w');
	simulationInputFile.write( simulationInputFileString )

	simulationInputFile.close()
	
	os.makedirs(pythonOutputFolder, exist_ok=True)
	
	print( "< Done" )
	
	#
	# SIMULATING
	#
	
	print( "> Simulating" )
	subprocess.Popen( programFolder + programName )
	print( "< Simulation finished" )
	
	#
	# READ DATA
	#
	
	print("> Reading main output file")
	mainSimulationOutputPath = simulationOutputFolder + "output.txt"
	mainSimulationOutputFile = open(mainSimulationOutputPath, 'r')
	
	
	
	mainSimulationOutputFile.close()
	
