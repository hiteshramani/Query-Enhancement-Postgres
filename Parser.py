#!/usr/bin/python
import os
import sys

q_String = sys.argv[1] # Copying arguements in q_String
q_String = (q_String.upper()) # Converting to Uppercase
q_O = "ORDER BY"

pid_Process = open('/tmp/pid_Process.txt','r')
PID = pid_Process.read().rstrip()

# Copy query to the first line of PID.txt and direction to the secondline of PID.txt otherwise leave the file blank(if there is no order by command)
if q_O in q_String:
	q_String_beg = q_String[0:q_String.find(q_O)].strip()
	if "ASC" in q_String[q_String.find(q_O)+8:].strip():
		q_String_dir = "ASC"
	elif "DESC" in q_String[q_String.find(q_O)+8:].strip():
		q_String_dir = "DESC"
	else:
		q_String_dir = "ASC"
	parsed_File = open('/tmp/'+str(PID)+'.txt','w')
	parsed_File.write(q_String_beg+'\n')
	parsed_File.write(q_String_dir)
else:
	parsed_File = open('/tmp/'+str(PID)+'.txt','w')
	parsed_File.write('')
