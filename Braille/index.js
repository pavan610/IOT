const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
})

const { text_to_braille } = require('./braille');
 

const five = require("johnny-five");
const board = new five.Board({port:"COM4"});

// let message = '';
// while(message!=='exit'){
//   readline.question(`Enter Message :( To quit press exit ) \n`, (message) => {
//     console.log(text_to_braille(message))
//     readline.close()
//   })
  board.on("ready", function() {

    const led1 = new five.Led(8);
    const led2 = new five.Led(9);
    const led3 = new five.Led(10);
    const led4 = new five.Led(11);
    const led5 = new five.Led(12);
    const led6 = new five.Led(13);
    
    const motor1 = new five.Led(2);
    const motor2 = new five.Led(3);
    const motor3 = new five.Led(4)
    const motor4 = new five.Led(5);
    const motor5 = new five.Led(6)
    const motor6 = new five.Led(7);
    
    led1.on();
    led2.on();
    led3.on();
    led4.on();
    led5.on();
    led6.on();

    motor1.on();
    motor2.on();
    motor3.on();
    motor4.on();
    motor5.on();
    motor6.on();
  
  
  });  
// }

