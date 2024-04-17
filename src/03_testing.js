const { SerialPortStream } = require('@serialport/stream');
const { MockBinding } = require('@serialport/binding-mock');

// Create a port and enable the echo and recording.
MockBinding.createPort('/dev/ROBOT', { echo: true, record: true });
const port = new SerialPortStream({ binding: MockBinding, path: '/dev/ROBOT', baudRate: 9600 });

port.on('data', (data) => {
  console.log('Data:', data.toString());
});

port.on('open', () => {
  port.port.emitData('pretend data from device');
});
