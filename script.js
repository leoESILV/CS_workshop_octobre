

//const test = 1;
//let test2 = 2;
//var test3 = 3;


var ws;
var motorState = false;
var ledState = false;

function initWebSocket() {
    ws = new WebSocket('ws://10.1.224.40');

    ws.onopen = function () {
        document.getElementById('status').innerHTML = "WebSocket est connecté";
    };

    ws.onmessage = function (event) {
        console.log(event.data);
        if (event.data.includes("temp:")) {
            document.getElementById('temperature').innerText = event.data.split(":")[1] + "°";
        }
    };

    ws.onclose = function () {
        document.getElementById('status').innerHTML = "WebSocket déconnecté";
    };
}

document.getElementById('motorButton').addEventListener('click', function () {
    motorState = !motorState;
    ws.send(motorState ? 'MOTOR_ON' : 'MOTOR_OFF');
    document.getElementById('motorButton').innerText = motorState ? 'OFF' : 'ON';
});

document.getElementById('ledButton').addEventListener('click', function () {
    ledState = !ledState;
    ws.send(ledState ? 'LED_ON' : 'LED_OFF');
    document.getElementById('ledButton').innerText = ledState ? 'OFF' : 'ON';
});

window.onload = function () {
    initWebSocket();
};
