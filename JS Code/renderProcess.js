// gets called in the body of the index.html
console.log("from renderProcess.js");

const path = require('path')
const url = require('url')
const electron = require('electron')
const ipc = electron.ipcRenderer

// connect button and code
const btnConnect = document.getElementById('btnConnect');
const btnSync = document.getElementById('btnSync');

btnConnect.addEventListener('click', function () {
    // write code for button
    console.log('from renderProcess')
    console.log('async message 1')
    ipc.send('async-message')
    console.log('async message 2')
})

btnSync.addEventListener('click', function () {
    // write code for button
    console.log('from renderProcess')
    console.log('sync message 1')
    const reply = ipc.sendSync('sync-message')
    console.log('reply')
    console.log('sync message 2')
})

ipc.on('async-reply', function (event, arg) {
    console.log(arg)
})

// remote does ipc sync way, exo here has the main build the new browser
const BrowserWindow = electron.remote.BrowserWindow