# -*- coding: utf-8 -*- 
import socket
import sys
from PIL import Image
import os
import io
from array import array
import base64
 
host = '192.168.137.1'
port = 4000
addr = (host, port)
 
pr = ['1.height', '2.width']
 
def run():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    
    try:
      s.connect(addr)
    except Exception as e:
      print('서버 (%s:%s)에 연결 할 수 없습니다.' % addr)
      sys.exit()
    print('서버 (%s:%s)에 연결 되었습니다.' % addr)
   
    #비트맵 바이트로 변환시키기
    fd = open('test.bmp', "rb")
    b = bytearray(fd.read())
    s.sendall(b) # 서버로 보내기
    print('바이트 이미지 전송 완료')
    fd.close()
    #resp = s.recv(65536)
    #server_image = resp # 서버로부터 받은 이미지 바이트 값 server_image 변수에 저장
    #print('서버에서 받은 바이트 이미지 길이 :', end=" ")
    #print(len(resp))
 
    '''
    #비트맵 문자열로 변환시키기
    fd = open('test.bmp', "rb")
    str = base64.b64encode(fd.read())
    s.sendall(str)
    fd.close()
    resp = s.recv(65536)
    print(resp)
    '''
    
    for i in pr: # height과 width 값 입력 후 서버로 보내기
      msg = "400"#input(i + ' : ')
      s.sendall(msg.encode())
      print('서버로 보냄')
      #resp = s.recv(1024)
      #print(f'{resp.decode()} 서버로부터 다시 받음')
    
    
    # 서버로 받은 이미지 바이트 값을 다시 이미지로 복원하기
    print("서버로 받은 이미지를 보시겠습니까? (y/n)")
    ans = input(':')
    if(ans == 'y'):
      image = Image.open(io.BytesIO(server_image)) # 바이트 이미지 다시 이미지로 만듬
      image.show()
    else:
      print('이미지 종료')
    
    
    '''  
    stopper = 0
    while True:
      if(stopper > 2):
        break
      resp = s.recv(1024)
      print(f'{resp.decode()}')
      stopper += 1
    '''
    s.close()
 
if __name__ == '__main__':
  run()
 
'''
def run():
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(('127.0.0.1', 4000)) // 호스트와 포트로 서버 연결 진행
    line = input(':') // 입력 값
    s.sendall(line.encode()) // 입력된 값을 서버로 전송
    resp = s.recv(1024) // 서버로부터 recv를 통해 데이터 받음
    print(f'>{resp.decode()}') // 받은 데이터를 출력
if __name__ == '__main__':
  run()
'''
