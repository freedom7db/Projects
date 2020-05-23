import serial,time, threading


ser = serial.Serial(port = "/dev/ttyACM0", baudrate=19200,bytesize=8, timeout=0.2, stopbits=serial.STOPBITS_ONE)

time.sleep(2)


def listening():

	ser.write("AT+CMGF=1\n")
	#time.sleep(0.5)
	ser.write("AT+CNMI=1,2,0,0,0\n")


	while True:
		response=ser.readline() [:-2]
	#	time.sleep(0.5)
		# response=response.decode('utf-8')
		if response:
			print (response)


def send_sms(number,mssg):
	ser.write("AT+CMGF=1\n")
	time.sleep(1)
	ser.write("AT+CMGS=\"+58"+number+"\"\n")
	time.sleep(0.5)
	ser.write(mssg+"\n")
	time.sleep(0.5)
	ser.write(chr(26))


#t=threading.Thread(target=listening)
#t.start()

def get_data_to_send():
	n = raw_input("Enter Number: ") 

	if (n[0]=='0'):
		n=n[1:len(n)]

	t = raw_input("Enter text message: ")

	send_sms(n,t)


#get_data_to_send()
#send_msm("4122059470","testing testing testing testing") 




# ser = serial.Serial("/dev/ttyACM0",19200)
# ser.timeout=2
# ser.open()

# ser.baudrate=9600

# ser.write("AT\n")  # solo, se envia el comando, pero no me da tiempo a reflejar

# ser.write("AT\n")
# time.sleep(5)
# response=ser.readline()
# print (response)


# ser.write("AT+CMGF=1\n")
# time.sleep(1)
# ser.write("AT+CMGS=\"+584123750113\"\n")
# time.sleep(0.5)
# ser.write("Ahora si estoy cansado de verdad!\n")
# time.sleep(0.5)
# ser.write(chr(26))

# for x in xrange(1,10):
# 	ser.write("AT\n")
# 	time.sleep(1)


# while 1:
# 	# ser.write("AT\n")
# 	# time.sleep(0.5)
# 	response=ser.readline()[:-2]
# 	# response=response.decode('utf-8')
# 	if response:
# 		print (response)

	# ser.write("AT\n")
	# time.sleep(0.5)
	# response=ser.readline()
	# print (response)

	# time.sleep(3)
	# ser.write("AT\n")
	# time.sleep(3)
	# response=ser.readline() #[:-2]
	# # response=response.decode('utf-8')
	# # if response:
	# print (response)


# for x in xrange(1,5):
# 	print (x)
# 	ser.write("AT\n")
# 	time.sleep(0.5)
# 	response=ser.readline() #[:-2]
# 	# response=response.decode('utf-8')
# 	# if response:
# 	print (response)


# ser.close()
