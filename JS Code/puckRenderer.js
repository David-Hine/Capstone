/* Copyright (c) 2019, Team2
 *
/** @example puck.js
 *
 * @brief Puck Application main file.
 *
 * This file contains the source code for a sample application that acts as a BLE Central device.
 * This application scans for the Puck and reads its data.
 */

'use strict';

//requires for csv file
var fs = require('fs');
var csv = require('fast-csv');
var csvName = '';
var intTrialNumber = 0;

// require electron
const electron = require('electron');
const { app } = require('electron')

const ipc = electron.ipcRenderer;

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


// Arrays for saving data transmitted in each trial
var bat_level_in_percent = 100;
var bat_level_in_volts = 3.2;
var acc_data = [];	//raw data received over BLE
var x = [];			//for data separated by accelerometer axis
var y = [];
var z = [];
var x_volts = []; 	//for updated x,y and z ADC measurements (ie in Volts)
var y_volts = [];
var z_volts = [];
var time_arr = [];
var resultant_g_force = [];
var G_FORCE_x = [];
var G_FORCE_y = [];
var G_FORCE_z = [];
var ACCELERATION_IN_MPS2 = [];
var VELOCITY_IN_MPS = [];
var C_TIME = 0;
var SUM_OF_G = 0;
var length_of_avg_g = 0;
var PEAK_VELOCITY = -99999999999;
var DELTA_VELOCITY = 0;
var AVERAGE_G_FORCE = 0;		// Calculate average g-force
var avgG = '';
var peakVel = '';
var contact = '';


/************************* computer specific, check com port values **********************************************/
const adapter = adapterFactory.createAdapter('v3', 'com3', '');

const btnStart = document.getElementById('btnStart');
const btnStop = document.getElementById('btnStop');
const btnQuit = document.getElementById('btnQuit');

// display calculated values
var intAccel = document.getElementById('intAccel');
var intVel = document.getElementById('intVel');
var intContat = document.getElementById('intContact');

var trialName = "";
const btnTrialSave = document.getElementById('btnTrialSave');
const inputTrialName = document.getElementById('inputTrialName');
var stringPlayerName = document.getElementById('stringPlayerName');

// Listener on the connect button, runs the connection code
const btnConnect = document.getElementById('btnConnect');
const progConnection = document.getElementById('progConnection');
const progBattery = document.getElementById('progBattery');

btnQuit.addEventListener('click', function () {
    ipc.send('window-all-closed');
});

btnConnect.addEventListener('click', function () {
    console.log('connect was pressed.  Ready to start stop.');
    //check that adapter is open and ready to connect

    btnConnect.disabled = true;
    btnConnect.value = "Scanning...";
    progConnection.classList.remove('progress-bar-danger');
    progConnection.classList.add('progress-bar-warning');

    addAdapterListener(adapter);

    openAdapter(adapter).then(() => {
        console.log('Opened adapter');
        return startScan(adapter);
    }).then(() => {
        console.log('Scanning...');
        }).catch(error => {
            alert("Error opening port. Ensure that usb dongle is inserted and driver is installed.");
            console.log('');
            console.log(error);
            location.reload();
            //process.exit(-1);
        });
});

// Listener on the disconnect button
const btnDisconnect = document.getElementById('btnDisconnect');
btnDisconnect.addEventListener('click', function () {
    console.log('disconnect was pressed');
    adapter.close(err => {
        if (err) {
            console.log(`Error closing the adapter: $(err).`)
        }

        //console.log('Exiting the application...')
        //process.exit(1);
    });
    btnConnect.disabled = false;
    btnConnect.value = "Connect";
    btnConnect.classList.remove('btn-success');
    btnConnect.classList.add('btn-primary');

    progConnection.classList.remove('progress-bar-success');
    progConnection.classList.add('progress-bar-danger');

    btnDisconnect.disabled = true;
    btnStart.disabled = true;
    btnStop.disabled = true;

    location.reload();
});

// press button before puck is shot
btnStart.addEventListener('click', function () {
    console.log('start trial pressed');
    initializeVariables();
    write_saadc_char(adapter, saadc_char.instanceId, [1]);
    btnStart.disabled = true;
    btnStop.disabled = false;
});

// press button when shot ends
btnStop.addEventListener('click', function () {
    console.log('stop trial pressed');
    write_saadc_char(adapter, saadc_char.instanceId, [0]);

    interpret_data_and_save(acc_data, csvName + intTrialNumber + ".csv");
    intTrialNumber = intTrialNumber + 1;

    console.log("Length of avg g" + length_of_avg_g);
    console.log("Avg g force " + AVERAGE_G_FORCE);
    console.log("Peak velocity: " + PEAK_VELOCITY);
    console.log("Contact time: " + C_TIME);

    //intAccel.value = length_of_avg_g;
    avgG = '' + AVERAGE_G_FORCE;
    peakVel = '' + PEAK_VELOCITY;
    contact = '' + C_TIME;

    intAccel.innerHTML = avgG.slice(0, 5);
    intVel.innerHTML = peakVel.slice(0, 5);
    intContact.innerHTML = contact.slice(0, 5);

    btnStart.disabled = false;
    btnStop.disabled = true;

    
});

// listener for when new trial is created
// btnTrialSave is found in the footer of the #addPlayer modal
// var trialName is used to pass the entered string to the parent
// stringPlayerName is in the parent form to show current trial
btnTrialSave.addEventListener('click', function (e) {
    e.preventDefault();

    console.log('modal save button pressed');
    trialName = inputTrialName.value;
    //btnTest.value = trialName;          // testing purposes
    stringPlayerName.innerText = trialName;
    csvName = trialName;
    intTrialNumber = 1;

    $('#addPlayer').modal('hide');
    
});

//button used for evelopment and testing
//const btnTest = document.getElementById('btnTest');
//btnTest.addEventListener('click', function () {
//    console.log('TEST button pressed');
//    //dialog.showSaveDialog((fileName) => {
//    //    if (fileName === undefined) {
//    //        alert('file was NOT saved');
//    //        return;
//    //    }

//    //    // var content should be the array
//    //    var content = "content"
//    //});

//});



// Function for separating received data into battery and x,y,z values. Also saves data to CSV file
// Call after each trial
function interpret_data_and_save(acc_data, file_name) {

    var csvStream = csv.createWriteStream({ headers: true }),
        writableStream = fs.createWriteStream(file_name);

    //Display message when data is written to CSV file
    writableStream.on("finish", function () {
        console.log("DONE writing to CSV!");
    });

    csvStream.pipe(writableStream);


    var joined_values = acc_data.join();						// Put all values into one variable
    var array_of_values = joined_values.match(/[^,]+,[^,]+/g);	// Each sample is represented by 2 bytes, so combine every 2 elements and place into an array


    //Take every 3rd value of array, save into respective array for x/y/z
    const every_nth = (arr, nth) => arr.filter((e, i) => i % nth === nth - 1);
    z = every_nth(array_of_values, 3);

    array_of_values.unshift('0');	//Add dummy value to 1st element of array, then get y values
    y = every_nth(array_of_values, 3);

    array_of_values.unshift('0');
    x = every_nth(array_of_values, 3);

    // Each sample comes in bytes of 2 (in Hex). JavaScript reads each byte as an integer.
    // So, for each array element, separate the 2 numbers by comma, combine, convert to HEX and convert back to Integer
    for (var k = 0; k < x.length; k++) {
        //For x
        var temp_x = x[k].split(',');
        var num1_x = temp_x[0];
        var num2_x = temp_x[1];
        var hex1_x = (Number(num1_x).toString(16)).slice(-2).toUpperCase();	//convert num1 and num2 to hex
        var hex2_x = (Number(num2_x).toString(16)).slice(-2).toUpperCase();
        hex2_x = hex2_x.concat(hex1_x);										//data comes in as [byte2, byte1] so make second number most significant byte 
        var hex_to_decimal_x = parseInt(hex2_x, 16);						//convert back to decimal
        x_volts.push(hex_to_decimal_x);										//push correct decimal into new arrays

        //For y
        var temp_y = y[k].split(',');
        var num1_y = temp_y[0];
        var num2_y = temp_y[1];
        var hex1_y = (Number(num1_y).toString(16)).slice(-2).toUpperCase();	//convert num1 and num2 to hex
        var hex2_y = (Number(num2_y).toString(16)).slice(-2).toUpperCase();
        hex2_y = hex2_y.concat(hex1_y);										//data comes in as [byte2, byte1] so make second number most significant byte 
        var hex_to_decimal_y = parseInt(hex2_y, 16);						//convert back to decimal
        y_volts.push(hex_to_decimal_y);										//push correct decimal into new arrays

        //For z
        var temp_z = z[k].split(',');
        var num1_z = temp_z[0];
        var num2_z = temp_z[1];
        var hex1_z = (Number(num1_z).toString(16)).slice(-2).toUpperCase();	//convert num1 and num2 to hex
        var hex2_z = (Number(num2_z).toString(16)).slice(-2).toUpperCase();
        hex2_z = hex2_z.concat(hex1_z);										//data comes in as [byte2, byte1] so make second number most significant byte 
        var hex_to_decimal_z = parseInt(hex2_z, 16);						//convert back to decimal
        z_volts.push(hex_to_decimal_z);										//push correct decimal into new arrays

    }

    // Calculate time samples
    var time = (x.length) / 2000;		//time = (#samples per axis)/(2000 samples/sec)
    const time_interval = 0.0005;	//sampling at 2kHz, so 1/2000s = 0.0005s
    var current_time = 0;

    var temp_sum = 0;

    //save time array and calculate adc_result_in_volts
    for (var j = 0; j < x.length; j++) {
        //calculate time interval
        time_arr.push(current_time);
        current_time += (time_interval);

        //calculate adc_result_in_volts
        x_volts[j] = x_volts[j] * 600 / 1024 * 6 / 1000;
        y_volts[j] = y_volts[j] * 600 / 1024 * 6 / 1000;
        z_volts[j] = z_volts[j] * 600 / 1024 * 6 / 1000;

        //convert voltage to g force in each direction
        G_FORCE_x[j] = 400 * (x_volts[j] - (bat_level_in_volts / 2));
        G_FORCE_y[j] = 400 * (y_volts[j] - (bat_level_in_volts / 2));
        G_FORCE_z[j] = 400 * (z_volts[j] - (bat_level_in_volts / 2));

        //calculate resultant g-force = sqrt(x^2 + y^2 + z^2)
        temp_sum = Math.sqrt(parseInt(G_FORCE_x[j]) * parseInt(G_FORCE_x[j]) + parseInt(G_FORCE_y[j]) * parseInt(G_FORCE_y[j]) + parseInt(G_FORCE_z[j]) * parseInt(G_FORCE_z[j]));
        resultant_g_force.push(temp_sum);

    }

    //calculate contact time and average g-force
    //only take values when puck and stick blade are in contact
    //if 50 most recent samples are below 10g's, stop calculating contact time
    //ASSUMED THAT PUCK IS AT REST BEFORE STARTING SAMPLING TRIAL
    var temp_g_force_samples = [];

    function below_10_g(elmt) {			//Function that checks if value is below 10
        return elmt < 10;
    }

    for (var p = 0; p < x.length; p++) {

        temp_g_force_samples.push(resultant_g_force[p]);	//push 50 most recent samples to get contact time

        //Contact time with stick (take all points over 10Gs)
        if (resultant_g_force[p] > 10) {
            C_TIME += 0.0005;

            //For average g-force
            SUM_OF_G += resultant_g_force[p];
            length_of_avg_g += 1;
        }


        //if 50 samples in a row are below 10g's, stop calculating contact time
        if (temp_g_force_samples.length == 50 && temp_g_force_samples.every(below_10_g)) {

            //remove last 10 samples from SUM_OF_G
            for (var z = 0; z < 50; z++) {
                SUM_OF_G -= resultant_g_force[length_of_avg_g - z];
            }

            //and exit from loop
            length_of_avg_g -= 50;

            break;
        }

        else if (temp_g_force_samples.length == 50)
            temp_g_force_samples.shift();	//remove first element of array


        //calculate acceleration from resultant g force = g-force*9.81
        ACCELERATION_IN_MPS2[p] = resultant_g_force[p] * 9.80665;
    }


    //velocity calculation loop
    for (let v = 1; v < (length_of_avg_g - 1); v++) {

        //converting acceleration to velocity
        VELOCITY_IN_MPS[0] = ((ACCELERATION_IN_MPS2[0] + ACCELERATION_IN_MPS2[1]) / 2) * (time_arr[1] - time_arr[0]);
        DELTA_VELOCITY = ((ACCELERATION_IN_MPS2[v - 1] + ACCELERATION_IN_MPS2[v + 1]) / 2) * (time_arr[v + 1] - time_arr[v - 1]);
        VELOCITY_IN_MPS[v] = VELOCITY_IN_MPS[v - 1] + DELTA_VELOCITY;
    }



    //Values to display on UI
    PEAK_VELOCITY = VELOCITY_IN_MPS[length_of_avg_g - 2];	//Peak velocity is puck velocity as it leaves the stick (ie at the end of contact time)
    AVERAGE_G_FORCE = SUM_OF_G / length_of_avg_g;

    //write values to CSV file
    for (var n = 0; n < x.length; n++) {
        //write values to CSV file
        csvStream.write({
            Time_sec: time_arr[n], X_volts: x_volts[n], Y_volts: y_volts[n], Z_volts: z_volts[n],
            G_force_x: G_FORCE_x[n], G_force_y: G_FORCE_y[n], G_force_z: G_FORCE_z[n], Res_g_force: resultant_g_force[n],
            Velocity_m_s: VELOCITY_IN_MPS[n]
        });
    }
    csvStream.end();

    //clear arrays for use in next trial
    acc_data.length = 0;
    x.length = 0;
    y.length = 0;
    z.length = 0;
    x_volts.length = 0;
    y_volts.length = 0;
    z_volts.length = 0;
    time_arr.length = 0;
    resultant_g_force.length = 0;
    G_FORCE_x.length = 0;
    G_FORCE_y.length = 0;
    G_FORCE_z.length = 0;
    ACCELERATION_IN_MPS2.length = 0;
    VELOCITY_IN_MPS.length = 0;

}



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
            //location.reload();
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
				saadc_char = characteristic;	//save SAADC characteristic to variable
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
// value = [0] stops trial
// value = [1] starts trial
function write_saadc_char(adapter, characteristic, value){
	adapter.writeCharacteristicValue(characteristic, value, false, err => {
        if (err) {
            console.log(`Error writing to SAADC characteristic: ${err}.`);
            process.exit(1);
        }

        console.log('Sampling started.');
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
				
				//stop ADC FIRST
				

                console.log('Exiting the application...');
                process.exit(1);
            });
        } else {
            if (saadcEnabled[0]) {
                saadcEnabled[0] = 0;
                console.log('Disabling SAADC.');
				
				// write 0 to characteristic to disable SAADC
				adapter.writeCharacteristicValue(characteristic, [0], false, err => {
					if (err) {
						console.log(`Error disabling SAADC characteristic: ${err}.`);
						process.exit(1);
					}

					console.log('SAADC toggled.');
				});
				
				
				//when SAADC stopped, write data to csv file
				// Figure out how to enter csv title name (2nd parameter)
				interpret_data_and_save(acc_data, "log.csv");
				
				
				
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
            timeout: 30,
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
    adapter.on('logMessage', (severity, message) => {
        if (severity > 3) console.log(`${message}.`);
        console.log('addAdapter logMessage');
    });
    adapter.on('error', error => {
        console.log(`error: ${JSON.stringify(error, null, 1)}.`);
        console.log('addAdapter error');
        console.log('2');
    });

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
					console.log('notifications on for battery and nus');
					//addUserInputListener(adapter, saadc_char.instanceId);

                    btnConnect.value = "Connected";
                    btnConnect.classList.remove('btn-primary');
                    btnConnect.classList.add('btn-success');
                    btnConnect.disabled = true;

                    progConnection.classList.remove('progress-bar-warning');
                    progConnection.classList.add('progress-bar-success');

                    btnDisconnect.disabled = false;
                    btnStart.disabled = false;
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
        location.reload();
        //process.exit(1);
    });

    adapter.on('characteristicValueChanged', attribute => {
        if (attribute.uuid === BLE_UUID_BAT_CHAR) {
            console.log(`Received battery measurement: ${attribute.value}.`);
			
			//NEED TO DISPLAY INCOMING BATTERY % SOMEWHERE IN UI
			//save current battery value
			bat_level_in_percent = attribute.value;
            bat_level_in_volts = ((3200 - 400 + (4 * bat_level_in_percent)) / 1000);

            if (bat_level_in_percent > 100) {
                //progBattery.classList.remove('progress-bar-primary');
                progBattery.classList.remove('progress-bar-warning');
                progBattery.classList.add('progress-bar-success');
            }
            else {
                //progBattery.classList.remove('progress-bar-primary');
                progBattery.classList.remove('progress-bar-success');
                progBattery.classList.add('progress-bar-danger');
            }
            
        }
		else if(attribute.uuid === BLE_UUID_NUS_TX_CHARACTERISTIC){
			console.log(`Received SAADC measurement: ${attribute.value}.`);
			
			//add to data array
			acc_data.push(attribute.value);
			
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
//if (process.argv.length !== 4) {
//    help();
//    process.exit(-1);
//} else {
//    const [,, port, apiVersion] = process.argv;

//    if (port == null) {
//        console.error('PORT must be specified');
//        process.exit(-1);
//    }

//    if (apiVersion == null) {
//        console.error('SD_API_VERSION must be provided');
//        process.exit(-1);
//    } else if (!['v2', 'v3'].includes(apiVersion)) {
//        console.error(`SD_API_VERSION must be v2 or v3, argument provided is ${apiVersion}`);
//        process.exit(-1);
//    }

//    const adapter = adapterFactory.createAdapter(apiVersion, port, '');
//    addAdapterListener(adapter);

//    openAdapter(adapter).then(() => {
//        console.log('Opened adapter.');
//        return startScan(adapter);
//    }).then(() => {
//        console.log('Scanning.');
//    }).catch(error => {
//        console.log(error);
//        process.exit(-1);
//    });
//}

// initialize variables before shot is taken
function initializeVariables() {
    bat_level_in_percent = 100;
    bat_level_in_volts = 3.2;
    acc_data = [];	//raw data received over BLE
    x = [];			//for data separated by accelerometer axis
    y = [];
    z = [];
    x_volts = []; 	//for updated x,y and z ADC measurements (ie in Volts)
    y_volts = [];
    z_volts = [];
    time_arr = [];
    resultant_g_force = [];
    G_FORCE_x = [];
    G_FORCE_y = [];
    G_FORCE_z = [];
    ACCELERATION_IN_MPS2 = [];
    VELOCITY_IN_MPS = [];
    C_TIME = 0;
    SUM_OF_G = 0;
    length_of_avg_g = 0;
    PEAK_VELOCITY = -99999999999;
    DELTA_VELOCITY = 0;
    AVERAGE_G_FORCE = 0;		// Calculate average g-force
}