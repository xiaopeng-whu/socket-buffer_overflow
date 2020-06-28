# -*- coding: utf-8 -*
import rsa
def rsa_encrypt(message):
	crypto_email_text = rsa.encrypt(message.encode(), pubkey)
	return crypto_email_text
def rsa_decrypt(message):
	message_str = rsa.decrypt(message,privkey).decode()
	return message_str


with open('./pubkey.pem' ,'r') as f:
	pubkey = rsa.PublicKey.load_pkcs1(f.read().encode())

with open('./rsa_private_key.pem' ,'r') as f:
	privkey = rsa.PrivateKey.load_pkcs1(f.read().encode())

text = rsa_encrypt("hello world")
print(text)
text1 = rsa_decrypt(text)
print(text1)

