from flask import Flask, request, render_template
import socket

app = Flask(__name__)

s = socket.socket()
s.connect(("127.0.0.1", 8420))

@app.route('/')
def my_form():
    return render_template('sendmessage.html')

@app.route('/', methods=['POST'])
def my_form_post():
    text = request.form['text']
    processed_text = text.upper()
    try:
        s.send(processed_text.encode("utf-8"))
        return "Send successful"

    except Exception:
        return "Unsuccessful"

    else:
        return "Unsuccessful"
