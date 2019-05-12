import socket
import struct
import asyncio
import websockets
import pickle
import time
import sys
import os
import sqlite3
# enxb827eb9cd99f

conn = sqlite3.connect('DoorLock.db')
cur = conn.cursor()

cur.execute('CREATE TABLE IF NOT EXISTS log( YEAR INTEGER, MONTH INTEGER, DAY INTEGER, TIME TEXT, ID TEXT, TIMESTRING INTEGER)')
cur.execute('CREATE TABLE IF NOT EXISTS user( ID text PRIMARY KEY, NAME text DEFAULT "name", ROLE text DEFAULT "role", PERM text DEFAULT "0")')

def make_timestring(year, month, day):
	return int(year + two_digit(month) + two_digit(day))

def two_digit(text):
	if len(text) < 2:
		return '0' + text
	else:
		return text


def get_ipaddress(network):
    return socket.gethostbyname(socket.getfqdn())

async def Account_Lookup(websocket):
	global cur, conn
	count, message = 0, ''
	while(count < 4):
		message += await websocket.recv()
		count += 1
	cur.execute("SELECT ID FROM user WHERE ID=(?)",(message, ))
	exist = cur.fetchone()
	if exist is not None:
		await websocket.send('1')
		print("회원입니다")
		#로그파일 저장
		now = time.localtime(time.time()) #현재시각을 가져온다.
		cur.execute('INSERT INTO log VALUES(?, ?, ?, ?, ?, ?)', (now.tm_year, now.tm_mon, now.tm_mday,
		 str(now.tm_hour)+':'+str(now.tm_min)+':'+str(now.tm_sec), message, make_timestring(str(now.tm_year), str(now.tm_mon), str(now.tm_mday))))
		conn.commit()
	else:
		await websocket.send('0')
		print("비회원입니다")

async def Account_Register(websocket):
	global cur, conn
	count, message = 0, ''
	while(count < 4):
		message += await websocket.recv()
		count += 1
	cur.execute("SELECT ID FROM user WHERE ID=(?)",(message, ))
	exist = cur.fetchone()
	if exist is not None:
		await websocket.send('3')
		print("이미 회원입니다")
	else:
		await websocket.send('2')
		print("등록되었습니다")
		cur.execute('INSERT INTO user(ID) VALUES(?)', (message, ))
		conn.commit()

def Webcam_streaming(websocket):
	pass
def Webcam_Capturing(websocket):
	pass

async def LogLookUp(websocket):
	global cur, conn
	count, start, end = 0, '', ''
	while(count < 2):
		if count == 0: start = await websocket.recv()
		if count == 1: end = await websocket.recv()
		count += 1
	start = start.split('-')
	end = end.split('-')
	cur.execute("SELECT * FROM log l, user u WHERE (l.TIMESTRING BETWEEN ? AND ?) AND l.ID == u.ID",
		(make_timestring(start[0],start[1],start[2]), make_timestring(end[0],end[1],end[2])))
	for i in cur:
		await websocket.send(str(i[0])+'년 '+str(i[1])+'월 '+str(i[2])+'일 '+i[3]+' - '+i[8])
	await websocket.send('End')

def photoLookUp(websocket):
	pass
def UserLookUp(websocket):
	pass

async def Login(websocket):
	global cur, conn
	UUID = ''
	UUID = await websocket.recv()
	cur.execute("SELECT ROLE FROM user WHERE ID=(?)",(UUID, ))
	exist = cur.fetchone()
	if exist is not None:
		await websocket.send(exist[0])
	else:
		await websocket.send('false')



async def echo(websocket, path):
	message = await websocket.recv() 

	#try:
	if message == '1':
		print('Account_Lookup')
		await Account_Lookup(websocket)
	elif message == '2':
		print('Account_Register')
		await Account_Register(websocket)
	elif message == '3':
		print('Webcam_streaming')
	elif message == '4':
		print('Webcam_Capturing')
	elif message == '5':
		await LogLookUp(websocket)
	elif message == '6':
		print('photoLookUp')
	elif message == '7':
		print('UserLookUp')
	elif message == '8':
		print('Login')
		await Login(websocket)
	#except:
	#	print("Unexpected error:", sys.exc_info()[0])

 
print("Server start: "+get_ipaddress('enxb827eb9cd99f'))
 
port = 180
asyncio.get_event_loop().run_until_complete(
	websockets.serve(echo, get_ipaddress('enxb827eb9cd99f'), port, close_timeout = 100))
asyncio.get_event_loop().run_forever()
