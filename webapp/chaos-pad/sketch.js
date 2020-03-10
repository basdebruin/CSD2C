/*
    Sketch op basis van csdosc-master,
    aangepast voor CSD2C eindopdracht
*/


let client;
let connect;
let x, y;
let touching = false;

function setup() {
    createCanvas(640, 480);
    //maak een connect-object aan dat zorgt voor de communicatie met oscServer.js
    connect = new Connect();

    //maak verbinding met oscServer.js, en voer code tussen {} uit zodra deze verbinding tot stand is gekomen.
    connect.connectToServer(function () {
        //maak een nieuwe client-object aan.
        client = new Client();

        //start de client en laat deze berichten sturen naar het ip-adres 127.0.0.1 en poort 9000
        client.startClient("127.0.0.1", 9000);
    });

    x = 100;
    y = 100;
}

function draw() {
    background(40, 40, 50, 30);
    //
    touching = mouseIsPressed;
    //ellipse(x * width, y * height, 10);
    drawGrid();
}

// on mouse move
mouseDragged = () => mouseMoved();
function mouseMoved() {

    x = map(mouseX, 0, width, 0, 1);
    y = map(mouseY, 0, height, 0, 1);

    //stuur een bericht naar het adres /x met als waarde de x-positie van de muis
    client.sendMessage("/x", x);

    //stuur een bericht naar het adres /y met als waarde de y-positie van de muis.
    client.sendMessage("/y", y);
}

// send "/filter" message
function setFilter(filt) {
    client.sendMessage("/filter", filt);
    console.log("Set filter to: " + filt);
}



function drawGrid() {
    // i and j as x and y grid
    for (let i = 0; i < 8; i++) {
        for (let j = 0; j < 8; j++) {

            const pos = {
                x: i * (width/8),
                y: j * (height/8)
            }

            push();
                stroke('#445');
                strokeWeight(2);
                noFill();

                rect(pos.x, pos.y, width/8, height/8);
            pop();

            if (touching) {
                const gridpos = {
                    x: int(x * 8),
                    y: int(y * 8)
                }
                // draw red squares around mouse/touch position
                if (
                    (gridpos.x-1 == i && gridpos.y == j) || 
                    (gridpos.x+1 == i && gridpos.y == j) ||
                    (gridpos.y-1 == j && gridpos.x == i) ||
                    (gridpos.y+1 == j && gridpos.x == i)
                    ) {
                        push();
                            noStroke();
                            fill('#f33');
                            rect(pos.x, pos.y, width/8, height/8);
                        pop();
                    }
            }

        }
    }
}