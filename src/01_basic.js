const { SerialPort } = require('serialport');

SerialPort.list().then((ports) => {
  console.log('ports:', ports);
});

// Create a port
const port = new SerialPort({
  path: 'COM3',
  baudRate: 9600,
});

// Write data to the port and listen for data to read
port.write('GET_PHOTO_STATUS', (err) => {
  if (err) {
    console.log('Error on write: ', err.message);
    return err;
  }
  console.log('REQUESTED GET_PHOTO_STATUS');
  return true;
});

// Switches the port into "flowing mode"
port.on('data', (data) => {
  console.log('Data flow:', data.toString());
});

// Open errors will be emitted as an error event
port.on('error', (err) => {
  console.log('Error: ', err.message);
});
