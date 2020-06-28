# -*- coding: utf-8 -*
import sys
import rsa
def rsa_encrypt(message):
	crypto_email_text = rsa.encrypt(message.encode(), pubkey)
	return crypto_email_text

if __name__=="__main__":
	with open('./pubkey.pem' ,'r') as f:
		pubkey = rsa.PublicKey.load_pkcs1(f.read().encode())

	#title='wangzepeng.txt'
	title=sys.argv[1]
	f1=open(title,'r')
	text=f1.read()
	text1=title+text
	text2 = rsa_encrypt(text1)
	#print(text1)

	with open("encrypt_message.txt", "w") as f:
		f.write(str(text2))
		f.close()
