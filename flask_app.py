from flask import Flask, request, render_template, redirect, url_for, current_app
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'  # SQLite database for simplicity
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(80), nullable=False)
    voice_data = db.Column(db.String(200), nullable=False)

# Initialize the database
def init_db():
    with app.app_context():
        db.create_all()

# Function to add a new user to the database
def add_user(username, password, voice_data):
    with app.app_context():
        new_user = User(username=username, password=password, voice_data=voice_data)
        db.session.add(new_user)
        db.session.commit()

init_db()  # Initialize the database

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        voice_data = request.form['voice_data']

        add_user(username, password, voice_data)
        return render_template('auth_success.html')

    return render_template('register.html')

@app.route('/')
def home():
   return render_template('home.html')

if __name__ == '__main__':
    app.run(debug=True)
