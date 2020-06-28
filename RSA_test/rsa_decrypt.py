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
print(text1)

