/* Copyright (c) 2019, Team2
 *
/** @example examples/puck
 *
 * @brief Puck Application main file.
 *
 * This file contains the source code for a sample application that acts as a BLE Central device.
 * This application scans for the Puck and reads its data.
 */

'use strict';

const api = require('../index');
const path = require('path');

const adapterFactory = api.AdapterFactory.getInstance(undefined, { enablePolling: false });

//Battery service
const BLE_UUID_BAT_SERVICE = '180F';
const BLE_UUID_BAT_CHAR = '2A19';
const BLE_UUID_CCCD = '2902';	//For both BAT and NUS services

//Nordic UART service (NUS)
const BLE_UUID_NUS_SREVICE = '6E400001B5A3F393E0A9E50E24DCCA9E';
const BLE_UUID_NUS_TX_CHARACTERISTIC = '6E400003B5A3F393E0A9E50E24DCCA9E';

//SAADC service	
const BLE_UUID_SAADC_SERVICE_UUID = 'CC1D000173764BFAAEEA1D69C99BB7F5';
const BLE_UUID_SAADC_VALUES_CHAR_UUID = 'CC1D000273764BFAAEEA1D69C99BB7F5';
const BLE_UUID_SAADC_CCCD = '2901';	//Different CCCD for SAADC service
var saadc_char;


// Function for enabling battery notifications
function enable_bat_notif(adapter, device){
	return new Promise((resolve, reject) => {
	discoverService(adapter, device, BLE_UUID_BAT_SERVICE).then(service => {
            console.log('Discovered the BATTERY service.');

            return discoverCharacteristic(adapter, service, BLE_UUID_BAT_CHAR)
            .then(characteristic => {
                console.log('Discovered the BATTERY characteristic.');
                return discoverCharCCCD(adapter, characteristic, BLE_UUID_CCCD);				
            })
            .then(descriptor => {
                console.log('Discovered the BATTERY characteristic\'s CCCD.');
				
				//enable battery notifications
				adapter.writeDescriptorValue(descriptor.instanceId, [1, 0], false, err => {
					if (err) {
						reject(Error(`Error enabling notifications on the BATTERY characteristic: ${err}.`));
						process.exit(1);
					}

					console.log('Notifications enabled on the BATTERY characteristic.');
					resolve('Done bat');
				});
            });
        }).catch(error => {
            console.log(error);
            process.exit(1);
        });
		
	});
}


//enable NUS notifications
function enable_nus_notif(adapter, device){
	return new Promise((resolve, reject) => {
    discoverService(adapter, device, BLE_UUID_NUS_SREVICE).then(service => {
            console.log('Discovered the NUS service.');

            return discoverCharacteristic(adapter, service, BLE_UUID_NUS_TX_CHARACTERISTIC)
            .then(characteristic => {
                console.log('Discovered the TX characteristic.');
                return discoverCharCCCD(adapter, characteristic, BLE_UUID_CCCD);
            })
            .then(descriptor => {
                console.log('Discovered the TX characteristic\'s CCCD.');
				
				//enable battery notifications
				adapter.writeDescriptorValue(descriptor.instanceId, [1, 0], false, err => {
					if (err) {
						reject(Error(`Error enabling notifications on the NUS characteristic: ${err}.`));
						process.exit(1);
					}

					console.log('Notifications enabled on the NUS characteristic.');
					resolve('Done NUS');
				});
				
            });
        }).catch(error => {
            console.log(error);
            process.exit(1);
        });
	});
}

//find SAADC characteristic
function find_saadc_char(adapter, device){
	return new Promise((resolve, reject) => {
    discoverService(adapter, device, BLE_UUID_SAADC_SERVICE_UUID).then(service => {
            console.log('Discovered the SAADC service.');

            return discoverCharacteristic(adapter, service, BLE_UUID_SAADC_VALUES_CHAR_UUID)
            .then(characteristic => {
                console.log('Discovered the SAADC characteristic.');
				saadc_char=characteristic;	//save SAADC characteristic to variable
				//console.log(saadc_char);
                //return discoverCharCCCD(adapter, characteristic, BLE_UUID_SAADC_CCCD);
				resolve('Done SAADC');
				
            });
        }).catch(error => {
            console.log(error);
            process.exit(1);
        });
	});
}

// function to wirte to SAADC char
function write_saadc_char(adapter, characteristic, value){
	adapter.writeCharacteristicValue(characteristic.instanceId, value, false, err => {
        if (err) {
            console.log(`Error writing to SAADC characteristic: ${err}.`);
            process.exit(1);
        }

        console.log('SAADC enabled.');
		console.log(characteristic);
    });
}


/**
 * Discovers a service by UUID in the BLE peripheral's GATT attribute table.
 *
 * @param {Adapter} adapter Adapter being used.
 * @param {Device} device Bluetooth central device being used.
 * @returns {Promise} Resolves on successfully discovering the service.
 *                    If an error occurs, rejects with the corresponding error.
 */
function discoverService(adapter, device, UUID) {
    return new Promise((resolve, reject) => {
        adapter.getServices(device.instanceId, (err, services) => {
            if (err) {
                reject(Error(`Error discovering the service: ${err}.`));
                return;
            }

            for (const service in services) {
                if (services[service].uuid === UUID) {
                    resolve(services[service]);
                    return;
                }
            }

            reject(Error('Did not discover the service in peripheral\'s GATT attribute table.'));
        });
    });
}

/**
 * Discovers a characteristic by UUID in the BLE peripheral's GATT attribute table.
 *
 * @param {Adapter} adapter Adapter being used.
 * @param {Service} Service The service to discover characteristics from
 * @returns {Promise} Resolves on successfully discovering the characteristic.
 *                    If an error occurs, rejects with the corresponding error.
 */
function discoverCharacteristic(adapter, Service, UUID) {
    return new Promise((resolve, reject) => {
        adapter.getCharacteristics(Service.instanceId, (err, characteristics) => {
            if (err) {
                reject(Error(`Error discovering the service's characteristics: ${err}.`));
                return;
            }

            // eslint-disable-next-line guard-for-in
            for (const characteristic in characteristics) {
                if (characteristics[characteristic].uuid === UUID) {
                    resolve(characteristics[characteristic]);
                    return;
                }
            }

            reject(Error('Did not discover the characteristic in peripheral\'s GATT attribute table.'));
        });
    });
}

/**
 * Discovers a characteristic's CCCD by UUID in the BLE peripheral's GATT attribute table.
 *
 * @param {Adapter} adapter Adapter being used.
 * @param {Characteristic} Characteristic The characteristic to discover CCCD from.
 * @returns {Promise} Resolves on successfully discovering the characteristic's CCCD.
 *                    If an error occurs, rejects with the corresponding error.
 */
function discoverCharCCCD(adapter, Characteristic, UUID) {
    return new Promise((resolve, reject) => {
        adapter.getDescriptors(Characteristic.instanceId, (err, descriptors) => {
            if (err) {
                reject(Error(`Error discovering the characteristic's CCCD: ${err}.`));
                return;
            }

            for (const descriptor in descriptors) {
                if (descriptors[descriptor].uuid === UUID) {
                    resolve(descriptors[descriptor]);
                    return;
                }
            }

            reject(Error('Did not discover the CCCD in peripheral\'s GATT attribute table.'));
        });
    });
}

/**
 * Allow user to toggle SAADC with a key press, as well as cleanly exiting the application.
 *
 * @param {Adapter} adapter Adapter being used.
 * @param {Descriptor} cccdDescriptor The descriptor for enabling/disabling enable/disable notifications.
 * @returns {undefined}
 */
function addUserInputListener(adapter, characteristic) {
    process.stdin.setEncoding('utf8');
    process.stdin.setRawMode(true);

    const saadcEnabled = [0, 0];

    process.stdin.on('readable', () => {
        const chunk = process.stdin.read();
        if (chunk === null) return;

        if (chunk[0] === 'q' || chunk[0] === 'Q') {
            adapter.close(err => {
                if (err) {
                    console.log(`Error closing the adapter: ${err}.`);
                }

                console.log('Exiting the application...');
                process.exit(1);
            });
        } else {
            if (saadcEnabled[0]) {
                saadcEnabled[0] = 0;
                console.log('Disabling SAADC.');
				
				// write 0 to characteristic to enable SAADC
				adapter.writeCharacteristicValue(characteristic, [0], false, err => {
					if (err) {
						console.log(`Error disabling SAADC characteristic: ${err}.`);
						process.exit(1);
					}

					console.log('SAADC toggled.');
				});
				
				
            } else {
                saadcEnabled[0] = 1;
                console.log('Enabling SAADC.');
				
				// write 1 to characteristic to enable SAADC
				adapter.writeCharacteristicValue(characteristic, [1], false, err => {
					if (err) {
						console.log(`Error enabling SAADC characteristic: ${err}.`);
						process.exit(1);
					}

					console.log('SAADC toggled.');
				});
            }


        }
    });
}

/**
 * Connects to the desired BLE peripheral.
 *
 * @param {Adapter} adapter Adapter being used.
 * @param {any} connectToAddress Device address of the advertising BLE peripheral to connect to.
 * @returns {Promise} Resolves on successfully connecting to the BLE peripheral.
 *                    If an error occurs, rejects with the corresponding error.
 */
function connect(adapter, connectToAddress) {
    return new Promise((resolve, reject) => {
        console.log(`Connecting to device ${connectToAddress}...`);

        const options = {
            scanParams: {
                active: false,
                interval: 100,
                window: 50,
                timeout: 0,
            },
            connParams: {
                min_conn_interval: 7.5,
                max_conn_interval: 7.5,
                slave_latency: 0,
                conn_sup_timeout: 4000,
            },
        };

        adapter.connect(connectToAddress, options, err => {
            if (err) {
                reject(Error(`Error connecting to target device: ${err}.`));
                return;
            }

            resolve();
        });
    });
}

/**
 * Function to start scanning (GAP Discovery procedure, Observer Procedure).
 *
 * @param {Adapter} adapter Adapter being used.
 * @returns {Promise} Resolves on successfully initiating the scanning procedure.
 *                    If an error occurs, rejects with the corresponding error.
 */
function startScan(adapter) {
    return new Promise((resolve, reject) => {
        console.log('Started scanning...');

        const scanParameters = {
            active: true,
            interval: 100,
            window: 50,
            timeout: 0,
        };

        adapter.startScan(scanParameters, err => {
            if (err) {
                reject(new Error(`Error starting scanning: ${err}.`));
            } else {
                resolve();
            }
        });
    });
}

/**
 * Handling events emitted by adapter.
 *
 * @param {Adapter} adapter Adapter in use.
 * @returns {void}
 */
function addAdapterListener(adapter) {
    /**
     * Handling error and log message events from the adapter.
     */
    adapter.on('logMessage', (severity, message) => { if (severity > 3) console.log(`${message}.`); });
    adapter.on('error', error => { console.log(`error: ${JSON.stringify(error, null, 1)}.`); });

    /**
     * Handling the Application's BLE Stack events.
     */
    adapter.on('deviceConnected', device => {
        console.log(`Device ${device.address}/${device.addressType} connected.`);

		//enable notifications
		enable_bat_notif(adapter, device).then(function(){
			enable_nus_notif(adapter, device).then(function(){
				find_saadc_char(adapter, device).then(function(){
					//console.log(saadc_char);
					//write_saadc_char(adapter, saadc_char, [1]);
					console.log('Press any key to toggle SAADC. ' +
                            'Press `q` or `Q` to disconnect from the BLE peripheral and quit application.');
					addUserInputListener(adapter, saadc_char.instanceId);
				});
			});
		});		
		
    });

    adapter.on('deviceDisconnected', device => {
        console.log(`Device ${device.address} disconnected.`);

        startScan(adapter).then(() => {
            console.log('Successfully initiated the scanning procedure.');
        }).catch(error => {
            console.log(error);
        });
    });

    adapter.on('deviceDiscovered', device => {
        console.log(`Discovered device ${device.address}/${device.addressType}.`);

        if (device.name === 'BLE_Puck') {
            connect(adapter, device.address).then(() => {
                // no need to do anything here
            }).catch(error => {
                console.log(error);
                process.exit(1);
            });
        }
    });

    adapter.on('scanTimedOut', () => {
        console.log('scanTimedOut: Scanning timed-out. Exiting.');
        process.exit(1);
    });

    adapter.on('characteristicValueChanged', attribute => {
        if (attribute.uuid === BLE_UUID_BAT_CHAR) {
            console.log(`Received battery measurement: ${attribute.value}.`);
        }
		else if(attribute.uuid === BLE_UUID_NUS_TX_CHARACTERISTIC){
			console.log(`Received SAADC measurement: ${attribute.value}.`);
		}
    });
}

/**
 * Opens adapter for use with the default options.
 *
 * @param {Adapter} adapter Adapter to be opened.
 * @returns {Promise} Resolves if the adapter is opened successfully.
 *                    If an error occurs, rejects with the corresponding error.
 */
function openAdapter(adapter) {
    return new Promise((resolve, reject) => {
        const baudRate = process.platform === 'darwin' ? 115200 : 1000000;
        console.log(`Opening adapter with ID: ${adapter.instanceId} and baud rate: ${baudRate}...`);

        adapter.open({ baudRate, logLevel: 'error' }, err => {
            if (err) {
                reject(Error(`Error opening adapter: ${err}.`));
            }

            resolve();
        });
    });
}

function help() {
    console.log(`Usage: ${path.basename(__filename)} <PORT> <SD_API_VERSION>`);
    console.log();
    console.log('PORT is the UART for the adapter. For example /dev/ttyS0 on Unix based systems or COM1 on Windows based systems.');
    console.log('SD_API_VERSION can be v2 or v3. nRF51 series uses v2.');
    console.log();
    console.log('It is assumed that the nRF device has been programmed with the correct connectivity firmware.');
}

/**
 * Application main entry.
 */
if (process.argv.length !== 4) {
    help();
    process.exit(-1);
} else {
    const [,, port, apiVersion] = process.argv;

    if (port == null) {
        console.error('PORT must be specified');
        process.exit(-1);
    }

    if (apiVersion == null) {
        console.error('SD_API_VERSION must be provided');
        process.exit(-1);
    } else if (!['v2', 'v3'].includes(apiVersion)) {
        console.error(`SD_API_VERSION must be v2 or v3, argument provided is ${apiVersion}`);
        process.exit(-1);
    }

    const adapter = adapterFactory.createAdapter(apiVersion, port, '');
    addAdapterListener(adapter);

    openAdapter(adapter).then(() => {
        console.log('Opened adapter.');
        return startScan(adapter);
    }).then(() => {
        console.log('Scanning.');
    }).catch(error => {
        console.log(error);
        process.exit(-1);
    });
}
