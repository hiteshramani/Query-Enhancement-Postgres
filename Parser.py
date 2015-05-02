#!/usr/bin/python
import os
import sys
#f = open("/tmp/test.txt","w")
os.system("id > /tmp/id.out")

q_String = sys.argv[1]
q_String = (q_String.upper())
q_O = "ORDER BY"
if q_O in q_String:
	q_String_beg = q_String[0:q_String.find(q_O)].strip()
	if "ASC" in q_String[q_String.find(q_O)+8:].strip():
		q_String_dir = "ASC"
	elif "DESC" in q_String[q_String.find(q_O)+8:].strip():
		q_String_dir = "DESC"
	else:
		q_String_dir = "ASC"
	#/home/hitesh/Desktop/Project/Project_Final_Work
	parsed_File = open('/tmp/Parsed_Query.txt','w')
	parsed_File.write(q_String_beg+'\n')
	parsed_File.write(q_String_dir)
else:
	parsed_File = open('/tmp/Parsed_Query.txt','w')
	parsed_File.write('')
