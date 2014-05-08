#!/usr/bin/env node

var path = require('path');
var spawn = require('child_process').spawn;
var EventEmitter = require('events').EventEmitter;
var Parser = require('newline-json').Parser;

function runProgram (cmd) {
	var e = new EventEmitter();
	var proc = spawn(cmd, []);
	// proc.stdout.pipe(process.stdout);
	// proc.stderr.pipe(process.stderr);
	// proc.on('exit', function (code) {
	// 	console.error('exited with code', code);
		// process.exit(code);
	// })

	var parser = new Parser();
	proc.stdout.pipe(parser);
	parser.on('data', function (data) {
		if (data && data.action) {
			e.emit(data.action);
		}
	})
	return e;
}

function listenDbus () {
	var e = new EventEmitter();

	var DBus = require('dbus');
	var dbus = new DBus();
	var bus = dbus.getBus('session');
	bus.getInterface('org.gnome.SettingsDaemon', '/org/gnome/SettingsDaemon/MediaKeys', 'org.gnome.SettingsDaemon.MediaKeys', function(err, iface) {
		e.emit('connected');
		iface.on('MediaPlayerKeyPressed', function (n, value) {
			switch (value) {
				case 'Play': e.emit('play'); return;
				case 'Next': e.emit('next'); return;
				case 'Previous': e.emit('back'); return;
				//case 'Stop': e.emit('stop'); return;
			}
		});
		iface.GrabMediaPlayerKeys(0, 'org.gnome.SettingsDaemon.MediaKeys');
	});
	return e;
}

function listen () {
	if (process.platform == 'darwin') {
		var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener');
		return runProgram(cmd);

	} else if (process.platform == 'win32') {
		var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener.exe');
		return runProgram(cmd);

	} else if (process.platform == 'linux') {
		return listenDbus();

	} else {
		throw new Error('unsupported platform', process.platform)
	}
}

exports.listen = listen;

if (require.main == module) {
	// demo
	var e = listen();
	e.on('connected', function () {
		console.log('connected');
	})
	e.on('play', function () {
		console.log('play');
	})
	e.on('next', function () {
		console.log('next');
	})
	e.on('back', function () {
		console.log('back');
	})
}
