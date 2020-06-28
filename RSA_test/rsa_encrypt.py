# -*- coding: utf-8 -*
import rsa
def rsa_encrypt(message):
	crypto_email_text = rsa.encrypt(message.encode(), pubkey)
	return crypto_email_text

with open('./pubkey.pem' ,'r') as f:
	pubkey = rsa.PublicKey.load_pkcs1(f.read().encode())

f1=open('wangzepeng.txt','r')
text=f1.read()
text1 = rsa_encrypt(text)

print(text1)

with open("encrypt_message.txt", "w") as f:
	f.write(str(text1))
	f.close()

