# -*- coding: utf-8 -*
import rsa
def rsa_decrypt(message):
	message_str = rsa.decrypt(message,privkey).decode()
	return message_str

with open('./rsa_private_key.pem' ,'r') as f:
	privkey = rsa.PrivateKey.load_pkcs1(f.read().encode())

f1=open('encrypt_message.txt','r')
text=f1.read()
text1 = rsa_decrypt(text)
#print(text1)
sep=text1.find('.txt')	# 使用find方法找到标题与文本的分界位置

title=text1[:sep+4]	# 分离得到标题字符串
#print(title)
content=text1[sep+4:]	# 分离得到文本字符串
#print(content)

with open(title, "w") as f2:
	f2.write(str(content))
	f2.close()
