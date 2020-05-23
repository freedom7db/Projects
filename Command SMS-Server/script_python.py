import serial,time, threading, os


ser = serial.Serial(port = "/dev/ttyACM0", baudrate=19200,bytesize=8, timeout=0.2, stopbits=serial.STOPBITS_ONE)

time.sleep(2)
command_test_internet = 'sh internet.sh'


def listening():

	while True:
		response=ser.readline() [:-2]
	#	time.sleep(0.5)
		# response=response.decode('utf-8')
		if response:
			print (response)
			
			if '+CMT' in response:
				number=response[8:18]
				print number
			if "internet" in response:

				os.system(command_test_internet)
				file = open(".connection.txt",'r')
				x = file.read(1)

				if (x=='1'):
					print send_sms(number,'[+] Your server is Connected') 
				else:
					print send_sms(number,'[-] Your server is Disconnected')

				print '[+] Internet status notify to admin' 
			


def send_sms(number,mssg):
	ser.write("AT+CMGF=1\n")
	time.sleep(1)
	ser.write("AT+CMGS=\"+58"+number+"\"\n")
	time.sleep(0.5)
	ser.write(mssg+"\n")
	time.sleep(0.5)
	ser.write(chr(26))


def get_data_to_send():
	n = raw_input("Enter Number: ") 

	if (n[0]=='0'):
		n=n[1:len(n)]

	t = raw_input("Enter text message: ")

	send_sms(n,t)



listening()

"""
n = "+CMT: \"04129381044\",\"\",\"19/10/18,12:52:06-16"
if '+CMT' in n:
	n=n[8:18]

print n

"""
"""
n = raw_input("Enter Admin Number: ") 

if (n[0]=='0'):
	n=n[1:len(n)]

command = 'sh internet.sh'
os.system(command)
file = open(".connection.txt",'r')
x = file.read(1)

if (x=='1'):
	print send_sms(n,'Connected') 
else:
	print send_sms(n,'Disconnected')

print '[+] Internet status notify to admin' 
"""



#listening()
#t=threading.Thread(target=listening)
#t.start()

#s = "hola como estas"
#if "hola" in s:
#	print "esta"

