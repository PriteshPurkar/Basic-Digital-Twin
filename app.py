from flask import Flask, request, jsonify, send_from_directory

app = Flask(__name__)
battery_level = 0

@app.route('/')
def index():
    return send_from_directory('.', 'index.html')  # serve static HTML

@app.route('/update')
def update():
    global battery_level
    level = request.args.get("level")
    if level is not None:
        battery_level = int(level)
        print(f"✅ Battery updated to {battery_level}%")
    return "OK"

@app.route('/get_level')
def get_level():
    return jsonify({"level": battery_level})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
