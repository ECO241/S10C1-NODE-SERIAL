const { SerialPort, ReadlineParser } = require('serialport');

// Create a port
const port = new SerialPort({
  path: 'COM3',
  baudRate: 9600,
});

// Create a parser
const parser = new ReadlineParser({ delimiter: '\n' });
// Pipe the port data to the parser
port.pipe(parser);

// Creating the parser and piping can be shortened to:
// const parser = port.pipe(new ReadlineParser())

parser.on('data', (data) => {
  console.log('incoming message:', data.toString());
  // port.write('GET_PHOTO_STATUS\n');
  // port.write('GET_TEMP_STATUS\n');
});

port.write('GET_PHOTO_STATUS\n', (err) => {
  if (err) {
    console.log('Error on write: ', err.message);
    return err;
  }
  console.log('message written');
  return true;
});

// detect errors
port.on('error', (err) => {
  console.log('Error: ', err.message);
});
